#include "Background.h"
#include <Texture.h>
#include <Renderer2D.h>



Background::Background()
{
	//create array of 2 background images
	m_array = new BGnode[2];

	//fill array with textures
	for (int i = 0; i < 2; ++i) {
		m_array[i].texture = new aie::Texture("../bin/textures/BootstrapAssignmentSprites/BackG.png");
		m_array[i].pos = 640 + (1280 * i);
	}
}

Background::~Background()
{
	//delete textures within array
	for (int i = 0; i < 2; ++i) {
		delete m_array[i].texture;
	}

	delete[] m_array;
}

void Background::update(float time)
{
	//index 0
	//move texture
	m_array[0].pos -= 300.0f * time;

	//if it reaches the edge of the screen reset its position
	if (m_array[0].pos < -640) {
		m_array[0].pos += 1280 * 2;
	}

	//index 1
	//move texture
	m_array[1].pos -= 300.0f * time;

	//if it reaches the edge of the screen reset its position
	if (m_array[1].pos < -640) {
		m_array[1].pos += 1280 * 2;
	}

}

void Background::draw(aie::Renderer2D* rend)
{
	//index 0
	rend->drawSprite(m_array[0].texture, m_array[0].pos, 360);

	//index 1
	rend->drawSprite(m_array[1].texture, m_array[1].pos, 360);
}
