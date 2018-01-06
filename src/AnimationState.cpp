#include "AnimationState.h"

namespace Cats {
  AnimationState::AnimationState() : paused(false) {}

  void AnimationState::SetAnimation(Animation *animation) {
    this->animation = animation;
    currentFrame = 0;
    currentFrameTime = 0;
    currentFrameDuration = animation->GetFrameDuration(currentFrame);
    animationLength = animation->GetLength();
    animationDone = false;
  }

  void AnimationState::Animate(int deltaMillis) {
    if(animationDone || paused) {
      return;
    }

    currentFrameTime += deltaMillis;

    if(currentFrameTime >= currentFrameDuration) {
      NextFrame();
    }
  }

  void AnimationState::Draw(SDL_Renderer *renderer, int x, int y) {
    animation->Draw(renderer, x, y, currentFrame);
  }

  void AnimationState::NextFrame() {
    if(currentFrame + 1 == animationLength) {
      if(animation->GetLooping()) {
        currentFrame = 0;
      } else {
        animationDone = true;
      }
    } else {
      currentFrame++;
    }
    currentFrameTime -= currentFrameDuration;
    currentFrameDuration = animation->GetFrameDuration(currentFrame);
  }
}
