#pragma once
#include<GameEngine/SpriteBatch.h>
#include <glm/glm.hpp>
#include <GameEngine/GLTexture.h>
#include <GameEngine/Vertex.h>

enum class actionState { STAND, WALK, ATTACK };

class Agent
{
public:
	Agent();
	virtual ~Agent();
	void draw(GameEngine::SpriteBatch& spriteBatch);
	bool update();


protected:
	glm::vec2 position;
	double sizeMultiplier;
	float speed;
	float life;
	float attackDamage;
	float defense;
	float height;
	float width;
	GameEngine::GLTexture texture;
	GameEngine::GLTexture textureStanding;
	GameEngine::GLTexture textureWalkLeft;
	GameEngine::GLTexture textureWalkRight;
	GameEngine::GLTexture textureWalkMid;
	actionState action;
	int  walkCounter;
	int walkState;
	bool attack;
	


	
};

