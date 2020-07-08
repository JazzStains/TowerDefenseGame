#pragma once
#include "GLTexture.h"
#include <string>
namespace GameEngine {
	//load images into GL texture
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};

}

