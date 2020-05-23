// -*- mode: c++ -*-

#ifndef TEXT_H
#define TEXT_H

#include "Font.h"
#include <vector>

namespace Cats {
  class Text {
  public:
    Text(const Font *font, std::string text);
    void Draw(SDL_Renderer *renderer);
    void SetPosition(int x, int y);

  private:
    SDL_Texture *image;
    int x;
    int y;
    std::vector<SDL_Rect> sources;
    std::vector<SDL_Rect> destinations;

    void InitDestinationRects();
  };
}

#endif
