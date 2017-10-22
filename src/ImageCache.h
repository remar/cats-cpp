// -*- mode: c++ -*-

#ifndef IMAGE_CACHE_H
#define IMAGE_CACHE_H

#include <SDL.h>
#include <string>
#include <map>

namespace Cats {
  class ImageCache {
  public:
    void ConnectRenderer(SDL_Renderer *renderer);
    SDL_Texture* GetImage(std::string filename);

  private:
    SDL_Renderer *renderer;
    std::map<std::string,SDL_Texture*> cache;
  };
}

#endif
