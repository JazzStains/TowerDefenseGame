#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>
namespace GameEngine {
	TextureCache::TextureCache() {

	}

	TextureCache::~TextureCache() {

	}

	GLTexture TextureCache::getTexture(std::string texturePath) {
		//look up texture to see if in map
		auto mit = _textureMap.find(texturePath);
		//check if not in map
		if (mit == _textureMap.end()) {
			//load texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);
			//insert into map
			_textureMap.insert(make_pair(texturePath, newTexture));

			//std::cout << "Loaded Cache Texture! \n";
			return newTexture;
		}
	//	std::cout << "Loaded Texture! \n";
		return mit->second;
	}
}