#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <chrono>

#include "Player.hpp"

Player::Player(Vector2f p_pos, SDL_Texture* p_tex, float p_scale, float p_velocity)
:Entity(p_pos, p_tex, p_scale)
{
	velocity = p_velocity;
	sprint_available = true;
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

void Player::update(double deltaTime, bool left_button_down, bool right_button_down, bool up_button_down, bool down_button_down, bool left_mouse_down, bool right_mouse_down, Vector2f player_to_mouse)
{
	direction.x = 0;
	direction.y = 0;
	setAngle((atan2(player_to_mouse.x ,-player_to_mouse.y) * 180.0d) / 3.1416d);

	Vector2f newPos;

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

	if (left_mouse_down)
	{	
		current_timestamp = std::chrono::steady_clock::now();
		if (sprint_available)
		{
			sprint_timestamp = std::chrono::steady_clock::now();
			std::cout << "sprint!" << '\n';
			newPos.x += 100.0d*direction.x;
			newPos.y += 100.0d*direction.y;
			sprint_available = false;
		} else
		{
			if (std::chrono::duration_cast<std::chrono::milliseconds>(current_timestamp - sprint_timestamp).count() >= 3000)
			{
				sprint_available = true;
			}
		}
	}

	if (right_mouse_down)
	{
		direction.x = (float) direction.x / 2.0f;
		direction.y = (float) direction.y / 2.0f;
	}

	newPos.x += getPos().x + getDirection().x * getVelocity() * deltaTime;
	newPos.y += getPos().y + getDirection().y * getVelocity() * deltaTime;
	setPos(newPos.x, newPos.y);
}