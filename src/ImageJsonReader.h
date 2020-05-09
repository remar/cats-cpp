#ifndef IMAGE_JSON_READER_H
#define IMAGE_JSON_READER_H


#include "gason.h"
#include "ImageCache.h"

namespace Cats {
  class ImageJsonReader {
  public:
    ImageJsonReader(JsonValue value, std::string filename);
    bool ValidImageJson();
    SDL_Texture *GetImage() {return image;}
    int GetWidth() {return width;}
    int GetHeight() {return height;}
  private:
    JsonValue value;
    std::string filename;
    SDL_Texture *image;
    int width;
    int height;
    bool gotPath;
    bool gotWidth;
    bool gotHeight;
  };
}

#endif
