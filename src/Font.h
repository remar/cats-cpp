// -*- mode: c++ -*-

#ifndef FONT_H
#define FONT_H

#include "gason.h"
#include <string>
#include <map>
#include <SDL.h>
#include <vector>

namespace Cats {
  class Font {
  public:
    Font(std::string filename);
    SDL_Texture *GetImage() const {return image;}
    std::vector<SDL_Rect> RenderText(std::string text) const;

  private:
    SDL_Texture *image;
    int imageWidth;
    int imageHeight;
    int tileWidth;
    int tileHeight;
    std::string characters;

    SDL_Rect RenderCharacter(char c) const;
    void AddImage(JsonValue value, std::string filename);
    void AddCharacters(JsonValue value, std::string filename);
  };
}

#endif
