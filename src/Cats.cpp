#include "Cats.h"
#include <SDL.h>
#include <stdexcept>

namespace Cats {
  namespace {
    SDL_Window *window;
    SDL_Renderer *renderer;
    void throw_runtime_error() {
      throw std::runtime_error(SDL_GetError());
    }
  }
  
  void Init(int width, int height) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
      throw_runtime_error();
    }

    if((window = SDL_CreateWindow("Cats++",
				  SDL_WINDOWPOS_UNDEFINED,
				  SDL_WINDOWPOS_UNDEFINED,
				  width, height,
				  SDL_WINDOW_SHOWN)) == 0) {
      throw_runtime_error();
    }

    if((renderer = SDL_CreateRenderer(window,
				      -1,
				      SDL_RENDERER_ACCELERATED)) == 0) {
      throw_runtime_error();
    }

    SDL_RenderSetLogicalSize (renderer, width, height);
    SDL_SetRenderDrawColor (renderer, 0x00, 0x00, 0x00, 0xFF);
  }
}
