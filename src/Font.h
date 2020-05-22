// -*- mode: c++ -*-

#ifndef FONT_H
#define FONT_H

#include <string>
#include <map>
#include "Animation.h"

namespace Cats {
  class Font {
  public:
    Font(std::string filename);

  private:
    void AddImage(JsonValue value, std::string filename);
    void AddCharacters(JsonValue value, std::string filename);
  };
}

#endif
