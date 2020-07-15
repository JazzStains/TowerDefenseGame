#pragma once
#include <SDL/SDL.h>   //includes the SDL library 
#include <GL/glew.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/GLSLProgram.h>
#include <GameEngine/GLTexture.h>
#include <vector>
#include <GameEngine/camera2D.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/Window.h>
#include <GameEngine/SpriteBatch.h>
#include <GameEngine/InputManager.h>
#include <GameEngine/Timing.h>
#include "Bullet.h"
#include "BackGround.h"
#include "BoarMan.h"

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

	

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	GameEngine::Window _window;
	int _screenWidth;    //declare screen width and height
	int _screenHeight;
	GameState _gameState;

	GameEngine::GLSLProgram _colorProgram;
	GameEngine::camera2D _camera;
	 
	GameEngine::SpriteBatch _spriteBatch;

	GameEngine::InputManager _InputManager;

	GameEngine::FPSLimiter _FPSLimiter; 

	BackGround _background;

	std::vector<Bullet> _bullets;
	std::vector<BoarMan> _boarMan;

	float _time;
	float _fps;
	float _maxFPS;
};

