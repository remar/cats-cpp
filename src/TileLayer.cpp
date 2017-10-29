#include "TileLayer.h"

namespace Cats {
  TileLayer::TileLayer(int width, int height, int tileWidth, int tileHeight)
    : width(width), height(height),
      tileWidth(tileWidth), tileHeight(tileHeight) {
    tiles = new Tile[width*height];
    for(int y = 0;y < height;y++) {
      for(int x = 0;x < width;x++) {
	tiles[y * width + x].Setup(x, y, tileWidth, tileHeight);
      }
    }
  }

  TileLayer::~TileLayer() {
    delete[] tiles;
  }
}
