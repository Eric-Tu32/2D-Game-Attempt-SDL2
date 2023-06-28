#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex, float p_scale);
	Vector2f& getPos();
	void setPos(float x, float y);

	double getAngle();
	void setAngle(double x);

	void setHitBox(SDL_Rect p_hitBox);
	SDL_Rect getHitBox();
	SDL_bool isHit(Entity* obj);

	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	float getScale();
protected:
	Vector2f pos;
	double angle;
	SDL_Rect currentFrame;
	SDL_Rect hitBox;
	SDL_Texture* tex;
	int textureWidth;
	int textureHeight;
	float scale;
};