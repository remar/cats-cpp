#include "ImageJsonReader.h"
#include "Util.h"

namespace Cats {
  extern ImageCache imageCache;

  ImageJsonReader::ImageJsonReader(JsonValue value, std::string filename) : value(value), filename(filename) {
    gotPath = gotWidth = gotHeight = false;

    for(auto obj : value) {
      if(strcmp(obj->key, "path") == 0) {
	image = imageCache.GetImage(GetBasePath(filename) + (obj->value).toString());
	gotPath = true;
      } else if(strcmp(obj->key, "width") == 0) {
	width = (obj->value).toNumber();
	gotWidth = true;
      } else if(strcmp(obj->key, "height") == 0) {
	height = (obj->value).toNumber();
	gotHeight = true;
      }
    }
  }

  bool ImageJsonReader::ValidImageJson() {
    return gotPath && gotWidth && gotHeight;
  }
}
