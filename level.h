#include <json/json.h>
#include "light.h"

namespace GameEngine {
	void loadLevel(const char* file, World* world, int windowWidth, int windowHeight);
	void loadSpriteSheet(const char* file, World* world);
}

std::string get_file_contents(const char *filename);