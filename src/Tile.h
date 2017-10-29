// -*- mode: c++ -*-

#ifndef TILE_H
#define TILE_H

#include <SDL.h>

namespace Cats {
  class Tile {
  public:
    Tile();
    void Setup(int x, int y, int width, int height);

  private:
    SDL_Texture *image;
    SDL_Rect src;
    SDL_Rect dest;
    int x;
    int y;
  };
}

#endif
