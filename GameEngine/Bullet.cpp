#include "Bullet.h"
#include <GameEngine/ResourceManager.h>
Bullet::Bullet(glm::vec2 postion) {
	_speed = 10;
	_lifeTime = 300;
	_texture = GameEngine::ResourceManager::getTexture("textures/jjp/PNG/Bullet.png");
	_position = postion;
}
void Bullet::draw(GameEngine::SpriteBatch& spriteBatch) {
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	GameEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x+70.0f, _position.y+40.0f,10,10);
	spriteBatch.draw(posAndSize, uv, _texture.id, 0.0f, color);
}
bool Bullet::update() {
	_position += glm::vec2(_speed,0.0f);
	_lifeTime--;
	if (_lifeTime == 0) {
		return true;
	}
	return false;
}