#ifndef imgtest
#define imgtest
#define GL_CLAMP_TO_EDGE 0x812f
#include "stb_image.h"
#include <string>
#include <glut.h>
namespace GameEngine {
	class Image {
		private:
			GLuint textureID;
		public:
			int width, height;
			Image();
			Image(const char* fileName);
			
			virtual ~Image();
	
			void render(int x, int y, float angle, float scale);
	};
}
#else
namespace GameEngine {
	class Image;
}
#endif