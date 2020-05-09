#include "Animation.h"
#include "ImageCache.h"
#include "ImageJsonReader.h"
#include "Util.h"
#include <string.h>
#include <list>
#include <stdexcept>
#include <SDL.h>

namespace Cats {
  extern ImageCache imageCache;

  Animation::Animation(JsonValue value, std::string filename)
    : looping(true), originX(0), originY(0) {
    bool gotImage = false;
    bool gotFrames = false;

    for(auto obj : value) {
      if(strcmp(obj->key, "image") == 0) {
        AddImage(obj->value, filename);
        gotImage = true;
      } else if(strcmp(obj->key, "origin") == 0) {
        AddOrigin(obj->value, filename);
      } else if(strcmp(obj->key, "looping") == 0) {
        looping = ((obj->value).getTag() == JSON_TRUE);
      } else if(strcmp(obj->key, "frames") == 0) {
        AddFrames(obj->value, filename);
        gotFrames = true;
      }
    }

    if(!gotImage || !gotFrames) {
      throw std::runtime_error("Incomplete animation specification in " + filename);
    }

    src.w = dest.w = tileWidth;
    src.h = dest.h = tileHeight;
    src.y = 0;
  }

  void Animation::Draw(SDL_Renderer *renderer, int x, int y, int frame) {
    int index = frames[frame].index;
    if(index == -1) {
      return; // Hide sprite instance during frame duration
    }
    src.x = tileWidth * index;
    dest.x = x - originX;
    dest.y = y - originY;
    SDL_RenderCopy(renderer, image, &src, &dest);
  }

  void Animation::AddImage(JsonValue value, std::string filename) {
    ImageJsonReader reader(value, filename);

    if(!reader.ValidImageJson()) {
      throw std::runtime_error("Incomplete image specification in " + filename);
    }

    image = reader.GetImage();
    tileWidth = reader.GetWidth();
    tileHeight = reader.GetHeight();
  }

  void Animation::AddOrigin(JsonValue value, std::string filename) {
    JsonNode *node = value.toNode();
    if((node->value).getTag() != JSON_NUMBER) {
      throw std::runtime_error("Faulty x origin specification in " + filename);
    }
    originX = (node->value).toNumber();
    node = node->next;
    if(node == nullptr) {
      throw std::runtime_error("Missing y origin specification in " + filename);
    }
    if((node->value).getTag() != JSON_NUMBER) {
      throw std::runtime_error("Faulty y origin specification in " + filename);
    }
    originY = (node->value).toNumber();
  }

  void Animation::AddFrames(JsonValue value, std::string filename) {
    Frame frame;

    for(JsonNode* list : value) {
      JsonNode *elem = (list->value).toNode();
      if((elem->value).getTag() != JSON_NUMBER) {
        throw std::runtime_error("Faulty frame index specification in " + filename);
      }
      frame.index = (elem->value).toNumber();
      if(elem->next == nullptr) {
        throw std::runtime_error("Missing frame duration specification in " + filename);
      }
      elem = elem->next;
      if((elem->value).getTag() != JSON_NUMBER) {
        throw std::runtime_error("Faulty frame duration specification in " + filename);
      }
      frame.duration = (elem->value).toNumber();
      frames.push_back(frame);
    }
  }
}
