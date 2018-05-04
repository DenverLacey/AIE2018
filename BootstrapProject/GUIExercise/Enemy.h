#pragma once
#include <Renderer2D.h>
#include "Bullet.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Update(float time, float speed);

	void Draw(aie::Renderer2D* rend);

	float GetPosX();
	float GetPosY();
	void SetPos(const float posX, const float posY);

	int GetWidth();
	int GetHeight();

	bool GetActive();
	void SetActive(const bool newState);

private:
	aie::Texture* e_texture;

	float e_posX;
	float e_posY;

	bool isActive;
};

