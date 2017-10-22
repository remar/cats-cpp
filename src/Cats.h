// -*- mode: c++ -*-

#ifndef CATS_H
#define CATS_H

#include <string>

namespace Cats {
  void Init(int width, int height);
  void Redraw(float delta);
  void SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue);
  void LoadSprite(std::string filename);
  int CreateSpriteInstance(std::string spritename);
}

#endif
