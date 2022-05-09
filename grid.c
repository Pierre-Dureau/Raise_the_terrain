#include "demo.h"

/**
 * IsometricGrid - Convert a rotated grid in a isometric one
 *
 * @grid: The grid
 * @altitudes: The Z of the grid
 */

void IsometricGrid(SDL_Point grid[8][8], int altitudes[8][8])
{
	int wx, wy, i, j;

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			wx = 0.65 * grid[i][j].x - 0.65 * grid[i][j].y + 430;
			wy = (1 - 0.65) * grid[i][j].x + (1 - 0.65) * grid[i][j].y
				- altitudes[j][i] + 100;
			grid[i][j].x = wx;
			grid[i][j].y = wy;
		}
	}
}

/**
 * AltitudesGrid - Transform file infos in a grid containing Z values
 *
 * @altitudes: The grid
 * @argv: name of the file
 */

void AltitudesGrid(int altitudes[8][8], char **argv)
{
	FILE *fp;
	char line[1000];
	char *word;
	int i = 0, j;

	fp = fopen(argv[1], "r");

	while (fgets(line, 1000, fp) != NULL)
	{
		word = strtok(line, " ");
		for (j = 0; j < 8; j++)
		{
			altitudes[i][j] = atoi(word);
			word = strtok(NULL, " ");
		}
		i++;
	}

	fclose(fp);
}

/**
 * RotateGrid - Rotate a grid
 *
 * @grid: The grid
 * @rotgrid: The grid rotated
 * @altitudes: Z values
 * @a: angle in radiants
 * @instance: Instance
 */

void RotateGrid(SDL_Point grid[8][8], SDL_Point rotgrid[8][8],
	int altitudes[8][8], float a, SDL_Instance instance)
{
	int i, j, rx, ry;

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			rx = (grid[i][j].x - 500) * cos(a) - (grid[i][j].y - 400) * sin(a) + 500;
			ry = (grid[i][j].x - 500) * sin(a) + (grid[i][j].y - 400) * cos(a) + 400;

			rotgrid[i][j].x = rx;
			rotgrid[i][j].y = ry;
		}
	}
	IsometricGrid(rotgrid, altitudes);
	DrawGrid(instance, rotgrid);
}

/**
 * CopyGrid - Copy a grid
 *
 * @grid: First grid
 * @rotgrid: Second grid
 */

void CopyGrid(SDL_Point grid[8][8], SDL_Point rotgrid[8][8])
{
	int i, j;

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			rotgrid[i][j].x = grid[i][j].x;
			rotgrid[i][j].y = grid[i][j].y;
		}
	}
}

/**
 * DrawGrid - Draw a grid in the SDL window
 *
 * @instance: Instance
 * @grid: The grid
 */

void DrawGrid(SDL_Instance instance, SDL_Point grid[8][8])
{
	int i, j;

	SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 7; j++)
			SDL_RenderDrawLine(instance.renderer, grid[j][i].x, grid[j][i].y,
				grid[j + 1][i].x, grid[j + 1][i].y);
	}
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 7; j++)
			SDL_RenderDrawLine(instance.renderer, grid[i][j].x, grid[i][j].y,
				grid[i][j + 1].x, grid[i][j + 1].y);
	}
	SDL_RenderPresent(instance.renderer);
}
