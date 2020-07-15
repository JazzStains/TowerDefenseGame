#pragma once
#include<GameEngine/SpriteBatch.h>
#include <glm/glm.hpp>
#include <GameEngine/GLTexture.h>


class Agent
{
public:
	Agent();
	virtual ~Agent();
	void draw(GameEngine::SpriteBatch& spriteBatch);
	bool update();


protected:
	glm::vec2 position;
	const static int HEIGHT = 70;
	const static int WIDTH = 60;
	float speed;
	float life;
	float attackDamage;
	float defense;
	float height;
	float width;
	GameEngine::GLTexture texture;

	
};

