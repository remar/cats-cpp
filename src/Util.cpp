#include "Util.h"

#include <fstream>
#include <sstream>

namespace Cats {
  std::string FilenameToName(std::string filename) {
    int afterlastslash = filename.rfind("/") + 1;
    int jsonpos = filename.find(".json");
    int len = jsonpos - afterlastslash;
    return filename.substr(afterlastslash, len);
  }

  std::string GetBasePath(std::string filename) {
    if(filename.find("/") == std::string::npos) {
      return "";
    }
    return filename.substr(0, filename.rfind("/") + 1);
  }

  std::string ReadFile(std::string filename) {
    std::ifstream s(filename);
    std::stringstream buffer;
    buffer << s.rdbuf();
    return buffer.str();
  }
}
