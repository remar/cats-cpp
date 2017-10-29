#include "TileSource.h"

namespace Cats {
  TileSource::TileSource(SDL_Texture* image, int x, int y, int w, int h)
    : image(image) {
    src.x = x;
    src.y = y;
    src.w = w;
    src.h = h;
  }
}
