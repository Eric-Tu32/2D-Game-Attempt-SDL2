#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Player.hpp"

Player::Player(Vector2f p_pos, SDL_Texture* p_tex, float p_scale, float p_velocity)
:Entity(p_pos, p_tex, p_scale)
{
	velocity = p_velocity;
	direction.x = 0.0f;
	direction.y = 0.0f;
}

float Player::getVelocity()
{
	return velocity;
}

void Player::setVelocity(float v)
{
	velocity = v;
}

Vector2f Player::getDirection()
{
	return direction;
}

void Player::setDirection(float x, float y)
{
	direction.x = x;
	direction.y = y;
}

void Player::update(double deltaTime, bool left_button_down, bool right_button_down, bool up_button_down, bool down_button_down)
{
	direction.x = 0;
	direction.y = 0;

	if (left_button_down)
	{
		direction.x -= 1;
	}
	if (right_button_down)
	{
		direction.x += 1;
	}
	if (up_button_down)
	{
		direction.y -= 1;
	}
	if (down_button_down)
	{
		direction.y += 1;
	}
	if (direction.x != 0 && direction.y != 0)
	{
		direction.x = (float) direction.x / 1.414f;
		direction.y = (float) direction.y / 1.414f;
	}

	Vector2f newPos;
	newPos.x = getPos().x + getDirection().x * getVelocity() * deltaTime;
	newPos.y = getPos().y + getDirection().y * getVelocity() * deltaTime;
	setPos(newPos.x, newPos.y);
}