#include "BackGround.h"

BackGround::BackGround() {

}
void BackGround::init(int width, int height) {
	_height = height;
	_width = width;
	_texture = GameEngine::ResourceManager::getTexture("textures/bg.png");
}

void BackGround:: draw(GameEngine::SpriteBatch& spriteBatch) {
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	GameEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(0.0f, 0.0f, _width, _height);
	spriteBatch.draw(posAndSize, uv, _texture.id, 0.0f, color);
}