// -*- mode: c++ -*-

#ifndef TILE_SOURCE_H
#define TILE_SOURCE_H

#include <SDL.h>

namespace Cats {
  class TileSource {
  public:
    TileSource(SDL_Texture* image, int x, int y, int w, int h);
    SDL_Texture *GetImage() {return image;}
    SDL_Rect GetSrc() {return src;}

  private:
    SDL_Texture* image;
    SDL_Rect src;
  };
}

#endif
