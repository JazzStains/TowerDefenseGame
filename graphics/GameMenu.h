#pragma once
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <GameEngine/GUI.h>
#include <SDL/SDL.h> 
#include <GameEngine/Window.h>
#include <GameEngine/camera2D.h>
#include <GameEngine/GLSLProgram.h>
#include <GameEngine/GameEngine.h>
#include "BackGround.h"
#include <GameEngine/SpriteBatch.h>
enum class MenuState {RUN, PLAY, EXIT };
class GameMenu
{
public:
	GameMenu();
	~GameMenu();
	void run();
	bool quit;
private:
	int _screenWidth;    //declare screen width and height
	int _screenHeight;
	GameEngine::Window _window;
	void menuLoop();
	void initSystems();
	void initShaders();
	GameEngine::SpriteBatch _spriteBatch;
	bool onExitClicked(const CEGUI::EventArgs& e);
	bool onPlayClicked(const CEGUI::EventArgs& e);
	void initUI();
	void drawMenu();
	MenuState _menuState;
	GameEngine::GLSLProgram _colorProgram;
	GameEngine::GUI m_gui;
	GameEngine::camera2D _camera;
	void processInput();
	BackGround _background;
};

