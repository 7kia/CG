#include "stdafx.h"

#include "Game.h"

const int FPS = 60;
const float DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
	Uint32 frameStart, frameTime;

	if (_Game::Instance()->init("SDL Practice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 640, SDL_WINDOW_SHOWN))
	{
		std::cout << "Game init succeeded" << std::endl;

		while (_Game::Instance()->isRunning())
		{
			frameStart = SDL_GetTicks();

			_Game::Instance()->update();
			_Game::Instance()->handleEvents();
			_Game::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}

	}
	else
	{
		std::cout << "game init failed" << SDL_GetError() << std::endl;
		return -1;
	}

	_Game::Instance()->clean();

	return 0;
}