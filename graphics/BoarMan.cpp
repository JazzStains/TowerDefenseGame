#include "BoarMan.h"

BoarMan::BoarMan(glm::vec2 pos) {

	action = actionState::WALK;
	attackDamage = 30;
	speed = 0.1;
	position = glm::vec2(pos.x - 30, pos.y - 35);
	textureStanding = GameEngine::ResourceManager::getTexture("textures/BoarMan_Standing.png");
	textureWalkLeft = GameEngine::ResourceManager::getTexture("textures/BoarMan_WalkLeft.png");
	textureWalkMid = GameEngine::ResourceManager::getTexture("textures/BoarMan_WalkMid.png");
	textureWalkRight = GameEngine::ResourceManager::getTexture("textures/BoarMan_WalkRight.png");
	texture = textureStanding;
	life = 100;
}
BoarMan::BoarMan() {
	textureStanding = GameEngine::ResourceManager::getTexture("textures/BoarMan_Standing.png");
	texture = textureStanding;
	position = glm::vec2(0,0);
}

void BoarMan::setPosition(glm::vec2 pos){
	position = glm::vec2(pos.x - 30, pos.y - 35);
}