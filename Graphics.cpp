#include "Graphics.h"

const int WIDTH = 1600;
const int HEIGHT = 800;
const int BPP = 4;
const int DEPTH = 32;
const double PI = 3.1415926535897932384626433832795f;

void clearScreen(SDL_Surface *screen)
{
	SDL_Rect d = { 0,0, WIDTH, HEIGHT };
	SDL_FillRect(screen, &d, 75);
}

inline void drawPixel(SDL_Surface *screen, int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		Uint32 *pixmem32;
		Uint32 colour;
		int ytimesw = y * screen->pitch / BPP;
		colour = SDL_MapRGB(screen->format, red, green, blue);
		pixmem32 = (Uint32*)screen->pixels + ytimesw + x;
		*pixmem32 = colour;
	}
}

void drawLine(SDL_Surface* screen, int x1, int y1, int x2, int y2, Uint8 red, Uint8 green, Uint8 blue)
{
	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	drawPixel(screen, x2, y2, red, green, blue);
	while (x1 != x2 || y1 != y2)
	{
		drawPixel(screen, x1, y1, red, green, blue);
		const int error2 = error << 1;
		if (error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}
}

void drawCircle(SDL_Surface* screen, int x0, int y0, int radius, Uint8 red, Uint8 green, Uint8 blue)
{
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while (y >= 0) {
		drawPixel(screen, x0 + x, y0 + y, red, green, blue);
		drawPixel(screen, x0 + x, y0 - y, red, green, blue);
		drawPixel(screen, x0 - x, y0 + y, red, green, blue);
		drawPixel(screen, x0 - x, y0 - y, red, green, blue);
		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if (delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}
