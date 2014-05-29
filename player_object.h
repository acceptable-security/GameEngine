#include "spritesheets.h"
#include <Box2D/Box2D.h>
namespace GameEngine {
	class PlayerObject {
		private:
			b2BodyDef bodyDef;
			b2Body* body;
			b2PolygonShape box;
			b2Vec2 vertices[4];
			b2FixtureDef fixtureDef;

			char* direction;
			int winWidth, winHeight;
			int termX;

			void* b2DataPtr;
		protected:
			SpriteSheet sprites;
			int x, y;
			char* state;
			float scale;

			void clean();
		public:
			const char* type;
			PlayerObject();
			PlayerObject(SpriteSheet* sprites, float scale, float x, float y, b2World* world, int wWidth, int wHeight);
			void render();
			void WindowResize(int wWidth, int wHeight);
			void SetPosition(int x, int y);
			void resize(float scale);
			void debug();
			void endContact();
			void startContact();
			void update(bool up, bool down, bool left, bool right);
			void _clean();
	};
}