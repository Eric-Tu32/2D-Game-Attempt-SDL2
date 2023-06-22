#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>

#include "Math.hpp"
#include "Entity.hpp"

class Enemy : public Entity
{
public:
	Enemy(Vector2f p_pos, SDL_Texture* p_tex, float p_scale, float p_velocity);
	float getVelocity();
	void setVelocity(float v);
	Vector2f getDirection();
	void setDirection(float x, float y);
	void update(double deltaTime, Vector2f enemy_to_player, bool isHit);
  
private:
	float velocity;
	std::chrono::steady_clock::time_point attack_timestamp;
	std::chrono::steady_clock::time_point current_timestamp;
	bool attack_available;
	Vector2f direction;
};