#include "game.h"

GameEngine::Game* game;

int main(int argc, char** argv) {


	game = GameEngine::NewGame("Neglect", 640, 480, argc, argv);
	game->initGL();
	game->initGame();

	GameEngine::PlayerObject* player = new GameEngine::PlayerObject(game->getWorld()->getSpritesheet("playersprites"), 2.0f, 50.0f, 300.0f, game->getWorld()->getWorld(), 640, 480);
	game->getWorld()->setActivatePlayer(player);
	game->begin();
	return 0;
}

