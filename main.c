#include "demo.h"

/**
 * poll_events - Check for action from keyboard
 *
 * @instance: Instance
 * @a: angle in radiants
 * @angle: angle in degrees
 * @grid: Grid flat
 * @rotgrid: Grid with rotation
 * @altitudes: Z of the points
 * Return: 0, 1 if error
 */

int poll_events(SDL_Instance instance, float a, int *angle,
	SDL_Point grid[8][8], SDL_Point rotgrid[8][8], int altitudes[8][8])
{
	SDL_Event event;
	SDL_KeyboardEvent key;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				return (1);
			case SDL_KEYDOWN:
				key = event.key;
				if (key.keysym.scancode == 0x29)
					return (1);
				if (event.key.keysym.sym == SDLK_RIGHT
					|| event.key.keysym.sym == SDLK_LEFT)
				{
					if (event.key.keysym.sym == SDLK_LEFT)
						*angle += 1;
					else
						*angle -= 1;
					a = *angle * M_PI / 180;

					SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
					SDL_RenderClear(instance.renderer);
					RotateGrid(grid, rotgrid, altitudes, a, instance);
				}
				break;
		}
	}
	return (0);
}

/**
 * main - Isometric Projection using SDL2
 *
 * @argc: Number of arguments
 * @argv: Arguments
 * Return: 0, 1 if error
 */

int main(int argc, char **argv)
{
	SDL_Instance instance;
	SDL_Point grid[8][8], rotgrid[8][8];
	int altitudes[8][8];
	int quit = 0, angle = 0;
	float a;

	if (argc != 2)
	{
		printf("Usage: ./terrain file\n");
		return (1);
	}
	AltitudesGrid(altitudes, argv);

	if (Init_instance(&instance) != 0)
		return (1);

	SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
	SDL_RenderClear(instance.renderer);


	InitialiseGrid(grid);
	CopyGrid(grid, rotgrid);
	IsometricGrid(rotgrid, altitudes);
	DrawGrid(instance, rotgrid);

	while ("C is awesome")
	{
		if (poll_events(instance, a, &angle, grid, rotgrid, altitudes) == 1)
			break;
	}

	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}
