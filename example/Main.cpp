#include "Cats.h"
#include <SDL2/SDL.h>
#include <list>
#include <random>

using namespace std;

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

class CaptainGood {
private:
  int spriteId;
  float x, y;
  float dx, dy;
public:
  bool toBeDeleted = false;

  CaptainGood(float x, float y) : x(x), y(y), dx(0), dy(0) {
    spriteId = Cats::CreateSpriteInstance("cpngood");
    Cats::SetSpritePosition(spriteId, x, y);
  }

  void setDirection(float dx, float dy) {
    this->dx = dx;
    this->dy = dy;
    Cats::SetAnimation(spriteId, dx > 0 ? "walk right" : "walk left");
  }

  void move(float delta) {
    if(!toBeDeleted) {
      x += dx * delta;
      y += dy * delta;
      Cats::SetSpritePosition(spriteId, x, y);
    }
  }

  bool outsideOfScreen() {
    return x < -16 || x > screenWidth || y < -24 || y > screenHeight;
  }

  void destroy() {
    toBeDeleted = true;
    Cats::RemoveSpriteInstance(spriteId);
  }
};

int main(int argc, char *argv[]) {
  default_random_engine generator;
  uniform_int_distribution<int> xdistribution(100, screenWidth - 100);
  uniform_int_distribution<int> ydistribution(100, screenHeight - 100);
  uniform_int_distribution<int> deltadistribution(-100, 100);

  SDL_Init(SDL_INIT_VIDEO);

  Cats::Init(screenWidth, screenHeight);

  Cats::LoadSprite("gfx/cpngood.json");

  int lastFrameTime = SDL_GetTicks();

  list<CaptainGood> cpngoods;

  float accum = 0;
  float limit = 0.01;

  while(!quitEvent) {
    checkForInput();

    float delta = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
    lastFrameTime = SDL_GetTicks();

    accum += delta;
    while(accum > limit) {
      accum -= limit;
      cpngoods.push_back(CaptainGood(xdistribution(generator), ydistribution(generator)));
      cpngoods.back().setDirection(deltadistribution(generator), deltadistribution(generator));
    }

    for (auto &cpngood : cpngoods) {
      cpngood.move(delta);
      if(cpngood.outsideOfScreen()) {
	cpngood.destroy();
      }
    }

    cpngoods.remove_if([](CaptainGood &cpngood)
		       {
			 return cpngood.toBeDeleted;
		       });

    Cats::Redraw(delta);
  }

  SDL_Quit();

  return 0;
}
