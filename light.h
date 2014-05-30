#include <GL/glew.h>
#include <Box2D/Box2D.h>
#include "world.h"
#include <glut.h>
namespace GameEngine {
	class Light {
		private:
			int x, y;
			float r, g, b, a;
			World* world;
			int windowWidth;
			int windowHeight;
			GLuint shader;
		public:
			Light() {};
			Light(World* world, int x, int y, float r, float g, float b, int worldWidth, int worldHeight, GLuint shader);
	
			void render();
			void clean();
	};
}