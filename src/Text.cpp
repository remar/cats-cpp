#include "Text.h"

namespace Cats {
  Text::Text(const Font *font, std::string text) : x{0}, y{0} {
    sources = font->RenderText(text);
    image = font->GetImage();
    InitDestinationRects();
  }

  void Text::Draw(SDL_Renderer *renderer) {
    for(unsigned int i = 0;i < sources.size();i++) {
      SDL_RenderCopy(renderer, image, &sources[i], &destinations[i]);
    }
  }

  void Text::SetPosition(int x, int y) {
    if(this->x != 0 || this->y != 0) {
      for(SDL_Rect &dest : destinations) {
	dest.x -= this->x;
	dest.y -= this->y;
      }
    }

    this->x = x;
    this->y = y;

    for(SDL_Rect &dest : destinations) {
      dest.x += this->x;
      dest.y += this->y;
    }
  }

  void Text::InitDestinationRects() {
    if(sources.size() > 0) {
      int width = sources[0].w;
      int height = sources[0].h;
      for(int i = 0;i < (int)sources.size();i++) {
	SDL_Rect dest = {i*width, 0, width, height};
	destinations.push_back(dest);
      }
    }
  }
}
