#include <Box2D/Box2D.h>
#include <string>
#include <map>
#include "render_list.h"
#include "player_object.h"

struct bodyData {
	const char* type;
	void* object;
};
#ifndef CONTACT
#define CONTACT
class GameContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) {
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		
		if ( bodyUserData ) {
			bodyData* bodyDat = (bodyData*)bodyUserData;
			//printf("%s \n", bodyDat->type);
			if(bodyDat->type == "dynamic")
				static_cast<GameEngine::DynamicObject*>( bodyUserData )->startContact();
			if(bodyDat->type == "static")
				static_cast<GameEngine::StaticObject*>( bodyUserData )->startContact();
			if(bodyDat->type == "player")
				static_cast<GameEngine::PlayerObject*>( bodyUserData )->startContact();
		}
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if ( bodyUserData ) {
			bodyData* bodyDat = (bodyData*)bodyUserData;
			if(bodyDat->type == "dynamic")
				static_cast<GameEngine::DynamicObject*>( bodyUserData )->startContact();
			if(bodyDat->type == "static")
				static_cast<GameEngine::StaticObject*>( bodyUserData )->startContact();
			if(bodyDat->type == "player")
				static_cast<GameEngine::PlayerObject*>( bodyUserData )->startContact();
		}
	}
  
	void EndContact(b2Contact* contact) {
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		
		if ( bodyUserData ) {
			bodyData* bodyDat = (bodyData*)bodyUserData;
			if(bodyDat->type == "dynamic")
				static_cast<GameEngine::DynamicObject*>( bodyUserData )->endContact();
			if(bodyDat->type == "static")
				static_cast<GameEngine::StaticObject*>( bodyUserData )->endContact();
			if(bodyDat->type == "player")
				static_cast<GameEngine::PlayerObject*>( bodyUserData )->endContact();
		}
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if ( bodyUserData ) {
			bodyData* bodyDat = (bodyData*)bodyUserData;
			if(bodyDat->type == "dynamic")
				static_cast<GameEngine::DynamicObject*>( bodyUserData )->endContact();
			if(bodyDat->type == "static")
				static_cast<GameEngine::StaticObject*>( bodyUserData )->endContact();
			if(bodyDat->type == "player")
				static_cast<GameEngine::PlayerObject*>( bodyUserData )->endContact();
		}
	}
};
#else
class GameContactListener;
#endif
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
			RenderList* getRenderList() { return &renderlist; }
	
			void setActivatePlayer(PlayerObject* player);
	
			void update(bool up, bool down, bool left, bool right);
			void render();
	
			SpriteSheet* initSpriteSheet(std::string name, const char* file);
			SpriteSheet* getSpritesheet(std::string name);

			void clearWorld();

			void clean();
	};
}