#include "GameMenu.h"

GameMenu::GameMenu() {

	//set screen width
	_screenWidth = 1350;
	//set screen height
	_screenHeight = 600;
	//set the state of the game to play
	_camera.init(_screenWidth, _screenHeight);
	_menuState = MenuState::RUN;
	quit = false;
}
GameMenu::~GameMenu() {
}
	
bool GameMenu::onExitClicked(const CEGUI::EventArgs& e) {
	_menuState = MenuState::EXIT;
	quit = true;
	return true;
}
void GameMenu::initSystems() {
	GameEngine::initWindow();
	_window.create("Game Menu", _screenWidth, _screenHeight, 0);

	initShaders();
	_background.init(_screenWidth, _screenHeight,"textures/bg.png");

	//init the UI
	initUI();
}
void GameMenu::initShaders() {
	_colorProgram.compileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}
void GameMenu::initUI() {
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.setFont("DejaVuSans-10");
	CEGUI::PushButton* playGame = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.455f, 0.46f, 0.09f, 0.08f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), "PlayGame"));
	playGame->setText("Play Game");
	playGame->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameMenu::onPlayClicked, this));
	CEGUI::PushButton* quitGame = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.455f, 0.56f, 0.09f, 0.08f), glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), "QuitGame"));
	quitGame->setText("Quit");
	quitGame->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameMenu::onExitClicked, this));
}
void GameMenu::run() {
	initSystems();
	_spriteBatch.init();
	menuLoop();
	m_gui.destroy();
	_window.deleteWindow();
}
void GameMenu::menuLoop() {
	while (_menuState == MenuState::RUN) {
		processInput();
		_camera.update();
		drawMenu();
	}
}

bool GameMenu::onPlayClicked(const CEGUI::EventArgs& e) {
	_menuState = MenuState::PLAY;
	return true;
}
void GameMenu::drawMenu() {
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
	_spriteBatch.end();

	_spriteBatch.renderBatch();
	glBindTexture(GL_TEXTURE_2D, 0);

	_colorProgram.unuse();
	m_gui.draw();
	_window.swapBuffer();
	
}
void GameMenu::processInput() {
	SDL_Event action;
	while (SDL_PollEvent(&action)) {
		switch (action.type) {
		case SDL_QUIT:
			_menuState = MenuState::EXIT;
			break;
		}
		m_gui.onSDLEvent(action); 
	}
}

