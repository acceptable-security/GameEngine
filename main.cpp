#include "game.h"

GameEngine::Game game;

int main(int argc, char** argv) {
	game = GameEngine::NewGame("Neglect", 640, 480, argc, argv);
	game.initGL();
	game.initGame();
		game.getWorld().addObject(new GameEngine::StaticObject("blue_square.png", 100.0f, b2Vec2(10,10), game.getWorld().getWorld(), 640, 480));

		GameEngine::SpriteSheet sprite("spritesheet.png");
	
		sprite.initSequence("idle", 60.0f, 9.0f, 14.0f);
		sprite.initSequence("run", 60.0f, 9.0f, 14.0f);
		sprite.initSequence("jump", 60.0f, 9.0f, 14.0f);
		sprite.initSequence("fall", 60.0f, 9.0f, 14.0f);
	
		sprite.addAnimationRow("idle", 0, 1);
		sprite.addAnimationRow("run", 1, 9);
		sprite.addAnimationRow("jump", 2, 1);
		sprite.addAnimationRow("fall", 2, 1);
		game.getWorld().setActivatePlayer(new GameEngine::PlayerObject(&sprite, 2.0f, 50.0f, 300.0f, game.getWorld().getWorld(), 640, 480));
	game.begin();
	return 0;
}

