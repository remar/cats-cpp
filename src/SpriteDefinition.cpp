#include "SpriteDefinition.h"
#include "Util.h"
#include "gason.h"
#include <stdexcept>
#include <string.h>

namespace Cats {
  SpriteDefinition::SpriteDefinition(std::string filename) {
    defaultAnimation = "";

    char *jsontext = strdup(ReadFile(filename).c_str());
    char *endptr;
    JsonValue value;
    JsonAllocator allocator;

    if(jsonParse(jsontext, &endptr, &value, allocator) != JSON_OK) {
      throw std::runtime_error("Unable to parse " + filename);
    }
    JsonNode* node = value.toNode();

    if(strcmp(node->key, "animations") != 0) {
      throw std::runtime_error("Object doesn't have \"animations\" key! (" + filename + ")");
    }

    value = node->value;
    for(auto anim : value) {
      animations[anim->key] = new Animation(anim->value, filename);
      if(defaultAnimation == "") {
	defaultAnimation = anim->key;
      }
    }

    free(jsontext);
  }
}
