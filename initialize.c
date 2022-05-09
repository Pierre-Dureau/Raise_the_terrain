#include "demo.h"

/**
 * Init_instance - Initialize the SDL window and her renderer
 *
 * @instance: Instance
 * Return: 0, 1 if error
 */

int Init_instance(SDL_Instance *instance)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable ot initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

	instance->window = SDL_CreateWindow("Raise the terrain",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, 0);

	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	instance->renderer = SDL_CreateRenderer(instance->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CREATERenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	return (0);
}

/**
 * InitialiseGrid - Initialize a grid
 *
 * @grid: The grid
 */

void InitialiseGrid(SDL_Point grid[8][8])
{
	int i, j, x, y;

	for (x = 150, i = 0; x <= 850; x += 100, i++)
	{
		for (y = 50, j = 0; y <= 750; y += 100, j++)
		{
			grid[i][j].x = x;
			grid[i][j].y = y;
		}
	}
}
