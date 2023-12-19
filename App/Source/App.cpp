#include <iostream>

#include <SDL.h>

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

int main(int agrc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not be initialized: " << SDL_GetError() << std::endl;
		return 0;
	}

	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (!window)
	{
		std::cout << "Could not create a window." << std::endl;
		return 0;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer)
	{
		std::cout << "Could not create a renderer." << std::endl;
		return 0;
	}

	bool gameIsRunning = true;
	while (gameIsRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameIsRunning = false;
		}
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();

	return 0;
}