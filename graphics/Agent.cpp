#include "Agent.h"
Agent::Agent() {

}
Agent::~Agent() {

}
void Agent::draw(GameEngine::SpriteBatch& spriteBatch) {
	GameEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	const glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 posAndSize = glm::vec4(position.x, position.y,WIDTH,HEIGHT);
	spriteBatch.draw(posAndSize,uv, texture.id, 0.0f, color);

}
bool Agent::update() {
	position += glm::vec2(speed, 0.0f);
	if (life == 0) {
		return true;
	}
	return false;
}