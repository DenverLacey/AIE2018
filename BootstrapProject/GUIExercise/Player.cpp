#include "Player.h"
#include "Texture.h"
#include <imgui.h>
#include <Application.h>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>
#include <Windows.h>


Player::Player()
{
	//set the plane texture to the player
	m_texture = new aie::Texture("../bin/textures/BootstrapAssignmentSprites/Plane/Fly(1).png");
	m_score = 0;

	//set plane's position
	m_posX = 320.0f;
	m_posY = 360.0f;

	//offset bullet spawn so it lines up with the plane's gun
	m_bulletOffsetX = 15.0f;
	m_bulletOffsetY = -16.0f;

	//set speeds for plane and enemy
	m_planeSpeed = 450.0f;
	e_speed = 500.0f;

	//initialise bullet and enemy counters
	b_counter = 0;
	e_counter = 0;

	//bullet initialisations
	for (int i = 0; i < 15; ++i) {
		Bullet* newBullet = new Bullet();
		b_array[i] = newBullet;
	}

	assert(b_array[0] != nullptr);

	//enemy initialisations
	for (int i = 0; i < 15; ++i) {
		Enemy* newEnemy = new Enemy();
		e_array[i] = newEnemy;
	}

	assert(e_array[0] != nullptr);

	//initialse enemy frequency
	e_freq = 3;

	//initialise bullet and enemy spawn timers
	b_timer = 0.0f;
	e_timer = 0.0f;

	//initialise seedSet
	seedSet = false;
}

Player::~Player()
{
	delete m_texture;
	
	//delete b_array
	for (int i = 0; i < 15; ++i) {
		delete b_array[i];
	}

	//delete e_array
	for (int i = 0; i < 15; ++i) {
		delete e_array[i];
	}
}

void Player::Update(float deltaTime, aie::Input* in)
{
	//run timers
	b_timer += deltaTime;
	e_timer += deltaTime;

	//set srand once
	if (!seedSet) {
		srand((unsigned)time(nullptr));
		seedSet = true;
	}

	//reset e_coutner
	if (e_counter >= 14) {
		e_counter = 0;
	}

	//Enemy spawn
	if (e_timer > (6 - e_freq)) {
		if (e_array[e_counter] != nullptr && e_array[e_counter]->GetActive() == false) {
			//spawn enemy at a random y coordinate
			e_array[e_counter]->SetPos(1350.0f, (float)(10 + (rand()) % (710 - 10 + 1)));
			
			//Activate the enemy
			e_array[e_counter]->SetActive(true);

			//increment counter & reset timer
			++e_counter;
			e_timer = 0.0f;
		}
	}

	//update enemies
	for (int i = 0; i < 15; ++i) {
		e_array[i]->Update(deltaTime, e_speed);
		
		//If enemy gets past the player decrement score
		if (e_array[i]->GetPosX() <= -150) {
			--m_score;
		}
	}

	//sets the arrow keys to control the plane position
	if (in->isKeyDown(aie::INPUT_KEY_W)) {
		if (m_posY <= 719) {
			m_posY += m_planeSpeed * deltaTime;
		}
	}
	if (in->isKeyDown(aie::INPUT_KEY_S)) {
		if (m_posY >= 0) {
			m_posY -= m_planeSpeed * deltaTime;
		}
	}
	if (in->isKeyDown(aie::INPUT_KEY_D)) {
		if (m_posX <= 1279) {
			m_posX += m_planeSpeed * deltaTime;
		}
	}
	if (in->isKeyDown(aie::INPUT_KEY_A)) {
		if (m_posX >= 0) {
			m_posX -= m_planeSpeed * deltaTime;
		}
	}

	//reset b_coutner
	if (b_counter >= 14) {
		b_counter = 0;
	}

	//shoot
	if (b_timer > 0.4f) {
		if (in->isKeyDown(aie::INPUT_KEY_SPACE)) {
			if (b_array[b_counter] != nullptr && b_array[b_counter]->GetActive() == false) {
				//set bullet spawn location
				b_array[b_counter]->SetPos(m_posX + m_bulletOffsetX, m_posY + m_bulletOffsetY);
			
				//activate the bullet
				b_array[b_counter]->SetActive(true);
				
				//increment counter and reset timer
				++b_counter;
				b_timer = 0.0f;
			}
		}
	}

	//update bullets
	for (int i = 0; i < 15; ++i) {
		b_array[i]->Update(deltaTime);
	}

	//detect collisions
	CollisionCheck();

	//draw score
	ImGui::Begin("");
	ImGui::Text("Score: %i", m_score);
	ImGui::End();
}

//draws the player when given the renderer from the game
void Player::Draw(aie::Renderer2D* rend)
{
	//plane
	rend->drawSprite(m_texture, m_posX, m_posY, 100, 75);

	//bullets
	for (int i = 0; i < 15; ++i) {
		b_array[i]->Draw(rend);
	}

	//enemies
	for (int i = 0; i < 15; ++i) {
		e_array[i]->Draw(rend);
	}
}

void Player::SetPlaneSpeed(float speed)
{
	m_planeSpeed = speed;
}

float Player::GetPlaneSpeed()
{
	return m_planeSpeed;
}

void Player::SetE_freq(int& freq)
{
	if (freq <= 5) {
		e_freq = freq;
	}
	else {
		e_freq = 5;
		freq = 5;
	}
}

int Player::GetE_freq()
{
	return e_freq;
}

int Player::GetScore()
{
	return m_score;
}

void Player::Hell(float& displaySpeed)
{
	e_speed = 1500;
	displaySpeed = 1500;
	e_freq = 5;
	m_score = 5;
}

float Player::GetE_speed()
{
	return e_speed;
}

void Player::SetE_speed(float& speed)
{
	if (speed <= 1000) {
		e_speed = speed;
	}
	else {
		e_speed = 1000;
		speed = 1000;
	}
}

int Player::GetWidth()
{
	return m_texture->getWidth();
}

int Player::GetHeight()
{
	return m_texture->getHeight();
}

void Player::CollisionCheck()
{
	//player collision
	for (int i = 0; i < 15; ++i)
	{
		if (e_array[i]->GetActive()) {
			if (m_posX < e_array[i]->GetPosX() + 90 &&
				m_posX + 80 > e_array[i]->GetPosX() &&
				m_posY < e_array[i]->GetPosY() + 40 &&
				55 + m_posY > e_array[i]->GetPosY()) {
				//collision detected
				e_array[i]->SetActive(false);
				m_score -= 5;
			}
		}
	}

	//bullet collision
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			if (b_array[i]->GetPosX() < e_array[j]->GetPosX() + 130 &&
				b_array[i]->GetPosX() + 50 > e_array[j]->GetPosX() &&
				b_array[i]->GetPosY() < e_array[j]->GetPosY() + 40 &&
				30 + b_array[i]->GetPosY() > e_array[j]->GetPosY()) {
				
				//Check that the bullet is active
				if (b_array[i]->GetActive()) {
					//collision detected:  Deactivate the bullet and enemy then increment score
					b_array[i]->SetActive(false);
					e_array[j]->SetActive(false);
					++m_score;
				}
			}
		}
	}
}
