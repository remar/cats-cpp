#include "TileLayer.h"

namespace Cats {
  TileLayer::TileLayer(int width, int height, int tileWidth, int tileHeight)
    : width(width), height(height),
      tileWidth(tileWidth), tileHeight(tileHeight),
      offsetX(0), offsetY(0) {
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

  void TileLayer::Draw(SDL_Renderer *renderer) {
    for(int y = 0;y < height;y++) {
      for(int x = 0;x < width;x++) {
	tiles[y * width + x].Draw(renderer, offsetX, offsetY);
      }
    }
  }

  void TileLayer::SetTile(int x, int y, TileSource *source) {
    tiles[y * width + x].Set(source->GetImage(), source->GetSrc());
  }

  void TileLayer::SetScroll(int x, int y) {
    offsetX = x;
    offsetY = y;
  }
}
