// -*- mode: c++ -*-

#ifndef TILE_LAYER_H
#define TILE_LAYER_H

#include "Tile.h"
#include "TileSource.h"
#include <SDL.h>

namespace Cats {
  class TileLayer {
  public:
    TileLayer(int width, int height, int tileWidth, int tileHeight);
    ~TileLayer();
    void Draw(SDL_Renderer *renderer);
    void SetTile(int x, int y, TileSource *source);

  private:
    Tile* tiles;
    int width;
    int height;
    int tileWidth;
    int tileHeight;
  };
}

#endif
