#pragma once
#include <Texture.h>
#include <Renderer2D.h>

class Background
{
public:
	Background();
	~Background();

	void update(float time);

	void draw(aie::Renderer2D* rend);

private:
	struct BGnode
	{
		aie::Texture* texture;
		float pos;
	};

	BGnode* m_array;
};

