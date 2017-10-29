#include "Tile.h"

namespace Cats {
  Tile::Tile() : image(nullptr) {}

  void Tile::Setup(int x, int y, int width, int height) {
    this->x = x*width;
    this->y = y*height;
    dest.w = width;
    dest.h = height;
  }

  void Tile::Draw(SDL_Renderer *renderer, int xOffset, int yOffset) {
    if(image == nullptr) {
      return;
    }

    dest.x = x + xOffset;
    dest.y = y + yOffset;

    SDL_RenderCopy(renderer, image, &src, &dest);
  }

  void Tile::Set(SDL_Texture *image, SDL_Rect src) {
    this->image = image;
    this->src = src;
  }
}
