#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"
namespace GameEngine {
	GLTexture ImageLoader::loadPNG(std::string filePath) {
		GLTexture texture = {}; //sets everything to 0
		std::vector<unsigned char> out; //pixel data
		std::vector <unsigned char> in;
		unsigned long width, height;

		if (IOManager::readFileToBuffer(filePath, in) == false) {
			fatalError("failed to load png file to buffer");
		}
		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());

		if (errorCode != 0) {
			fatalError("decodePNG failed with error: " + std::to_string(errorCode));
		}

		glGenTextures(1, &(texture.id)); //turn id from 0 into unique id for texture
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0])); //upload to graphics card and stored in vram
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //uses linear interpolation
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //mipmap fades texture as sprite gets smaller


		//generate mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0); // unbinds current texture

		texture.width = width;
		texture.height = height;

		//return copy of texture data
		return texture;

	}

}