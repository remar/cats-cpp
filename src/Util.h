// -*- mode: c++ -*-

#ifndef UTIL_H
#define UTIL_H

#include <string>

namespace Cats {
  std::string FilenameToName(std::string filename);
  std::string GetBasePath(std::string filename);
  std::string ReadFile(std::string filename);
}

#endif
