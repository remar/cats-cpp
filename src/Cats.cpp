#include "Cats.h"
#include "ImageCache.h"
#include "SpriteDefinition.h"
#include "SpriteInstance.h"
#include "Util.h"
#include <SDL.h>
#include <stdexcept>
#include <map>

namespace Cats {
  namespace {
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::map<std::string,SpriteDefinition*> spriteDefinitions;
    std::map<int,SpriteInstance*> spriteInstances;
    int nextSpriteId = 0;

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
    int deltaMillis = (int)(delta * 1000);

    SDL_RenderClear(renderer);

    for(auto const& spriteInstance : spriteInstances) {
      (spriteInstance.second)->Draw(renderer, deltaMillis);
    }

    SDL_RenderPresent(renderer);
  }

  void SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue) {
    SDL_SetRenderDrawColor(renderer, red, green, blue, 0xFF);
  }

  void LoadSprite(std::string filename) {
    std::string name = FilenameToName(filename);
    spriteDefinitions[name] = new SpriteDefinition(filename);
  }

  int CreateSpriteInstance(std::string spritename) {
    int spriteId = nextSpriteId;
    nextSpriteId++;
    spriteInstances[spriteId] = new SpriteInstance(spriteDefinitions[spritename]);
    return spriteId;
  }
}
