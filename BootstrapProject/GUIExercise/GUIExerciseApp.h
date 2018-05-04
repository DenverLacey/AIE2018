#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Player.h"
#include "Background.h"

class GUIExerciseApp : public aie::Application {
public:

	GUIExerciseApp();
	virtual ~GUIExerciseApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();


protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	
	//Plane
	Player*				m_plane;

	//Background
	Background*			m_bckgrnd;

	//Menu
	bool				gui_playing;
	bool				gui_gameOver;
	bool				gui_hell;
	bool				gui_controls;
	int					gui_freq;
	float				gui_speed;



};