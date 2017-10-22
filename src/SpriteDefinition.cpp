#include "SpriteDefinition.h"
#include "Util.h"
#include "gason.h"
#include <stdexcept>
#include <string.h>

#include <iostream>

namespace Cats {
  SpriteDefinition::SpriteDefinition(std::string filename) {
    char *jsontext = strdup(ReadFile(filename).c_str());
    char *endptr;
    JsonValue value;
    JsonAllocator allocator;

    jsonParse(jsontext, &endptr, &value, allocator);
    JsonNode* node = value.toNode();

    value = node->value;
    for(auto anim : value) {
      JsonNode *animDef = (anim->value).toNode();
      animations[anim->key] = new Animation(anim->value, filename);
    }

    free(jsontext);
  }
}
