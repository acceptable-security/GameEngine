#include <Box2D/Box2D.h>
#include <string>
#include <map>
#include "render_list.h"
#include "player_object.h"

namespace GameEngine {
	class World {
		private:
			b2World* world;
			RenderList renderlist;
			PlayerObject* activeplayer;
			std::map<std::string, SpriteSheet*> spriteMap;
		public:
			World();
	
			void addObject(StaticObject* object);
			void addObject(DynamicObject* object);
	
			b2World* getWorld() { return world; };
	
			void setActivatePlayer(PlayerObject* player);
	
			void update(bool up, bool down, bool left, bool right);
			void render();
	
			SpriteSheet* initSpriteSheet(std::string name, const char* file);
			SpriteSheet* getSpritesheet(std::string name);

			void clean();
	};
}