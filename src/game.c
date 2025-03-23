#include "game.h"

#include <stdlib.h>

#include <SDL3/SDL_render.h>

Game* createGame(const int windowWidth, const int windowHeight) {
  Game* game = calloc(1, sizeof(Game));
  if (!game) {
    SDL_Log("Couldn't create a game");

    return NULL;
  }

  game->windowWidth = windowWidth;
  game->windowHeight = windowHeight;

  game->mushroomTexture = NULL;
  game->mushroomPreviousPosition = (Vec2){.x = 0.f, .y = 0.f};
  game->mushroomPosition = (Vec2){.x = 0.f, .y = 0.f};
  game->mushroomVelocity = (Vec2){.x = 0.f, .y = 0.f};

  game->currentTime = 0.f;
  game->accumulator = 0.f;
  game->lastTime = 0.f;

  return game;
}

bool initGame(Game* game) {
  if (!SDL_CreateWindowAndRenderer("Breakout",
                                   game->windowWidth, game->windowHeight, 0,
                                   &game->window, &game->renderer)) {
    SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
    return false;
  }

  if (!SDL_SetRenderLogicalPresentation(game->renderer,
                                        game->windowWidth, game->windowHeight,
                                        SDL_LOGICAL_PRESENTATION_INTEGER_SCALE)) {
    SDL_Log("Couldn't set renderer logical presentation: %s", SDL_GetError());
    return false;
  }

  game->mushroomPosition = (Vec2){.x = 10.f, .y = 10.f};
  game->mushroomVelocity = (Vec2){.x = 100.f, .y = 100.f};

  game->accumulator = 0.f;
  game->currentTime = (float)SDL_GetTicks() / 1000.f;
  game->lastTime = game->currentTime;

  return true;
}

void destroyGame(Game* game) {
  if (game != NULL) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    free(game);
  }
}
