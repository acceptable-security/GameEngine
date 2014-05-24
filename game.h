#include <stdlib.h>
#include <glut.h>
#include "world.h"

namespace GameEngine {
	class Game {
		private:
			char* title;
			
			int originalWindowWidth;
			int originalWindowHeight;
			
			int windowWidth;
			int windowHeight;
			
			int windowPosX;
			int windowPosY;
			
			bool keys[4];
	
			int refreshMillis;
			int base_time;
			int fps;
			int frames;
	
			World universe;
		
			bool fullScreenMode;
			
			int argc;
			char** argv;
	
		public:
			Game();
			Game(char* title, int windowWidth, int windowHeight, int argc, char** argv);
	
			void begin();
			void initGL();
			void initGame();
	
			void keyboardDown(unsigned char key, int x, int y);
			void keyboardUp(unsigned char key, int x, int y);
			void specialKeys(int key, int x, int y);
			void mouse(int button, int state, int x, int y);
	
			void timer(int value);
	
			void display();
			void reshape(GLsizei width, GLsizei height);
	
			void calculateFrameRate();
			float getFrameRate();

			World* getWorld() { printf("G %d\n", &universe); return &universe; };
	};
	Game NewGame(char* title, int windowWidth, int windowHeight, int argc, char** argv);
}