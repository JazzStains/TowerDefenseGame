#include <iostream>
#include "MainGame.h"
#include "GameMenu.h"


int main(int argc, char** argv ) {
	GameMenu gameMenu;
	MainGame mainGame;
	gameMenu.run();
	if (gameMenu.quit == true) {
		return 0;
	}
	mainGame.run(); 
	return 0;
}