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
    std::cout << node->key << "\n";
  }
}
