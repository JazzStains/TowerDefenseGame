#include "Window.h"
#include "Errors.h"
#include <iostream>
namespace GameEngine {
	Window::Window() {

	}

	Window::~Window() {
		
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {

		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE) {
			//sets window to minimize
			flags |= SDL_WINDOW_HIDDEN;
		}

		if (currentFlags & FULLSCREEN) {
			//sets window to fullscreen
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		if (currentFlags & BORDERLESS) {
			//sets window to borderless
			flags |= SDL_WINDOW_BORDERLESS;
		}


		//creates the window
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

		if (_sdlWindow == nullptr)
			fatalError("SDL Window could not be created.");

		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);

		if (glContext == nullptr)
			fatalError("SDL context could not be created.");

		GLenum error = glewInit();
		if (error != GLEW_OK)
			fatalError("Could not initialize glew!");

		//check OpenGL version
		std::printf("***OpenGL Version : % s***\n", glGetString(GL_VERSION));

		//sets background to blue
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

		//set Vsync to on
		SDL_GL_SetSwapInterval(0);

		//enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer() {
		//Swap buffer and draw everuthing on screen
		SDL_GL_SwapWindow(_sdlWindow);
	}
	void Window::deleteWindow() {
		SDL_DestroyWindow(_sdlWindow);
	}
}