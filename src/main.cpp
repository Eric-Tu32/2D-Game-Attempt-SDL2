#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

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

//Load textures
SDL_Texture* playerTexture = window.loadTexture("res/gfx/player.png");
SDL_Texture* bgTexture = window.loadTexture("res/gfx/bgTexture.png");

Player player(Vector2f(500,300), playerTexture, 2, 0.5f);

void update()
{
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency());

	//keyboard detection
	bool up_button_down = false;
	bool down_button_down = false;
	bool left_button_down = false;
	bool right_button_down = false;

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W]) up_button_down = true;
	if (state[SDL_SCANCODE_A]) left_button_down = true;
	if (state[SDL_SCANCODE_S]) down_button_down = true;
	if (state[SDL_SCANCODE_D]) right_button_down = true;

	//mouse detection (1-left key, 3-right key)
	int mouse_x, mouse_y;
	bool left_mouse_down = false;
	bool right_mouse_down = false;
	if(SDL_GetMouseState(&mouse_x,&mouse_y) & 1) left_mouse_down = true;
	if(SDL_GetMouseState(&mouse_x,&mouse_y) & 4) right_mouse_down = true;

	//player angle
	Vector2f player_to_mouse;
	if (mouse_x != 0 || mouse_y != 0)
	{
		player_to_mouse.x = mouse_x - (double)(player.getPos().x + player.getCurrentFrame().w / 2.0d * player.getScale());
		player_to_mouse.y = mouse_y - (double)(player.getPos().y + player.getCurrentFrame().h / 2.0d * player.getScale());
	}
		
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

	player.update(deltaTime, left_button_down, right_button_down, up_button_down, down_button_down, left_mouse_down, right_mouse_down, player_to_mouse);
}

void graphics()
{
	window.clear();
	window.render(0, 0, bgTexture);
	
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