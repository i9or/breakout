#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include <SDL3/SDL.h>

typedef struct Game {
  SDL_Window* window;
  SDL_Renderer* renderer;

  int windowWidth;
  int windowHeight;
  bool isRunning;

  bool showFPS;
  bool showDebugRendering;
} Game;

Game* createGame(int windowWidth, int windowHeight);
bool initGame(Game* game);
void destroyGame(Game* game);

#endif  // BREAKOUT_GAME_H
