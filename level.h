#include <json/json.h>
#include "world.h"

namespace GameEngine {
	void loadLevel(const char* file, World* world, int windowWidth, int windowHeight);
	void loadSpriteSheet(const char* file, World* world);
}