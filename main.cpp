#include "game.h"

GameEngine::Game game;

int main(int argc, char** argv) {
	game = GameEngine::NewGame("Neglect", 640, 480, argc, argv);
	game.initGL();
	game.initGame();
	game.begin();
	return 0;
}

