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
#include "SkeletonDemon.h"
#include "Player.h"
#include <cstdlib>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <GameEngine/GUI.h>

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
	void spawnWave();
	void createWave();
	void initUI();
	bool createBoarManSprite(const CEGUI::EventArgs& e);

	GameEngine::Window _window;
	int _screenWidth;    //declare screen width and height
	int _screenHeight;
	GameState _gameState;

	GameEngine::GLSLProgram _colorProgram;
	GameEngine::camera2D _camera;
	GameEngine::SpriteBatch _spriteBatch;
	GameEngine::InputManager _InputManager;
	GameEngine::GUI m_gui;
	
	std::vector<BoarMan> _spriteOverlay;
	std::vector<BoarMan> _boarMan;
	std::vector<SkeletonDemon> _skeletonDemon;
	BackGround _background1;
	bool _createBoar;
	glm::vec4 _spawnLimit;
	int _enemies;
	int _counter;
	int _enemiesSpawned;
	Player _player;
	int _wave;
};

