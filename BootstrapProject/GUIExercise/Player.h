#pragma once
#include <Renderer2D.h>
#include <Texture.h>
#include <Input.h>
#include "Enemy.h"

class Player : public Bullet, public Enemy
{
public:
	Player();
	~Player();

	void Update(float time, aie::Input* in);

	void Draw(aie::Renderer2D* rend);

	void SetPlaneSpeed(float speed);
	float GetPlaneSpeed();

	void SetE_freq(int& freq);
	int GetE_freq();

	int GetScore();

	void Hell(float& displaySpeed);

	float GetE_speed();
	void SetE_speed(float& speed);

	int GetWidth();
	int GetHeight();

	void CollisionCheck();

private:
	aie::Texture* m_texture;
	int m_score;

	float m_posX;
	float m_posY;

	float b_timer;
	float e_timer;

	float m_bulletOffsetX;
	float m_bulletOffsetY;

	float m_planeSpeed;

	Bullet* b_array[15];
	int b_counter;

	Enemy* e_array[15];
	int e_counter;
	int e_freq;
	float e_speed;
	bool seedSet;
};