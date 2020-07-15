#include "MainGame.h"
#include <iostream>
#include <GameEngine/Errors.h>
#include <string>
#include <GameEngine/ResourceManager.h>



MainGame::MainGame(): _screenWidth(1350), _time(0),   
	_screenHeight(600), 
	_gameState(GameState::PLAY),
	_maxFPS(60.0f) 
{
	//sets pointer to null
	//set screen width
	//set screen height
	//set the state of the game to play
	_camera.init(_screenWidth,_screenHeight);
}

MainGame::~MainGame()
{	

}

void MainGame::run() {
	initSystems();
	_background.init(_screenWidth, _screenHeight);
	gameLoop();
}

void MainGame::initSystems() {

	GameEngine::initWindow();
	 
	_window.create("Game Engine", _screenWidth,_screenHeight,0);

	initShaders();
	_spriteBatch.init();   

	_FPSLimiter.init(_maxFPS);
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();

	 
}
void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {

		                                                                                   
		//frame time measuring  
		_FPSLimiter.beginFrame();

		processInput(); //gathers input
		_time += 0.01;

		//updates camera
		_camera.update();

		//updates bullets
		for (int i = 0; i < _bullets.size();) {
			if (_bullets[i].update() == true) {
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else
				i++;
		}

		for (int i = 0; i < _boarMan.size();) {
			if (_boarMan[i].update() == true) {
				_boarMan[i] = _boarMan.back();
				_boarMan.pop_back();
			}
			else
				i++;
		}
		drawGame();

		
	}
	
}


void MainGame::processInput() {
	SDL_Event action;
	while (SDL_PollEvent(&action)) {
		switch (action.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;

		case SDL_KEYDOWN:
			//checks which key is pressed 
			_InputManager.pressedKey(action.key.keysym.sym);
			break;

		case SDL_KEYUP:
			_InputManager.releaseKey(action.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_InputManager.pressedKey(action.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_InputManager.releaseKey(action.button.button);
			break;
		case SDL_MOUSEMOTION:
			_InputManager.setMouseCoords(action.motion.x, action.motion.y);
		}
	}

	if (_InputManager.isKeyPressed(SDLK_w)) {
		//moves the camera up
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, 1.0));
	}

	if (_InputManager.isKeyPressed(SDLK_a)) {
		//moves the camera up
		_camera.setPosition(_camera.getPosition() + glm::vec2(-1.0, 0.0));
	}

	if (_InputManager.isKeyPressed(SDLK_s)) {
		//moves the camera up
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -1.0));
	}

	if (_InputManager.isKeyPressed(SDLK_d)) {
		//moves the camera up
		_camera.setPosition(_camera.getPosition() + glm::vec2(1.0, 0.0));
	}
	if (_InputManager.isKeyPressed(SDLK_q)) {
		_camera.setScale(_camera.getScale() + 0.1f);
	}
	if (_InputManager.isKeyPressed(SDLK_e)) {
		_camera.setScale(_camera.getScale() - 0.1f);
	}

	if (_InputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = _InputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		std::cout << mouseCoords.x << " " << mouseCoords.y << std::endl;

		glm::vec2 position(55.0f, 47.0f);
		_boarMan.emplace_back(mouseCoords);
		_bullets.emplace_back(position);

		
	}
}
 
void MainGame::drawGame() {



	glClearDepth(1.0); //sets base depth to 1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears color and depth buffer

	_colorProgram.use();
	//using texture unit 0
	glActiveTexture(GL_TEXTURE0);

	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");

	//tell shader texture unit is 0
	glUniform1i(textureLocation, 0);

	//set camera matrix
	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	//uploads matrix to GPU
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();
	_background.draw(_spriteBatch);

	for (int i = 0; i < _boarMan.size(); i++) {
		_boarMan[i].draw(_spriteBatch);

	}
	_spriteBatch.end();
	_spriteBatch.renderBatch();

	//unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unuse();

	_window.swapBuffer();

}

