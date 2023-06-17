#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"
#include "Entity.hpp"

class Player : public Entity
{
public:
	Player(Vector2f p_pos, SDL_Texture* p_tex, float p_scale, float p_velocity);
	float getVelocity();
	void setVelocity(float v);
	Vector2f getDirection();
	void setDirection(float x, float y);
	void update(double deltaTime, bool left_button_down, bool right_button_down, bool up_button_down, bool down_button_down, bool left_mouse_down, bool right_mouse_down, Vector2f player_to_mouse);
private:
	float velocity;
	Vector2f direction;
};