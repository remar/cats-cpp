#include "ImageCache.h"
#include <SDL_image.h>

namespace Cats {
  void ImageCache::ConnectRenderer(SDL_Renderer *renderer) {
    this->renderer = renderer;
  }

  SDL_Texture* ImageCache::GetImage(std::string filename) {
    if(cache.count(filename) == 0) {
      SDL_Surface* surface = IMG_Load(filename.c_str());
      cache[filename] = SDL_CreateTextureFromSurface(renderer, surface);
      SDL_FreeSurface(surface);
    }
    
    return cache[filename];
  }
}
