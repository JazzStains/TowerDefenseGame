#include "BoarMan.h"

BoarMan::BoarMan(glm::vec2 pos) {
	attackDamage = 30;
	speed = 0.13;
	position = glm::vec2(pos.x - 30, pos.y - 35);
	texture = GameEngine::ResourceManager::getTexture("textures/BoarMan_Standing.png");
	life = 100;
}