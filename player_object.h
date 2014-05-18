#include "spritesheets.h"
#include <Box2D/Box2D.h>

class PlayerObject {
	private:
		b2BodyDef bodyDef;
		b2Body* body;
		b2PolygonShape box;
		b2Vec2 vertices[4];
		b2FixtureDef fixtureDef;
		//float r, g, b;
		char* state;
		char* direction;
		int x, y;
		float scale;
		int winWidth, winHeight;
		int termX;
		SpriteSheet sprites;
	public:
		PlayerObject();
		PlayerObject(SpriteSheet* sprites, float scale, float x, float y, b2World* world, int wWidth, int wHeight);
		void render();
		void WindowResize(int wWidth, int wHeight);
		void SetPosition(int x, int y);
		void resize(float scale);
		void debug();
		void update(bool up, bool down, bool left, bool right);
		void clean(); // does box2D objects need to be cleaned?	
};