// -*- mode: c++ -*-

#ifndef ANIMATION_STATE_H
#define ANIMATION_STATE_H

#include "Animation.h"

namespace Cats {
  class AnimationState {
  public:
    void SetAnimation(Animation *animation);
    void Animate(int deltaMillis);
    void Draw(SDL_Renderer *renderer, int x, int y);

  private:
    Animation* animation;
    int currentFrame;
    int currentFrameTime;
    int currentFrameDuration;
    int animationLength;
    bool animationDone;

    void NextFrame();
  };
}

#endif
