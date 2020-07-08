#include "MainGame.h"
#include <iostream>
#include <GameEngine/Errors.h>
#include <string>



MainGame::MainGame(): _screenWidth(960), _time(0),   
	_screenHeight(720), 
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
	_sprites.push_back(new GameEngine::Sprite());
	_sprites.back()->init(0.0f, 0.0f,_screenWidth/2, _screenWidth / 2, "textures/jjp/PNG/Enemys/Enemy_Broccoli1.png");

	_sprites.push_back(new GameEngine::Sprite());
	_sprites.back()->init(_screenWidth / 2, 0.0f, _screenWidth / 2, _screenWidth / 2, "textures/jjp/PNG/Enemys/Enemy_Candy1.png");

	gameLoop();
}

void MainGame::initSystems() {
	GameEngine::initWindow();

	_window.create("Game Engine", _screenWidth,_screenHeight,0);

	initShaders();
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
		static int attack = 0;
		static int counter = 0;
		counter++;

		if ((counter == 20) && (attack == 0)) {
			_sprites[0]->changeTexture("textures/jjp/PNG/Enemys/Enemy_Broccoli2.png");
			_sprites[1]->changeTexture("textures/jjp/PNG/Enemys/Enemy_Candy1.png");

			counter = 0;
			attack = 1;

		}
		if ((counter == 20) && (attack == 1)){
			attack = 0;
			_sprites[0]-> changeTexture("textures/jjp/PNG/Enemys/Enemy_Broccoli1.png");
			_sprites[1]->changeTexture("textures/jjp/PNG/Enemys/Enemy_Candy2.png");
			counter = 0;
		}
		                                                                                   
		//frame time measuring
		float startTicks = SDL_GetTicks(); 

		processInput(); //gathers input
		_time += 0.01;

		_camera.update();

		drawGame();
		calculateFPS();
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}
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
			switch (action.key.keysym.sym) {
			case SDLK_w:
				//moves the camera up
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, 1.0));
				break;
			case SDLK_q:
				_camera.setScale(_camera.getScale() + 0.1f);
				break;
			}
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
	//set the constantly changing time variable
	//GLint timeLocation = _colorProgram.getUniformLocation("time");
	//glUniform1f(timeLocation, _time);

	//set camera matrix
	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	//uploads matrix to GPU
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));



	//draw the sprite
	for (int i = 0; i < _sprites.size(); i++) {
		_sprites[i]->draw();
	}
	

	//unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unuse();

	_window.swapBuffer();

}

void MainGame::calculateFPS() {
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;
	static float prevTicks = SDL_GetTicks();
	float currentTicks;

	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;

	int count; 

	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;
	float frameTimeAverage = 0;

	for (int i = 0; i < count; i++) {
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0) {
		_fps = 1000.0f / frameTimeAverage;
	}
	else
		_fps = 60.0f;

	
	
}

