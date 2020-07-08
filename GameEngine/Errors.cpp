#include "Errors.h"
#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>
namespace GameEngine {
	// for error checking
	void fatalError(std::string errorString) {
		std::cout << errorString << std::endl;
		std::cin.ignore();
		SDL_Quit();
		exit(10);
	}
}
