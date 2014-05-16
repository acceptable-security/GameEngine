#include <Box2D/Box2D.h>
#include "image_test.h"

class StaticObject {
	private:
		b2BodyDef bodyDef;
		b2Body* body;
		b2PolygonShape box;
		b2Vec2 vertices[4];
		
		int x, y;
		float scale;
		int width, height;
		int winWidth, winHeight;
		
		const char* imageFile;
		Image gLoadedTexture;
	public:
		StaticObject(const char* imageFile, float scale, b2Vec2 pos, b2World* world, int wWidth, int wHeight);
		void render();
		void WindowResize(int wWidth, int wHeight);
		void resize(int width, int height);
		//void debug();
		void clean(); // does box2D objects need to be cleaned?
};