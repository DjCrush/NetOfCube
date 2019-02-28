#pragma once
#include <SDL.h>

extern const int WIDTH;
extern const int HEIGHT;
extern const int BPP;
extern const int DEPTH;
extern const double PI;

void clearScreen(SDL_Surface* screen);
inline void drawPixel(SDL_Surface *screen, int x, int y, Uint8 red, Uint8 green, Uint8 blue);
void drawLine(SDL_Surface* screen, int x1, int y1, int x2, int y2, Uint8 red, Uint8 green, Uint8 blue);
void drawCircle(SDL_Surface* screen, int x0, int y0, int radius, Uint8 red, Uint8 green, Uint8 blue);
