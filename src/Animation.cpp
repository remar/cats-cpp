#include "Animation.h"
#include "ImageCache.h"
#include "Util.h"
#include <iostream>
#include <string.h>
#include <list>
#include <stdexcept>

namespace Cats {
  extern ImageCache imageCache;

  Animation::Animation(JsonValue value, std::string filename) : looping(true) {
    bool gotImage = false;
    bool gotFrames = false;

    for(auto obj : value) {
      if(strcmp(obj->key, "image") == 0) {
	AddImage(obj->value, filename);
	gotImage = true;
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
  }

  void Animation::AddImage(JsonValue value, std::string filename) {
    bool gotPath = false;
    bool gotWidth = false;
    bool gotHeight = false;

    for(auto obj : value) {
      if(strcmp(obj->key, "path") == 0) {
	image = imageCache.GetImage(GetBasePath(filename) + (obj->value).toString());
	gotPath = true;
      } else if(strcmp(obj->key, "width") == 0) {
	tileWidth = (obj->value).toNumber();
	gotWidth = true;
      } else if(strcmp(obj->key, "height") == 0) {
	tileHeight = (obj->value).toNumber();
	gotHeight = true;
      }
    }

    if(!gotPath || !gotWidth || !gotHeight) {
      throw std::runtime_error("Incomplete image specification in " + filename);
    }
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
