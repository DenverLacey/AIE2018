#include "GUIExerciseApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <imgui.h>
#include "Player.h"
#include "Background.h"

GUIExerciseApp::GUIExerciseApp() {

}

GUIExerciseApp::~GUIExerciseApp() {

}

bool GUIExerciseApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_bckgrnd = new Background();

	m_plane = new Player();

	//initialise gui variables
	gui_playing = false;
	gui_gameOver = false;
	gui_hell = false;
	gui_controls = false;
	gui_freq = m_plane->GetE_freq();
	gui_speed = m_plane->GetE_speed();

	return true;
}

void GUIExerciseApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete m_plane;
	delete m_bckgrnd;
}

void GUIExerciseApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	if (gui_playing && !gui_gameOver) {
		// set arrow keys to control the plane position
		m_plane->Update(deltaTime, input);
	}

	// run scrolling background
	m_bckgrnd->update(deltaTime);

	//If the player loses, exit the application
	if (m_plane->GetScore() < 0) {
		ImGui::Begin("Game Over!");
		ImGui::Text("You Lose!");
		gui_gameOver = true;
		if (ImGui::Button("Quit")) {
			quit();
		}
		ImGui::End();
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void GUIExerciseApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	//Menu GUI
	if (!gui_playing) {
		ImGui::Begin("Menu:");
		ImGui::Text("GET READY TO SHOOT UP THE SKIES!");

		ImGui::SliderInt("Enemy Frequency", &gui_freq, 1, 5);
		ImGui::SliderFloat("Enemy Speed", &gui_speed, 100.0f, 1000.0f);

		ImGui::Checkbox("Gimme Hell!", &gui_hell);
		if (gui_hell) {
			//Gimme Hell mode
			m_plane->Hell(gui_speed);
			gui_freq = 5;
		}
		else {
			//change values based on user's settings
			m_plane->SetE_freq(gui_freq);
			m_plane->SetE_speed(gui_speed);
		}

		ImGui::Text("Press to see controls");
		ImGui::Checkbox("Controls", &gui_controls);

		ImGui::Text("Rules:");
		ImGui::Text("  1. Shoot a blimp, get a point.");
		ImGui::Text("  2. Collide with blimp, lose 5 points.");
		ImGui::Text("  3. Let a blimp get past you, lost a point.");
		ImGui::Text("");
		ImGui::Text("If you dip below 0 points the game ends.");

		if (ImGui::Button("Start")) {
			gui_playing = true;
		}
		ImGui::End();

		if (gui_controls) {
			ImGui::Begin("Controls:");
			ImGui::Text("'W' to fly up.");
			ImGui::Text("'A' to fly left.");
			ImGui::Text("'S' to fly down.");
			ImGui::Text("'D' to fly right.");
			ImGui::Text("'Space' to shoot.");
			ImGui::Text("'Esc' to exit the game.");
			if (ImGui::Button("Close")) {
				gui_controls = false;
			}
			ImGui::End();
		}
	}

	// draw background
	m_bckgrnd->draw(m_2dRenderer);

	//draw plane sprite
	m_plane->Draw(m_2dRenderer);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}
