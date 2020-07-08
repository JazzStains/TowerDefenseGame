#pragma once
#include <GL/glew.h>
//information for the texture

namespace GameEngine {
	struct GLTexture {
		//pointer to the texture in memory
		GLuint id;
		int width;
		int height;
	};
}