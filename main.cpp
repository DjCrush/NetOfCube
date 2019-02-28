#include <SDL.h>  // SDL 1.2.15
#include <vector>
#include "Graphics.h"
#include "Mesh.h"
using namespace std;

int wmain(int argc, wchar_t *argv[], wchar_t *envp[])
{
	SDL_Event event;
	SDL_Surface* screen = NULL;
	int keypress{};
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
	if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE)))
	{
		SDL_Quit();
		return 1;
	}
	Mesh cube(screen);
	while (!keypress)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				keypress = 1;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_SPACE:
					cube.event();
				}
			}
		}
		clearScreen(screen);
		cube.draw();
		SDL_Flip(screen);
	}
	SDL_FreeSurface(screen);
	SDL_Quit();
	return 0;
}
