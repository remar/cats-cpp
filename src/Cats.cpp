#include "Cats.h"
#include "ImageCache.h"
#include "SpriteDefinition.h"
#include "SpriteInstance.h"
#include "TileLayer.h"
#include "Tileset.h"
#include "Util.h"

#include <SDL.h>
#include <stdexcept>
#include <map>
#include <memory>

namespace Cats {
  namespace {
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::map<std::string,std::unique_ptr<SpriteDefinition>> spriteDefinitions;
    std::map<int,std::unique_ptr<SpriteInstance>> spriteInstances;
    int nextSpriteId = 0;
    TileLayer *tileLayer = nullptr;
    std::map<std::string,std::unique_ptr<Tileset>> tilesets;

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

    if(tileLayer != nullptr) {
      tileLayer->Draw(renderer);
    }

    for(auto const& spriteInstance : spriteInstances) {
      (spriteInstance.second)->Draw(renderer, deltaMillis);
    }

    SDL_RenderPresent(renderer);
  }

  void SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue) {
    SDL_SetRenderDrawColor(renderer, red, green, blue, 0xFF);
  }

  void SetFullscreen(bool on) {
    SDL_SetWindowFullscreen(window, on ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
  }

  void LoadSprite(std::string filename) {
    std::string name = FilenameToName(filename);
    spriteDefinitions[name] = std::unique_ptr<SpriteDefinition>(new SpriteDefinition(filename));
  }

  int CreateSpriteInstance(std::string spritename) {
    int spriteId = nextSpriteId;
    nextSpriteId++;
    spriteInstances[spriteId] = std::unique_ptr<SpriteInstance>(new SpriteInstance(spriteDefinitions.at(spritename).get()));
    return spriteId;
  }

  void RemoveSpriteInstance(int spriteId) {
    spriteInstances.erase(spriteId);
  }

  void ShowSprite(int spriteId, bool show) {
    spriteInstances.at(spriteId)->SetVisible(show);
  }

  void SetSpritePosition(int spriteId, int x, int y) {
    spriteInstances.at(spriteId)->SetPosition(x, y);
  }

  void SetAnimation(int spriteId, std::string animation) {
    spriteInstances.at(spriteId)->SetAnimation(animation);
  }

  void PauseAnimation(int spriteId, bool on) {
    spriteInstances.at(spriteId)->SetPause(on);
  }

  void PauseAnimations(bool on) {
    for(auto const& spriteInstance : spriteInstances) {
      (spriteInstance.second)->SetPause(on);
    }
  }

  void SetupTileLayer(int width, int height, int tileWidth, int tileHeight) {
    if(tileLayer != nullptr) {
      delete tileLayer;
    }
    tileLayer = new TileLayer(width, height, tileWidth, tileHeight);
  }

  void LoadTileset(std::string filename) {
    std::string name = FilenameToName(filename);
    tilesets[name] = std::unique_ptr<Tileset>(new Tileset(filename));
  }

  void SetTile(int x, int y, std::string tileset, int tileX, int tileY) {
    if(tileLayer != nullptr) {
      tileLayer->SetTile(x, y, tilesets[tileset]->GetTileSource(tileX, tileY));
    }
  }

  void SetScroll(int x, int y) {
    if(tileLayer != nullptr) {
      tileLayer->SetScroll(x, y);
    }
  }
}
