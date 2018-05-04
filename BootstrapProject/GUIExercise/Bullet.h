#pragma once
#include <Renderer2D.h>
#include <Texture.h>

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Update(float time);

	void Draw(aie::Renderer2D* rend);

	void SetPos(float b_posX, float b_posY);

	float GetPosX();
	float GetPosY();

	bool GetActive();
	void SetActive(const bool newState);

	int GetWidth();
	int GetHeight();

private:
	aie::Texture* b_texture;
	
	float b_posX;
	float b_posY;

	bool isActive;
};

