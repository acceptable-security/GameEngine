#include "image_test.h"
#include <Box2D/Box2D.h>
class DynamicObject {
	private:
		b2BodyDef bodyDef;
		b2Body* body;
		b2PolygonShape box;
		b2Vec2 vertices[4];
		b2FixtureDef fixtureDef;
		
		int x, y;
		float scale;
		int width, height;
		int winWidth, winHeight;



		const char* imageFile;
		Image gLoadedTexture;
public:
		DynamicObject(const char* imageFile, float scale, b2Vec2 pos, b2World* world, int wWidth, int wHeight);
		void render();
		void WindowResize(int wWidth, int wHeight);
		void SetPosition(int x, int y);
		void resize(int width, int height);
		void debug();
		void clean(); // does box2D objects need to be cleaned?
};