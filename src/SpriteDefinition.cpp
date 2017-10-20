#include "SpriteDefinition.h"
#include "rapidjson/document.h"
#include "Util.h"
#include <stdexcept>

#include <iostream>

namespace Cats {
  namespace {
    void verify(bool shouldBeTrue, std::string filename, std::string errorMessage) {
      if(!shouldBeTrue) {
	throw std::runtime_error("[" + filename + "] " + errorMessage);
      }
    }
  }

  SpriteDefinition::SpriteDefinition(std::string filename) {
    std::string jsontext = ReadFile(filename);

    rapidjson::Document d;
    d.Parse(jsontext.c_str());
    if(d.HasParseError()) {
      throw std::runtime_error("Parse error in " + filename);
    }

    if(!d.HasMember("animations")) {
	throw std::runtime_error("[" + filename + "] Missing \"animations\" key");
    }

    auto animations = d["animations"].GetObject();
    for(auto iter = animations.MemberBegin();iter != animations.MemberEnd();
	++iter) {
      std::cout << iter->name.GetString() << "\n";
    }
  }
}
