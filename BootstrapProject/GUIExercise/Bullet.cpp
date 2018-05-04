#include "Bullet.h"
#include <Texture.h>
#include <Renderer2D.h>



Bullet::Bullet()
{
	b_texture = new aie::Texture("../bin/textures/BootstrapAssignmentSprites/Bullet/Bullet(1).png");


	b_posX = 0.0f;
	b_posY = 0.0f;

	isActive = false;
}


Bullet::~Bullet()
{
	if (b_texture != nullptr)
	{
		delete b_texture;
	}
}

void Bullet::Update(float time)
{
	if (isActive) {
		b_posX += 700.0f * time;
	}
	else {
		b_posX = 1290.0f;
		b_posY = 0.0f;
	}

	if (b_posX > 1280) {
		isActive = false;
	}
}

void Bullet::Draw(aie::Renderer2D* rend)
{
	if (isActive) {
		rend->drawSprite(b_texture, b_posX, b_posY, 50.0f, 30.0f);
	}
}

void Bullet::SetPos(float posX, float posY)
{
	b_posX = posX;
	b_posY = posY;
}

float Bullet::GetPosX()
{
	return b_posX;
}

float Bullet::GetPosY()
{
	return b_posY;
}

bool Bullet::GetActive()
{
	return isActive;
}

void Bullet::SetActive(const bool newState)
{
	isActive = newState;
}

int Bullet::GetWidth()
{
	return b_texture->getWidth();
}

int Bullet::GetHeight()
{
	return b_texture->getHeight();
}
