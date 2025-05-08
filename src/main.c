#include <stdlib.h>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "game.h"

#include <stdio.h>

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());

    return SDL_APP_FAILURE;
  }

  Game* game = createGame(1024, 768);
  if (!game) {
    return SDL_APP_FAILURE;
  }

  *appstate = game;

  if (!initGame(game)) {
    return SDL_APP_FAILURE;
  }

  // TODO: Remove debug code
  SDL_Surface* surface = NULL;
  char bmpPath[256];
  sprintf(bmpPath, "%s../assets/images/mushroom.bmp", SDL_GetBasePath());
  surface = SDL_LoadBMP(bmpPath);
  if (!surface) {
    SDL_Log("Couldn't load bitmap: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  const Uint32 colorKey = SDL_MapSurfaceRGB(surface, 255, 0, 255);
  SDL_SetSurfaceColorKey(surface, true, colorKey);

  game->mushroomTexture = SDL_CreateTextureFromSurface(game->renderer, surface);
  if (!game->mushroomTexture) {
    SDL_Log("Couldn't create mushroom texture: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_SetTextureScaleMode(game->mushroomTexture, SDL_SCALEMODE_NEAREST);

  SDL_DestroySurface(surface);
  // End of TODO

  return SDL_APP_CONTINUE;
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
  switch (event->type) {
  case SDL_EVENT_KEY_DOWN:
    if (event->key.scancode == SDL_SCANCODE_ESCAPE) {
      return SDL_APP_SUCCESS;
    }
    break;

  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;

  default:
    break;
  }

  return SDL_APP_CONTINUE;
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
SDL_AppResult SDL_AppIterate(void* appstate) {
  Game* game = appstate;

  // Calculate delta time
  game->currentTime = SDL_GetPerformanceCounter();
  float deltaTime = (float)(game->currentTime - game->lastTime) / (float)game->frequency;

  if (deltaTime > 0.25f) {
    deltaTime = 0.25f;
  }

  game->accumulator += deltaTime;

  // Update
  while (game->accumulator >= FIXED_TIME_STEP) {
    game->mushroomPosition = vec2Add(game->mushroomPosition,
                                     vec2Multiply(game->mushroomVelocity,
                                                  FIXED_TIME_STEP));

    const float x = game->mushroomPosition.x;
    const float y = game->mushroomPosition.y;
    const float w = (float)game->mushroomTexture->w;
    const float h = (float)game->mushroomTexture->h;

    if (x + w > (float)game->windowWidth ||
        x < 0.f) {
      game->mushroomVelocity.x *= -1.f;
    }

    if (y + h > (float)game->windowHeight ||
        y < 0.f) {
      game->mushroomVelocity.y *= -1.f;
    }

    game->accumulator -= FIXED_TIME_STEP;
  }

  // Render
  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
  SDL_RenderClear(game->renderer);

  float currX = game->mushroomPosition.x;
  float currY = game->mushroomPosition.y;
  game->mushroomRect.x = currX;
  game->mushroomRect.y = currY;
  game->mushroomRect.w = (float)game->mushroomTexture->w;
  game->mushroomRect.h = (float)game->mushroomTexture->h;
  SDL_RenderTexture(game->renderer, game->mushroomTexture, NULL, &game->mushroomRect);

  SDL_RenderPresent(game->renderer);

  SDL_Delay(1);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
  Game* game = appstate;
  destroyGame(game);
}
