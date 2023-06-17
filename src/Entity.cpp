#include "Entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, float p_scale)
:pos(p_pos), tex(p_tex), scale(p_scale)
{
	angle = 0.0d;

	SDL_Point size;
    SDL_QueryTexture(p_tex, NULL, NULL, &size.x, &size.y);

	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = size.x;
	currentFrame.h = size.y;
}

void Entity::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

void Entity::setAngle(double x)
{
	angle = x;
}

double Entity::getAngle()
{
	return angle;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

float Entity::getScale()
{
	return scale;
}