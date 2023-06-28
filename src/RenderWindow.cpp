#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (window == NULL)
		std::cout << "Window failed to init: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL) std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity* p_entity)
{
	SDL_Rect src; 

	src.x = p_entity->getCurrentFrame().x;
	src.y = p_entity->getCurrentFrame().y;
	src.w = p_entity->getCurrentFrame().w;
	src.h = p_entity->getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity->getPos().x;
	dst.y = p_entity->getPos().y;
	dst.w = p_entity->getCurrentFrame().w * p_entity->getScale();
	dst.h = p_entity->getCurrentFrame().h * p_entity->getScale();

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	SDL_RenderCopyEx(renderer, p_entity->getTex(), &src, &dst, p_entity->getAngle(), NULL, flip);
}

void RenderWindow::render(int p_x, int p_y, SDL_Texture* p_tex)
{	
    SDL_Point size;
    SDL_QueryTexture(p_tex, NULL, NULL, &size.x, &size.y);

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	//dst.w = size.x;
	//dst.h = size.y;
	dst.w = 1280;
	dst.h = 720;

	SDL_RenderCopy(renderer, p_tex, NULL, &dst);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}