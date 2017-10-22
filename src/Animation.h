// -*- mode: c++ -*-

#ifndef ANIMATION_H
#define ANIMATION_H

#include "gason.h"
#include <vector>
#include <string>
#include <SDL.h>

namespace Cats {
  struct Frame {
    int index;
    int duration;
  };

  class Animation {
  public:
    Animation(JsonValue value, std::string filename);
    int GetFrameDuration(int index) { return frames[index].duration; }
    int GetLength() { return frames.size(); }
    bool GetLooping() { return looping; }
    void Draw(SDL_Renderer *renderer, int x, int y, int frame);

  private:
    std::vector<Frame> frames;
    bool looping;
    SDL_Texture *image;
    int tileWidth;
    int tileHeight;
    SDL_Rect src, dest;

    void AddImage(JsonValue value, std::string filename);
    void AddFrames(JsonValue value, std::string filename);
  };
}

#endif
