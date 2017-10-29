// -*- mode: c++ -*-

#ifndef TILESET_H
#define TILESET_H

#include "TileSource.h"
#include "gason.h"
#include <SDL.h>
#include <string>

namespace Cats {
  class Tileset {
  public:
    Tileset(std::string filename);
    ~Tileset();
    TileSource* GetTileSource(int x, int y);

  private:
    SDL_Texture *image;
    int width;
    int height;
    TileSource **sources;
    int sourcesWidth;
    int sourcesHeight;

    void AddImage(JsonValue value, std::string filename);
    void SetupSources();
  };
}

#endif
