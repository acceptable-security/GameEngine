#include "world.h"

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

void World::clean() {
	renderlist.clean();
	activeplayer->clean();
	delete world;
}