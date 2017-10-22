#include "SpriteInstance.h"

namespace Cats {
  SpriteInstance::SpriteInstance(SpriteDefinition *spriteDef) : x(0), y(0), visible(true) {
    this->spriteDefinition = spriteDef;
    animationState.SetAnimation(spriteDefinition->GetDefaultAnimation());
  }

  void SpriteInstance::Draw(SDL_Renderer *renderer, int deltaMillis) {
    if(!visible) {
      return;
    }
    animationState.Animate(deltaMillis);
    animationState.Draw(renderer, x, y);
  }
}
