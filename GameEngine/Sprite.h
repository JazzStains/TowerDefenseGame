#pragma once
#include <GL/glew.h>
#include "GLTexture.h"
#include <string>
namespace GameEngine {
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void draw();
		void init(float x, float y, float width, float height, std::string texturePath);
		void changeTexture(std::string texturePath);


	private:
		float _x;
		float _y;
		float _width;
		float _height;
		GLTexture _texture;
		GLuint _vboiID;  //unsigned int of 
						 
						 //acts as vertex buffer

	};
}
