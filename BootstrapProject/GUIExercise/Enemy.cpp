#include "Enemy.h"
#include <Renderer2D.h>
#include <Texture.h>
#include <iostream>


Enemy::Enemy()
{
	e_texture = new aie::Texture("../bin/textures/BootstrapAssignmentSprites/Enemy/Enemy(1).png");

	//initialise enemies as deactivated
	isActive = false;
}


Enemy::~Enemy()
{
	if (e_texture != nullptr) {
		delete e_texture;
	}
}

void Enemy::Update(float time, float speed)
{
	//if enemy is active. move toward player
	if (isActive) {
		e_posX -= speed * time;
	}
	else {
		//dump inactive enemies outside the screen
		e_posX = 800.0f;
		e_posY = 1300.0f;
	}

	//if enemy reaches the edge of screen, deactive
	if (e_posX < -150.0f) {
		isActive = false;
	}
}

void Enemy::Draw(aie::Renderer2D* rend)
{
	if (isActive) {
		rend->drawSprite(e_texture, e_posX, e_posY, 150, 100);
	}
}

float Enemy::GetPosX()
{
	return e_posX;
}

float Enemy::GetPosY()
{
	return e_posY;
}

void Enemy::SetPos(const float posX, const float posY)
{
	e_posX = posX;
	e_posY = posY;
}

int Enemy::GetWidth()
{
	return e_texture->getWidth();
}

int Enemy::GetHeight()
{
	return e_texture->getHeight();
}

bool Enemy::GetActive()
{
	return isActive;
}

void Enemy::SetActive(const bool newState)
{
	isActive = newState;
}

