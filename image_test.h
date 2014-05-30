#ifndef imgtest
#define imgtest
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