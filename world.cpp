#include "world.h"

namespace GameEngine {
	World::World() {
		world = new b2World(b2Vec2(0.0f, -10.0f));
	}
	
	void World::addObject(StaticObject* object) {
		renderlist.add(object);
	}
	
	void World::addObject(DynamicObject* object) {
		renderlist.add(object);
	}
	
	void World::setActivatePlayer(PlayerObject* player) {
		activeplayer = player;
	}
	
	void World::update(bool up, bool down, bool left, bool right) {
		world->Step(1.0f/60.0f, 6, 2);
		activeplayer->update(up, down, left, right);
	}
	
	void World::render() {
		renderlist.render();
		activeplayer->render();
	}

	SpriteSheet* World::initSpriteSheet(std::string name, const char* file) {
		spriteMap[name] = new SpriteSheet(file);
		return spriteMap[name];
	}
	
	SpriteSheet* World::getSpritesheet(std::string name) {
		return spriteMap[name];
	}

	void World::clearWorld() {
		for(std::map<std::string, SpriteSheet*>::iterator it = spriteMap.begin(); it != spriteMap.end(); ++it) {
			delete spriteMap[it->first];
		}
		renderlist.clean();
		activeplayer->_clean();
		delete activeplayer;
	}

	void World::clean() {
		clearWorld();
		delete world;
	}
}