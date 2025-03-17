#include "game.h"

#include <stdlib.h>

Game* createGame(const int windowWidth, const int windowHeight) {
  Game* game = calloc(1, sizeof(Game));
  if (!game) {
    SDL_Log("Couldn't create a game");

    return NULL;
  }

  game->windowWidth = windowWidth;
  game->windowHeight = windowHeight;

  return game;
}

bool initGame(Game* game) {
  if (!SDL_CreateWindowAndRenderer("Breakout",
                                   game->windowWidth,
                                   game->windowHeight,
                                   0,
                                   &game->window,
                                   &game->renderer)) {
    SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());

    return false;
  }

  return true;
}

void destroyGame(Game* game) {
  if (game != NULL) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    free(game);
  }
}
