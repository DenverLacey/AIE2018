#include "GUIExerciseApp.h"
#include <iostream>

int main() {

	// log memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	// allocation
	auto app = new GUIExerciseApp();

	try {
		// initialise and loop
		app->run("GUIExercise", 1280, 720, false);
	}
	catch (std::exception e){
		std::cout << "Game could not run." << std::endl;
	}

	// deallocation
	delete app;

	return 0;
}