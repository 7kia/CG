#pragma once

#include <SDL.h>
#include <iostream>
#include <string>

class Game
{
public:

	static Game* Instance()
	{
		if (instance == 0)
		{
			instance = new Game();
		}

		return instance;
	}

	bool init(const char* title, int x, int y, int width, int height, int flags);

	void update();
	void handleEvents();
	void render();
	void clean();
	void quit();

	bool isRunning() { return running; }
	SDL_Window* getWindow() const { return window; }
	SDL_Renderer* getRenderer() const { return renderer; }

private:

	static Game* instance;

	Game() {}
	~Game() {}

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool running;

};

typedef Game _Game;