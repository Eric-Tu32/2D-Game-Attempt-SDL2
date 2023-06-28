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

	textureWidth = size.x;
	textureHeight = size.y;

	hitBox.x = 0;
	hitBox.y = 0;
	hitBox.w = 0;
	hitBox.h = 0; 
}

Vector2f& Entity::getPos()
{
	return pos;
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

void Entity::setHitBox(SDL_Rect p_hitBox)
{
	hitBox = p_hitBox;
}

SDL_Rect Entity::getHitBox()
{
	hitBox.x = pos.x;
	hitBox.y = pos.y;
	hitBox.w = textureWidth * scale;
	hitBox.h = textureHeight * scale; 

	return hitBox;
}

SDL_bool Entity::isHit(Entity* obj)
{
	hitBox.x = pos.x;
	hitBox.y = pos.y;
	hitBox.w = textureWidth * scale;
	hitBox.h = textureHeight * scale; 

	SDL_bool isCollided;

	SDL_Rect objhitbox = obj->getHitBox();

	const SDL_Rect* selfhitboxptr = &hitBox;
	const SDL_Rect* objhitboxptr = &objhitbox;

	SDL_Rect inter;
	inter.x = 0;
	inter.y = 0;
	inter.w = 0;
	inter.h = 0;

	isCollided = SDL_IntersectRect(selfhitboxptr, objhitboxptr, &inter);

	return isCollided;
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