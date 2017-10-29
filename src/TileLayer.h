// -*- mode: c++ -*-

#ifndef TILE_LAYER_H
#define TILE_LAYER_H

#include "Tile.h"

namespace Cats {
  class TileLayer {
  public:
    TileLayer(int width, int height, int tileWidth, int tileHeight);
    ~TileLayer();

  private:
    Tile* tiles;
    int width;
    int height;
    int tileWidth;
    int tileHeight;
  };
}

#endif
