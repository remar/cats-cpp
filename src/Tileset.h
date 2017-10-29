// -*- mode: c++ -*-

#ifndef TILESET_H
#define TILESET_H

#include "gason.h"
#include <string>
#include <SDL.h>

namespace Cats {
  class Tileset {
  public:
    Tileset(std::string filename);

  private:
    SDL_Texture *image;
    int width;
    int height;

    void AddImage(JsonValue value, std::string filename);
  };
}

#endif
