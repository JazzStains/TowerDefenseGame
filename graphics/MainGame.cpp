#include "MainGame.h"
#include <iostream>
#include <GameEngine/Errors.h>
#include <string>
#include <GameEngine/ResourceManager.h>




MainGame::MainGame() 
{
	//set screen width
	_screenWidth =1350;
	//set screen height
	_screenHeight = 600;
	_gameState = GameState::PLAY;
	//set the state of the game to play
	_camera.init(_screenWidth,_screenHeight);
	_enemies = 0;
	_wave = 1;
	_spawnLimit = glm::vec4(_screenWidth/ 9.57f,_screenWidth/3.85f,_screenHeight/6.06f , _screenHeight / 1.89f);
	_counter = 1000;
}

MainGame::~MainGame()
{	

}

void MainGame::run() {
	initSystems();
	gameLoop();
	
}

void MainGame::initSystems() {
	
	GameEngine::initWindow();
	 
	_window.create("Game Engine", _screenWidth,_screenHeight,0);

	initShaders();
	_spriteBatch.init();   
	_background1.init(_screenWidth, _screenHeight, "textures/bg1.png");

	//init the UI
	initUI();
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
		//gathers input
		processInput(); 
		//updates camera
		_camera.update();
		if ((_counter == 0) && (_enemies != 0)) {
			_counter = 1000;
			spawnWave();
		}
		if ((_player.killCount == _enemiesSpawned) && (_enemies == 0)) {
			createWave();
		}
		_counter--;

		for (int i = 0; i < _boarMan.size();) {

			if (_boarMan[i].update() == true) {
				_boarMan[i] = _boarMan.back();
				_boarMan.pop_back();
			}
			else
				i++;
		}
		for (int i = 0; i < _skeletonDemon.size();) {

			if (_skeletonDemon[i].update() == true) {
				_skeletonDemon[i] = _skeletonDemon.back();
				_skeletonDemon.pop_back();
				_player.killCount++;
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
			glm::vec2 mouseCoords = _InputManager.getMouseCoords();
			mouseCoords = _camera.convertScreenToWorld(mouseCoords);
			for (int i = 0; i < _spriteOverlay.size(); i++) {
				_spriteOverlay[i].setPosition(mouseCoords);
			}
			break;
		}
		m_gui.onSDLEvent(action);
	}

	if (_InputManager.isKeyPressed(SDLK_w)) {
		//moves the camera up
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, 1.0));
	}

	if (_InputManager.isKeyPressed(SDLK_a)) {
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
		if (_createBoar == true){
			if (((mouseCoords.x >= _spawnLimit.x) && (mouseCoords.x <= _spawnLimit.y))&&((mouseCoords.y >= _spawnLimit.z)&&(mouseCoords.y <= _spawnLimit.w))) {
				_boarMan.emplace_back(mouseCoords);
			}
			for (int i = 0; i < _spriteOverlay.size();) {
					_spriteOverlay[i] = _spriteOverlay.back();
					_spriteOverlay.pop_back();
				}
			_createBoar = false;
		}
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
	_background1.draw(_spriteBatch);

	for (int i = 0; i < _boarMan.size(); i++)
		_boarMan[i].draw(_spriteBatch);

	for (int i = 0; i < _skeletonDemon.size(); i++)
		_skeletonDemon[i].draw(_spriteBatch);

	for (int i = 0; i < _spriteOverlay.size(); i++) 
		_spriteOverlay[i].draw(_spriteBatch);
	
	_spriteBatch.end();
	
	_spriteBatch.renderBatch();
	

	//unbind the texture
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	_colorProgram.unuse();
	
	m_gui.draw();
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	_window.swapBuffer();
}

void MainGame::spawnWave() {
	_enemies--;
	float randonSpawmY = rand() % (200) + 99;
	glm::vec2 spawnPosition = glm::vec2(1350.00f, randonSpawmY);
	_skeletonDemon.emplace_back(spawnPosition);

}

void MainGame::createWave() {
	_counter = 1000 - (_wave * 10);
	_enemies = _wave * 5;
	_enemiesSpawned = _enemies;
}

void MainGame::initUI() {
	m_gui.init("GUI");
	m_gui.loadScheme("AlfiskoSkin.scheme");
	m_gui.setFont("DejaVuSans-10");
	CEGUI::PushButton* boarMan = static_cast<CEGUI::PushButton*>(m_gui.createWidget("AlfiskoSkin/Button", glm::vec4(0.0549f, 0.904f, 0.05f, 0.093f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), "Boar Man"));
	boarMan->setText("Boar Man");
	boarMan->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainGame::createBoarManSprite,this));
}
bool MainGame::createBoarManSprite(const CEGUI::EventArgs& e) {
	glm::vec2 mouseCoords = _InputManager.getMouseCoords();
	mouseCoords = _camera.convertScreenToWorld(mouseCoords);
	_spriteOverlay.emplace_back(mouseCoords);
	_createBoar = true;
	return true;
}