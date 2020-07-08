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
	void calculateFPS();

	GameEngine::Window _window;
	int _screenWidth;    //declare screen width and height
	int _screenHeight;
	GameState _gameState;
	std::vector <GameEngine::Sprite*> _sprites;

	GameEngine::GLSLProgram _colorProgram;
	GameEngine::camera2D _camera;
	 
	float _time;
	float _fps;
	float _frameTime; 
	float _maxFPS;
};

