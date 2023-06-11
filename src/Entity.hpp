#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex, float p_scale);
	Vector2f& getPos()
	{
		return pos;
	}
	void setPos(float x, float y);
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	float getScale();
private:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	float scale;
};