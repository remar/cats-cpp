#include "Font.h"
#include "ImageJsonReader.h"
#include "Util.h"
#include "gason.h"

namespace Cats {
  Font::Font(std::string filename) {
    char *jsontext = strdup(ReadFile(filename).c_str());
    char *endptr;
    JsonValue value;
    JsonAllocator allocator;

    if(jsonParse(jsontext, &endptr, &value, allocator) != JSON_OK) {
      throw std::runtime_error("Unable to parse " + filename);
    }
    bool gotImage = false;
    bool gotCharacters = false;

    for(auto obj : value) {
      if(strcmp(obj->key, "image") == 0) {
	AddImage(obj->value, filename);
	gotImage = true;
      } else if(strcmp(obj->key, "characters") == 0) {
	AddCharacters(obj->value, filename);
	gotCharacters = true;
      }
    }

    if(!gotImage || !gotCharacters) {
      throw std::runtime_error("Incomplete font specification in " + filename);
    }

    SDL_QueryTexture(image, NULL, NULL, &imageWidth, &imageHeight);
  }

  std::vector<SDL_Rect> Font::RenderText(std::string text) const {
    std::vector<SDL_Rect> chars;

    for(char &c : text) {
      chars.push_back(RenderCharacter(c));
    }

    return chars;
  }

  SDL_Rect Font::RenderCharacter(char c) const {
    SDL_Rect rect = {0, 0, tileWidth, tileHeight};
    int pos = characters.find(c) * tileWidth;
    if(pos >= 0) {
      rect.x = pos%imageWidth;
      rect.y = (pos/imageWidth)*tileHeight;
    }
    return rect;
  }

  void Font::AddImage(JsonValue value, std::string filename) {
    ImageJsonReader reader(value, filename);

    if(!reader.ValidImageJson()) {
      throw std::runtime_error("Incomplete image specification in " + filename);
    }

    image = reader.GetImage();
    tileWidth = reader.GetWidth();
    tileHeight = reader.GetHeight();
  }

  void Font::AddCharacters(JsonValue value, std::string filename) {
    characters = value.toString();
  }
}
