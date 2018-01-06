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
    void SetVisible(bool show) {visible = show;}
    void SetPosition(int x, int y) {this->x = x; this->y = y;}
    void SetAnimation(std::string animation);
    void SetPause(bool on);

  private:
    SpriteDefinition *spriteDefinition;
    AnimationState animationState;
    int x;
    int y;
    bool visible;
  };
}

#endif
