// -*- mode: c++ -*-

#ifndef SPRITE_DEFINITION_H
#define SPRITE_DEFINITION_H

#include <string>
#include <map>
#include "Animation.h"

namespace Cats {
  class SpriteDefinition {
  public:
    SpriteDefinition(std::string filename);
    Animation* GetDefaultAnimation() {return animations[defaultAnimation];}

  private:
    std::map<std::string,Animation*> animations;
    std::string defaultAnimation;
  };
}

#endif
