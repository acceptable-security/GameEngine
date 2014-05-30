#include "image_test.h"
#include <Box2D/Box2D.h>

namespace GameEngine {
	class DynamicObject {
		private:
			b2BodyDef bodyDef;
			b2Body* body;
			b2PolygonShape box;
			b2Vec2 vertices[4];
			b2FixtureDef fixtureDef;
			int winWidth, winHeight;
			Image gLoadedTexture;
			void* b2DataPtr;

			void drawImage();
			
		protected:
			int x, y;
			float scale;
			int width, height;
			const char* imageFile;	

			void clean();
		public:
			const char* type;

			DynamicObject(const char* imageFile, float scale, b2Vec2 pos, b2World* world, int wWidth, int wHeight);
			DynamicObject() {};
			b2Body* getBody() { return body; };
			void render();
			void WindowResize(int wWidth, int wHeight);
			void SetPosition(int x, int y);
			void resize(int width, int height);
			void startContact();
			void endContact();
			void _clean();
	};
}