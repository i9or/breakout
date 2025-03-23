#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include <SDL3/SDL.h>

#include "utils/vec2.h"

#define FIXED_TIMESTEP 1.f / 60.f

typedef struct Game {
  SDL_Window* window;
  SDL_Renderer* renderer;

  int windowWidth;
  int windowHeight;
  float viewportWidth;
  float viewportHeight;

  SDL_Texture* mushroomTexture;
  Vec2 mushroomPreviousPosition;
  Vec2 mushroomPosition;
  Vec2 mushroomVelocity;

  // Time step
  float currentTime;
  float accumulator;
  float lastTime;

  // Debug flags
  bool showFPS;
  bool showDebugRendering;
} Game;

Game* createGame(int windowWidth, int windowHeight);
bool initGame(Game* game);
void destroyGame(Game* game);

#endif // BREAKOUT_GAME_H
