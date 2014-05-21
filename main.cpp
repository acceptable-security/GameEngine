#include <stdlib.h>
#include <glut.h>
#include <Math.h>
#include <Box2D/Box2D.h>
#include "world.h"

#define PI 3.14159265f

// Global variables
char title[] = "Neglect";
int originalWindowWidth = 640;
int originalWindowHeight = 480;
int windowWidth  = originalWindowWidth;
int windowHeight = originalWindowHeight;
int windowPosX	= 50;
int windowPosY	= 50;
bool keys[4];

int refreshMillis = 15.0f;
int base_time = 0;
int fps = 0;
int frames = 0;

World universe;

bool fullScreenMode = false;

StaticObject* createStaticObject(b2Vec2 position, const char* imageFile, float scale) { //
	return new StaticObject(imageFile, scale, position, universe.getWorld(), windowWidth, windowHeight);
}

void CalculateFrameRate()
{
	int time = glutGet(GLUT_ELAPSED_TIME);
	if ((time - base_time) > 1000.0)
	{
		fps = frames*1000.0/(time - base_time);
		base_time = time;
		frames = 0;
		printf("FPS: %d\n", fps);
	}
}


void display() {
	frames++;
	CalculateFrameRate();
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	
	universe.update(keys[0], keys[1], keys[2], keys[3]);
	universe.render();

	glutSwapBuffers();
	
}
 
void reshape(GLsizei width, GLsizei height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	windowWidth = width;
	windowHeight = height;
	glOrtho(0.0f,windowWidth,0.0f,windowHeight,0.0f,1.0f);
	glViewport(0, 0, width, height);
}
 

void Timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(refreshMillis, Timer, 0);
}

void keyboardUp(unsigned char key, int x, int y) {
	switch (key) {
		case 'd':
			keys[3] = false;
			break;
		case 'a':
			keys[2] = false;
			break;
		case 'w':
			keys[0] = false;
			break;
		case 's':
			keys[1] = false; 
			break;
	}
}

void keyboardDown(unsigned char key, int x, int y) {
	switch (key) {
		case 'd':
			keys[3] = true;
			break;
		case 'a':
			keys[2] = true;
			break;
		case 'w':
			keys[0] = true;
			break;
		case 's':
			keys[1] = true; 
			break;
		case 27:	 // ESC key
			exit(0);
			break;
	}
}

void specialKeys(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_F1:
			fullScreenMode = !fullScreenMode;
			if (fullScreenMode) {
				originalWindowWidth = windowWidth;
				originalWindowHeight = windowHeight;
				windowPosX	= glutGet(GLUT_WINDOW_X);
				windowPosY	= glutGet(GLUT_WINDOW_Y);
				windowWidth  = glutGet(GLUT_WINDOW_WIDTH);
				windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
				reshape(windowWidth, windowHeight);
				glutFullScreen();

			}
			else {
				windowWidth = originalWindowWidth;
				windowHeight = originalWindowHeight;
				
				glutReshapeWindow(windowWidth, windowHeight);
				glutPositionWindow(windowPosX, windowPosX);
			}
			break;
		/*case GLUT_KEY_RIGHT:
			printf("RIGHT\n");
			keys[3] = true;
			break;
		case GLUT_KEY_LEFT:
			printf("LEFT\n");
			keys[2] = true;
			break;
		case GLUT_KEY_UP:
			printf("UP\n");
			keys[0] = true;
			break;
		case GLUT_KEY_DOWN:
			printf("DOWN\n");
			keys[1] = true; 
			break;*/
		case GLUT_KEY_PAGE_UP:
			//page up
			break;
		case GLUT_KEY_PAGE_DOWN:
			//page down
			break;
	}
}
 
void mouse(int button, int state, int x, int y) {
	if(!state) {
		//addMoreBlocks(x, windowHeight - y);
		printf("Mouse clicked %d (%d,%d)\n", state, x, y);
	}
}
void initGL(int argc, char** argv) {

	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0f,windowWidth,0.0f,windowHeight,0.0f,1.0f);
	glClearColor(0.3, 0.3, 0.3, 0.3);
	GLenum error = glGetError();
	if(error != GL_NO_ERROR) {
		printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
		exit(0);
	}
}

void initGame() {
	universe.addObject(createStaticObject(b2Vec2(10,10), "blue_square.png", 100.0f));

	SpriteSheet sprite("spritesheet.png");
	
	sprite.initSequence("idle", 60.0f, 9.0f, 14.0f);
	sprite.initSequence("run", 60.0f, 9.0f, 14.0f);
	sprite.initSequence("jump", 60.0f, 9.0f, 14.0f);
	sprite.initSequence("fall", 60.0f, 9.0f, 14.0f);
	
	sprite.addAnimationRow("idle", 0, 1);
	sprite.addAnimationRow("run", 1, 9);
	sprite.addAnimationRow("jump", 2, 1);
	sprite.addAnimationRow("fall", 2, 1);
	
	universe.setActivatePlayer(new PlayerObject(&sprite, 2.0f, 50.0f, 300.0f, universe.getWorld(), windowWidth, windowHeight));
}

int main(int argc, char** argv) {

	keys[0] = false;
	keys[1] = false;
	keys[2] = false;
	keys[3] = false;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); 
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY); 
	glutCreateWindow(title);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, Timer, 0);
	glutSpecialFunc(specialKeys);
	glutKeyboardUpFunc(keyboardUp);
	glutKeyboardFunc(keyboardDown);
	if(fullScreenMode)
		glutFullScreen();
	glutMouseFunc(mouse);

	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	initGL(argc, argv);
	initGame();
	
	glutMainLoop();
	return 0;
}

