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
	AddImage(obj->value, GetBasePath(filename));
	gotImage = true;
      } else if(strcmp(obj->key, "looping") == 0) {
	looping = ((obj->value).getTag() == JSON_TRUE);
      } else if(strcmp(obj->key, "frames") == 0) {
	AddFrames(obj->value);
	gotFrames = true;
      }
    }

    if(!gotImage || !gotFrames) {
      throw std::runtime_error("Incomplete animation specification");
    }
  }

  void Animation::AddImage(JsonValue value, std::string basepath) {
    for(auto obj : value) {
      if(strcmp(obj->key, "path") == 0) {
	image = imageCache.GetImage(basepath + (obj->value).toString());
      } else if(strcmp(obj->key, "width") == 0) {
	tileWidth = (obj->value).toNumber();
      } else if(strcmp(obj->key, "height") == 0) {
	tileHeight = (obj->value).toNumber();
      }
    }
  }

  void Animation::AddFrames(JsonValue value) {
    Frame frame;

    for(JsonNode* list : value) {
      JsonNode *elem = (list->value).toNode();
      frame.index = (elem->value).toNumber();
      elem = elem->next;
      frame.duration = (elem->value).toNumber();
      frames.push_back(frame);
    }
  }
}
