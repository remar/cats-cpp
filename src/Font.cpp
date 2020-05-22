#include "Font.h"
#include "Util.h"
#include "gason.h"

namespace Cats {
  Font::Font(std::string filename) {
    char *jsontext = strdup(ReadFile(filename).c_str());
    char *endptr;
    JsonValue value;
    JsonAllocator allocator;

    if(jsonParse(jsontext, &endptr, &value, allocator) != JSON_OK) {
      throw std::runtime_error("Unable to parse " + filename);
    }
    bool gotImage = false;
    bool gotCharacters = false;

    for(auto obj : value) {
      if(strcmp(obj->key, "image") == 0) {
	AddImage(obj->value, filename);
	gotImage = true;
      } else if(strcmp(obj->key, "characters") == 0) {
	AddCharacters(obj->value, filename);
	gotCharacters = true;
      }
    }

    if(!gotImage || !gotCharacters) {
      throw std::runtime_error("Incomplete font specification in " + filename);
    }
  }

  void Font::AddImage(JsonValue value, std::string filename) {
  }

  void Font::AddCharacters(JsonValue value, std::string filename) {
  }
}
