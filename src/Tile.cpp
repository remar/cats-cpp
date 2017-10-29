#include "Tile.h"

namespace Cats {
  Tile::Tile() : image(nullptr) {}

  void Tile::Setup(int x, int y, int width, int height) {
    x = x*width;
    y = y*height;
    dest.w = width;
    dest.h = height;
  }
}
