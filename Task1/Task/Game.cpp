#include "stdafx.h"

#include "Game.h"

Game* Game::instance = 0;

bool Game::init(const char* title, int x, int y, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init successful..." << std::endl;

		window = SDL_CreateWindow(title, x, y, width, height, flags);

		if (window != 0)
		{
			std::cout << "Window creation successful..." << std::endl;

			renderer = SDL_CreateRenderer(window, -1, 0);

			if (renderer != 0)
			{
				std::cout << "Renderer creation successful..." << std::endl;

				SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
			}
			else
			{
				std::cout << "Renderer creation failed!!!" << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "Window creation failed!!!" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "SDL init failed!!!" << std::endl;
		return false;
	}

	std::cout << "Complete init successful..." << std::endl;

	running = true;

	return true;
}

void Game::render()
{
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void Game::update()
{

}

void Game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			quit();
		}
	}
}

void Game::clean()
{
	std::cout << "Cleaning Game" << std::endl;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::quit()
{
	running = false;
}