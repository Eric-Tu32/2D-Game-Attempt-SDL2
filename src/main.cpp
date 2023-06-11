#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Player.hpp"

void init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init failed: "<< SDL_GetError() << std::endl;
}

RenderWindow window("GAME", 1280, 720);
bool gameRunning = true;

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

SDL_Event event;

SDL_Texture* playerTexture = window.loadTexture("res/gfx/player.png");

Player player(Vector2f(500,300), playerTexture, 2, 0.5f);

void update()
{
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency());

	bool up_button_down = false;
	bool down_button_down = false;
	bool left_button_down = false;
	bool right_button_down = false;

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W]) up_button_down = true;
	if (state[SDL_SCANCODE_A]) left_button_down = true;
	if (state[SDL_SCANCODE_S]) down_button_down = true;
	if (state[SDL_SCANCODE_D]) right_button_down = true;

	//Get our controls and events
	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		}
	}

	player.update(deltaTime, left_button_down, right_button_down, up_button_down, down_button_down);
}

void graphics()
{
	window.clear();
	//window.render(0, 0, bgTexture);
	
	window.render(player);
	window.display();
}

int main(int argc, char* args[ ])
{
	while (gameRunning)
	{
		update();
		graphics();
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}