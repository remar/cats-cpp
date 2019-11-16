#include "Cats.h"
#include <SDL2/SDL.h>

const int screenWidth = 640;
const int screenHeight = 480;

bool quitEvent = false;

void checkForInput() {
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    if(event.type == SDL_QUIT) {
      quitEvent = true;
    }
  }
}

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);

  Cats::Init(screenWidth, screenHeight);

  int lastFrameTime = SDL_GetTicks();

  while(!quitEvent) {
    checkForInput();

    float delta = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
    lastFrameTime = SDL_GetTicks();

    Cats::Redraw(delta);
  }

  SDL_Quit();

  return 0;
}
