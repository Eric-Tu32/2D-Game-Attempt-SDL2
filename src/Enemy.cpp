#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <chrono>

#include "Enemy.hpp"

Enemy::Enemy(Vector2f p_pos, SDL_Texture* p_tex, float p_scale, float p_velocity)
:Entity(p_pos, p_tex, p_scale)
{
	velocity = p_velocity;
	attack_available = true;
	direction.x = 0.0f;
	direction.y = 0.0f;
}

float Enemy::getVelocity()
{
	return velocity;
}

void Enemy::setVelocity(float v)
{
	velocity = v;
}

Vector2f Enemy::getDirection()
{
	return direction;
}

void Enemy::setDirection(float x, float y)
{
	direction.x = x;
	direction.y = y;
}

void Enemy::update(double deltaTime, Vector2f enemy_to_player, bool isHit)
{
	direction.x = enemy_to_player.x / (float) sqrt(enemy_to_player.x*enemy_to_player.x + enemy_to_player.y*enemy_to_player.y);
	direction.y = enemy_to_player.y / (float) sqrt(enemy_to_player.x*enemy_to_player.x + enemy_to_player.y*enemy_to_player.y);
	setAngle((atan2(enemy_to_player.x ,-enemy_to_player.y) * 180.0d) / 3.1416d);

	Vector2f newPos;

	newPos.x += getPos().x + getDirection().x * getVelocity() * deltaTime;
	newPos.y += getPos().y + getDirection().y * getVelocity() * deltaTime;
	setPos(newPos.x, newPos.y);
}