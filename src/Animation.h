// -*- mode: c++ -*-

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

  private:
    std::vector<Frame> frames;
    bool looping;
    SDL_Texture *image;
    int tileWidth;
    int tileHeight;

    void AddImage(JsonValue value, std::string filename);
    void AddFrames(JsonValue value, std::string filename);
  };
}
