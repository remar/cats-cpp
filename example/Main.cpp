#include "Cats.h"
#include <SDL2/SDL.h>
#include <list>
#include <random>

// For compiling libcats.a and then compiling example, in emacs:
// make -C ../src && make -k && ./example

using namespace std;

const int screenWidth = 640;
const int screenHeight = 480;

bool quitEvent = false;
bool fullscreen = false;
bool textVisible = true;
int text;

void checkForInput() {
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    if(event.type == SDL_QUIT) {
      quitEvent = true;
    } else if(event.type == SDL_KEYDOWN) {
      switch(event.key.keysym.sym) {
      case SDLK_f:
	fullscreen = !fullscreen;
	Cats::SetFullscreen(fullscreen);
	break;

      case SDLK_v:
	textVisible = !textVisible;
	Cats::ShowText(text, textVisible);
	break;
      }
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

  Cats::ShowPointer(false);
  Cats::LoadSprite("gfx/cpngood.json");
  Cats::LoadTileset("gfx/block1.json");
  Cats::LoadFont("gfx/font.json");

  Cats::SetupTileLayer(20, 15, 32, 32);

  for(int x = 1;x < 19;x++) {
    Cats::SetTile(x, 0, "block1", 1, 0);
    Cats::SetTile(x, 14, "block1", 1, 0);
  }
  for(int y = 1;y < 14;y++) {
    Cats::SetTile(0, y, "block1", 2, 0);
    Cats::SetTile(19, y, "block1", 2, 0);
  }
  Cats::SetTile(0, 0, "block1", 3, 0);
  Cats::SetTile(19, 0, "block1", 4, 0);
  Cats::SetTile(0, 14, "block1", 5, 0);
  Cats::SetTile(19, 14, "block1", 6, 0);

  text = Cats::CreateText("font", "Hello world");
  Cats::SetTextPosition(text, 32, 32);

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
