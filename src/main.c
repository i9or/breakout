#include <stdlib.h>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "game.h"

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());

    return SDL_APP_FAILURE;
  }

  Game* game = createGame(1280, 1024);
  if (!game) {
    return SDL_APP_FAILURE;
  }

  *appstate = game;

  if (!initGame(game)) {
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
  switch (event->type) {
  case SDL_EVENT_KEY_DOWN:
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  default:
    break;
  }

  return SDL_APP_CONTINUE;
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
SDL_AppResult SDL_AppIterate(void* appstate) {
  const Game* game = appstate;

  const char* message = "Breakout";
  int w = 0, h = 0;
  const float scale = 4.f;

  SDL_GetRenderOutputSize(game->renderer, &w, &h);
  SDL_SetRenderScale(game->renderer, scale, scale);
  const float x = ((float)w / scale -
                   SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) /
                  2;
  const float y = ((float)h / scale - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;

  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
  SDL_RenderClear(game->renderer);
  SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
  SDL_RenderDebugText(game->renderer, x, y, message);
  SDL_RenderPresent(game->renderer);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
  Game* game = appstate;
  destroyGame(game);
}
