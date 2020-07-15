#pragma once
#include <glm/glm.hpp>
#include <GameEngine/SpriteBatch.h>
#include <GameEngine/GLTexture.h>

class Bullet
{
public:
	Bullet(glm::vec2 postion);
	void draw(GameEngine::SpriteBatch& spriteBatch);
	bool update();
private:
	float _speed;
	glm::vec2 _position;
	GameEngine::GLTexture _texture;
	int _lifeTime;
};

