#ifndef DEMO_H
#define DEMO_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

/**
 * struct SDL_Instance - Instance of the window
 *
 * @window: Window
 * @renderer: Renderer
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

int Init_instance(SDL_Instance *);
void InitialiseGrid(SDL_Point grid[8][8]);

void IsometricGrid(SDL_Point grid[8][8], int altitudes[8][8]);
void AltitudesGrid(int grid[8][8], char **argv);
void RotateGrid(SDL_Point grid[8][8], SDL_Point rotgrid[8][8],
	int altitudes[8][8], float a, SDL_Instance instance);
void CopyGrid(SDL_Point grid[8][8], SDL_Point rotgrid[8][8]);
void DrawGrid(SDL_Instance instance, SDL_Point grid[8][8]);

#endif /* DEMO_H */
