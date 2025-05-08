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
	game->mushroomPosition = (Vec2){.x = 0.f, .y = 0.f};
	game->mushroomVelocity = (Vec2){.x = 0.f, .y = 0.f};

	game->currentTime = 0;
	game->lastTime = 0;
	game->frequency = 0;
	game->accumulator = 0.f;

	return game;
}

bool initGame(Game* game) {
	const SDL_DisplayID di = SDL_GetPrimaryDisplay();
	float scale = SDL_GetDisplayContentScale(di);
	if (scale < 1.f) {
		scale = 1.f;
	}

	if (!SDL_CreateWindowAndRenderer("Breakout",
																	 game->windowWidth * (int)scale,
																	 game->windowHeight * (int)scale,
																	 0,
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
	game->mushroomVelocity = (Vec2){.x = 5.f, .y = 5.f};

	game->accumulator = 0.f;
	game->currentTime = SDL_GetPerformanceCounter();
	game->frequency = SDL_GetPerformanceFrequency();
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
