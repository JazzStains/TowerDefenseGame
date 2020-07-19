#include "SkeletonDemon.h"

SkeletonDemon::SkeletonDemon(glm::vec2 pos) {
	action = actionState::WALK;
	attackDamage = 10;
	speed = -0.1;
	position = pos;
	textureStanding = GameEngine::ResourceManager::getTexture("textures/SkeletonDemon_Standing.png");
	textureWalkLeft = GameEngine::ResourceManager::getTexture("textures/SkeletonDemon_WalkLeft.png");
	textureWalkMid = GameEngine::ResourceManager::getTexture("textures/SkeletonDemon_WalkMid.png");
	textureWalkRight = GameEngine::ResourceManager::getTexture("textures/SkeletonDemon_WalkRight.png");
	texture = textureStanding;
	life = 100;
	sizeMultiplier = 2;
}