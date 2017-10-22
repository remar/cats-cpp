#include "ImageCache.h"
#include <SDL_image.h>
#include <stdexcept>

namespace Cats {
  void ImageCache::ConnectRenderer(SDL_Renderer *renderer) {
    this->renderer = renderer;
  }

  SDL_Texture* ImageCache::GetImage(std::string filename) {
    if(cache.count(filename) == 0) {
      SDL_Surface* surface = IMG_Load(filename.c_str());
      if(surface == nullptr) {
	throw std::runtime_error("Unable to load image " + filename + " (" + IMG_GetError() + ")");
      }
      SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
      if(texture == nullptr) {
	throw std::runtime_error("Unable to create texture from " + filename + " (" + SDL_GetError() + ")");
      }
      cache[filename] = texture;
      SDL_FreeSurface(surface);
    }
    
    return cache[filename];
  }
}
