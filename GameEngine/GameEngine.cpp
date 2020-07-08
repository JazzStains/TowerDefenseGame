#include <SDL/SDL.h>
#include <GL/glew.h>
#include "GameEngine.h"
#include <iostream>
namespace GameEngine {
	int initWindow() {
		//Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//tell SDL to set double buffer sot here will be no flickering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		return 0;
	}
}