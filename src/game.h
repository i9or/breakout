#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include <SDL3/SDL.h>

#include "utils/vec2.h"

#define FIXED_TIME_STEP 1.f / 60.f

typedef struct Game {
  SDL_Window* window;
  SDL_Renderer* renderer;

  int windowWidth;
  int windowHeight;

  SDL_Texture* mushroomTexture;
  Vec2 mushroomPreviousPosition;
  Vec2 mushroomPosition;
  Vec2 mushroomVelocity;
  SDL_FRect mushroomRect;

  // Time step
  Uint64 currentTime;
  Uint64 lastTime;
  Uint64 frequency;
  float accumulator;

  // Debug flags
  bool showFPS;
  bool showDebugRendering;
} Game;

Game* createGame(int windowWidth, int windowHeight);
bool initGame(Game* game);
void destroyGame(Game* game);

#endif // BREAKOUT_GAME_H
