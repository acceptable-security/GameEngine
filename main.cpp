#include <stdlib.h>
#include <glut.h>
#include <Math.h>
#include <Box2D/Box2D.h>
#include "player_object.h"
#include "spritesheets.h"
#include "render_list.h"

#define PI 3.14159265f


// Global variables
char title[] = "Blockland Forums: The Game";
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


b2Vec2 gravity(0.0f, -10.0f);
b2World world(gravity);

PlayerObject player(25.0f, 25.0f, 50.0f, 300.0f, 1.0f, 0.0f, 1.0f, &world, windowWidth, windowHeight);
RenderList renderList;
SpriteSheet sprite;

bool fullScreenMode = false;

StaticObject* createStaticObject(b2Vec2 position, const char* imageFile, float scale) { //
	return new StaticObject(imageFile, scale, position, &world, windowWidth, windowHeight);
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

void addMoreBlocks(int x, int y) {
	DynamicObject* obj = new DynamicObject("box.png", 1.0f, b2Vec2(x,y), &world, windowWidth, windowHeight);
	renderList.add(obj);
}

void display() {
	frames++;
	CalculateFrameRate();
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	player.update(keys[0], keys[1], keys[2], keys[3]);
	renderList.render();
	sprite.render("test", 100.0f, 100.0f, 0.0f, 1.0f);
	player.render();

	glutSwapBuffers();
	world.Step(1.0f/60.0f, 6, 2);
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
		case GLUT_KEY_RIGHT:
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
			break;
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
		addMoreBlocks(x, windowHeight - y);
		printf("Mouse clicked %d (%d,%d)\n", state, x, y);
	}
}
void initGL(int argc, char** argv) {

	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0f,windowWidth,0.0f,windowHeight,0.0f,1.0f);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	GLenum error = glGetError();
	if(error != GL_NO_ERROR) {
		printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
		exit(0);
	}
}

void initGame() {
	renderList.add(createStaticObject(b2Vec2(10,10), "box.png", 2.0f));
	sprite = "box.png";
	sprite.initSequence("test", 1000.0f, 35.0f, 35.0f);
	sprite.addAnimationRow("test", 0, 2);
	//sprite.addSequenceFrame("test", b2Vec2(0.0f, 0.0f));
	//sprite.addSequenceFrame("test", b2Vec2(35.0f, 35.0f));
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
	printf("TEST");
	return 0;
}

