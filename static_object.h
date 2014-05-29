#include <Box2D/Box2D.h>
#include <string.h>
#include "image_test.h"

namespace GameEngine {
	class StaticObject {
		private:
			b2BodyDef bodyDef;
			b2Body* body;
			b2PolygonShape box;
			b2Vec2 vertices[4];
			Image gLoadedTexture;
			int winWidth, winHeight;

			void* b2DataPtr;

		protected:
			int x, y;
			float scale;
			int width, height;
			const char* imageFile;
			
			void clean();
		public:
			const char* type;
			StaticObject(const char* imageFile, float scale, b2Vec2 pos, b2World* world, int wWidth, int wHeight);
			void render();
			void WindowResize(int wWidth, int wHeight);
			void resize(int width, int height);
			void startContact();
			void endContact();
			
			void _clean();
	};
}