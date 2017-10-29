// -*- mode: c++ -*-

#ifndef TILE_H
#define TILE_H

#include <SDL.h>

namespace Cats {
  class Tile {
  public:
    Tile();
    void Setup(int x, int y, int width, int height);
    void Draw(SDL_Renderer *renderer, int xOffset, int yOffset);
    void Set(SDL_Texture *image, SDL_Rect src);

  private:
    SDL_Texture *image;
    SDL_Rect src;
    SDL_Rect dest;
    int x;
    int y;
  };
}

#endif
