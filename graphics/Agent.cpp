#include "Agent.h"
#include <iostream>
Agent::Agent() {
	sizeMultiplier = 1.5;
	walkCounter = 0;
	walkState = 0;
}
Agent::~Agent() {

}
void Agent::draw(GameEngine::SpriteBatch& spriteBatch) {
	GameEngine::ColorRGBA8 color;
	color = GameEngine::ColorRGBA8(255, 255,255,255);

	const glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 posAndSize = glm::vec4(position.x, position.y,texture.width * sizeMultiplier, texture.height * sizeMultiplier);
	spriteBatch.draw(posAndSize,uv, texture.id, 0.0f, color);

}
bool Agent::update() {

	switch (action)
	{
	case actionState::STAND:

		break;
	case actionState::WALK:
		if( walkCounter == 250)
		{
			switch (walkState) {
			case (0):
				texture = textureWalkLeft;
				break;
			case(1):
				texture = textureWalkMid;
				break;
			case(2):
				texture = textureWalkRight;
				break;
			case(3):
				texture = textureWalkMid;
				walkState = -1;
				break;

			 }
			walkState++;
			
			walkCounter = 0;
		}
		
		walkCounter++;
		break;
	case actionState::ATTACK:
		break;
	default:
		break;
	}
	position += glm::vec2(speed, 0.0f);
	if (life == 0) {
		return true;
	}
	return false;
}