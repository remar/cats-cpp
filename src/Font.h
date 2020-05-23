// -*- mode: c++ -*-

#ifndef FONT_H
#define FONT_H

#include <string>
#include <map>
#include "Animation.h"

namespace Cats {
  class Font {
  public:
    Font(std::string filename);

  private:
    SDL_Texture *image;
    int imageWidth;
    int imageHeight;
    int tileWidth;
    int tileHeight;
    std::string characters;

    void AddImage(JsonValue value, std::string filename);
    void AddCharacters(JsonValue value, std::string filename);
  };
}

#endif
