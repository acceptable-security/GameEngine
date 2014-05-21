#include <Box2D/Box2D.h>
#include "render_list.h"
#include "player_object.h"

class World {
	private:
		b2World* world;
		RenderList renderlist;
		PlayerObject* activeplayer;
	public:
		World();

		void addObject(StaticObject* object);
		void addObject(DynamicObject* object);

		b2World* getWorld() { return world; };

		void setActivatePlayer(PlayerObject* player);

		void update(bool up, bool down, bool left, bool right);
		void render();

		void clean();
};