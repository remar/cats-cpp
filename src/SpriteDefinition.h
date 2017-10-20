// -*- mode: c++ -*-

#include <string>
#include <map>
#include "Animation.h"

namespace Cats {
  class SpriteDefinition {
  public:
    SpriteDefinition(std::string filename);

  private:
    std::map<std::string,Animation*> animations;
  };
}
