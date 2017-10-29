#include "ImageCache.h"
#include "Tileset.h"
#include "Util.h"
#include "gason.h"
#include <cmath>
#include <cstring>
#include <stdexcept>

namespace Cats {
  extern ImageCache imageCache;

  Tileset::Tileset(std::string filename) {
    char *jsontext = strdup(ReadFile(filename).c_str());
    char *endptr;
    JsonValue value;
    JsonAllocator allocator;

    if(jsonParse(jsontext, &endptr, &value, allocator) != JSON_OK) {
      throw std::runtime_error("Unable to parse " + filename);
    }

    JsonNode* node = value.toNode();

    if(strcmp(node->key, "image") != 0) {
      throw std::runtime_error("Object doesn't have \"image\" key! (" + filename + ")");
    }

    AddImage(node->value, filename);

    free(jsontext);

    SetupSources();
  }

  Tileset::~Tileset() {
    for(int i = 0;i < sourcesWidth * sourcesHeight;i++) {
      if(sources[i] != nullptr) {
	delete sources[i];
      }
    }
    delete[] sources;
  }

  TileSource* Tileset::GetTileSource(int x, int y) {
    int index = y * sourcesWidth + x;
    if(sources[index] == nullptr) {
      sources[index] = new TileSource(image, x * width, y * height, width, height);
    }
    return sources[index];
  }

  void Tileset::AddImage(JsonValue value, std::string filename) {
    bool gotPath = false;
    bool gotWidth = false;
    bool gotHeight = false;

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

    if(!gotPath || !gotWidth || !gotHeight) {
      throw std::runtime_error("Incomplete image specification in " + filename);
    }
  }

  void Tileset::SetupSources() {
    uint format;
    int access;
    int textureWidth, textureHeight;
    SDL_QueryTexture(image, &format, &access, &textureWidth, &textureHeight);

    sourcesWidth = std::ceil(((double)textureWidth) / width);
    sourcesHeight = std::ceil(((double)textureHeight) / height);
    sources = new TileSource*[sourcesWidth * sourcesHeight];

    memset(sources, 0, sourcesWidth * sourcesHeight * sizeof(TileSource*));
  }
}
