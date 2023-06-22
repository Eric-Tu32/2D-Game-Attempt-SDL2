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
	double getAngle();
	void setAngle(double x);
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	float getScale();
protected:
	Vector2f pos;
	double angle;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	float scale;
};