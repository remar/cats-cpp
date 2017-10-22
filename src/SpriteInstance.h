// -*- mode: c++ -*-

#ifndef SPRITE_INSTANCE_H
#define SPRITE_INSTANCE_H

#include "SpriteDefinition.h"
#include "AnimationState.h"

namespace Cats {
  class SpriteInstance {
  public:
    SpriteInstance(SpriteDefinition *spriteDef);
    void Draw(SDL_Renderer *renderer, int deltaMillis);

  private:
    SpriteDefinition *spriteDefinition;
    AnimationState animationState;
    int x;
    int y;
    bool visible;
  };
}

#endif
