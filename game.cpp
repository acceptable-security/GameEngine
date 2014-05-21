#include "game.h"

namespace GameEngine {
	void _display_redirect() {
		gameObject.display();
	}
 
	void _reshape_redirect(GLsizei width, GLsizei height) {
		gameObject.reshape(width, height);
	}
 

	void _timer_redirect(int value) {
		gameObject.timer(value);
	}

	void _keyboardUp_redirect(unsigned char key, int x, int y) {
		gameObject.keyboardUp(key, x, y);
	}

	void _keyboardDown_redirect(unsigned char key, int x, int y) {
		gameObject.keyboardDown(key, x, y);
	}

	void _specialKeys_redirect(int key, int x, int y) {
		gameObject.specialKeys(key, x, y);
	}
 
	void _mouse_redirect(int button, int state, int x, int y) {
		gameObject.mouse(button, state, x, y);
	}

	Game::Game() {

	}

	Game::Game(char* _title, int width, int height, int _argc, char** _argv) {
		title = _title;
	
		originalWindowWidth = width;
		originalWindowHeight = height;
	
		windowWidth  = originalWindowWidth;
		windowHeight = originalWindowHeight;

		windowPosX	= 50;
		windowPosY	= 50;

		argc = _argc;
		argv = _argv;
	
		refreshMillis = 15.0f;
		base_time = 0;
		fps = 0;
		frames = 0;

		fullScreenMode = false;
	}

	void Game::begin() {
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glOrtho(0.0f,windowWidth,0.0f,windowHeight,0.0f,1.0f);
		glClearColor(0.3, 0.3, 0.3, 0.3);
		GLenum error = glGetError();
		if(error != GL_NO_ERROR) {
			printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
			exit(0);
		}
		keys[0] = false;
		keys[1] = false;
		keys[2] = false;
		keys[3] = false;
	
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE); 
		glutInitWindowSize(windowWidth, windowHeight);
		glutInitWindowPosition(windowPosX, windowPosY); 
		glutCreateWindow(title);
		glutDisplayFunc(_display_redirect);
		glutReshapeFunc(_reshape_redirect);
		glutTimerFunc(0, _timer_redirect, 0);
		glutSpecialFunc(_specialKeys_redirect);
		glutKeyboardUpFunc(_keyboardUp_redirect);	
		glutKeyboardFunc(_keyboardDown_redirect);
		if(fullScreenMode)
			glutFullScreen();
		glutMouseFunc(_mouse_redirect);

		B2_NOT_USED(argc);
		B2_NOT_USED(argv);

		glutMainLoop();
	}

	void Game::initGame() {
	}

	void Game::keyboardDown(unsigned char key, int x, int y) {
	}
	
	void Game::keyboardUp(unsigned char key, int x, int y) {
	}
	
	void Game::specialKeys(int key, int x, int y) {
	}

	void Game::mouse(int button, int state, int x, int y) {
	}
	
	void Game::timer(int value) {
	}
	
	void Game::display() {
	}
	
	void Game::reshape(GLsizei width, GLsizei height) {
	}
	
	void Game::calculateFrameRate() {
	}
	
	void Game::getFrameRate() {
	}

	Game NewGame(char* title, int windowWidth, int windowHeight, int argc, char** argv) {
		return Game(title, windowWidth, windowHeight, argc, argv);
	}
}