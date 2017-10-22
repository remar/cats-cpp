#include "Cats.h"
#include <SDL.h>
#include <stdexcept>
#include <map>
#include "SpriteDefinition.h"
#include "Util.h"
#include "ImageCache.h"

namespace Cats {
  namespace {
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::map<std::string,SpriteDefinition*> spriteDefinitions;
    void throw_runtime_error() {
      throw std::runtime_error(SDL_GetError());
    }
  }

  ImageCache imageCache;

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
    imageCache.ConnectRenderer(renderer);

    SDL_RenderSetLogicalSize (renderer, width, height);
    SDL_SetRenderDrawColor (renderer, 0x00, 0x00, 0x00, 0xFF);
  }

  void Redraw(float delta) {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }

  void SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue) {
    SDL_SetRenderDrawColor(renderer, red, green, blue, 0xFF);
  }

  void LoadSprite(std::string filename) {
    std::string name = FilenameToName(filename);
    spriteDefinitions[name] = new SpriteDefinition(filename);
  }
}
