#include <iostream>
#include <string>
#include "pgr.h"


// #include "external/imGui/imgui.h"
// #include "external/imGui/imgui_impl_glut.h"
// #include "external/imGui/imgui_impl_opengl3.h"
//teststtsts

namespace mullemi5 {

	struct GameState {
		int windowWidth = -1;    // set by reshape callback
		int windowHeight = -1;   // set by reshape callback

		bool camLock = true;
		float camPitchAngle = 0.0f; // in degrees = initially 0.0f
		float camYawAngle = 0.0f; // in degrees = initially 0.0f
		float camRollAngle = 0.0f; // in degrees = initially 0.0f

		bool gameOver = false;              // false;
		bool keyMap[KEYS_COUNT] = {false};    // false

		float lastCallTime = 0.0f;
		float currentTime = 0.0f;
	} gameState;

	struct ObjectClasses { //TODO probably move to renderer
		
	} objectClasses;

	struct GameObjectInstances {

	} gameObjectInstances;


	void restartGame() { //TODO TIME????

	}

	void drawCallback() {

	}
	
	void winResizeCallback(int width, int height) {

	}

	void passiveMouseMotionCallback(int mouseX, int mouseY) {

	}

	void keyboardCallback(unsigned char keyPressed, int mouseX, int mouseY) {

	}

	void updateGame() { //TODO
		//timeflow
		gameState.currentTime = 0.001f * (float)glutGet(GLUT_ELAPSED_TIME); // milliseconds => seconds
		float timeDelta = gameState.currentTime - gameState.lastCallTime;
	}

	void timerCallback(int) {
		//update objects over time
		updateGame();

		// set timeCallback next invocation
		glutTimerFunc(REFRESH_INTERVAL, timerCallback, 0);
		//send request for a display function (multiple requests dont stack up)
		glutPostRedisplay();
	}

	void finalizeApplication() {
		//delete shaderProgram;
	}

	void init() {
		//GLUT OPENGL STUFF INITIALIZATION
		glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR); //context = instance of opengl, think of it like object in which all states n stuff from opengl are
		glutInitContextProfile(GLUT_CORE_PROFILE); //to assert newer conventions n stuff - MY OWN ADDED LINE DONT FORGET!
		glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
		glutInitContextFlags(GLUT_DEBUG); //MY OWN ADDED FOR ALLOWING DEBUG MESSAGES (also needed to change in pgr.h)

		//GLUT WINDOW INITIALIZATION
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
		//glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
		glutCreateWindow(WIN_TITLE);

		//GLUT CALLBACK FUNCTIONS ASSIGNING
		glutDisplayFunc(drawCallback);
		glutReshapeFunc(winResizeCallback);
		glutKeyboardFunc(keyboardCallback);
		//glutKeyboardUpFunc(keyboardUpCallback);
		//glutSpecialFunc(specialKeyboardCallback);     // key pressed
		//glutSpecialUpFunc(specialKeyboardUpCallback); // key released
		glutPassiveMotionFunc(passiveMouseMotionCallback); //mouse moved without click
		glutWarpPointer(gameState.windowWidth / 2, gameState.windowHeight / 2); //move mouse position ^^
		//glutMouseFunc(mouseCallback);
		glutCloseFunc(finalizeApplication);
		glutTimerFunc(REFRESH_INTERVAL, timerCallback, 0);

		//PGR FRAMEWORK / OPENGL CONTEXT INITIALIZATION (GL, DevIl, etc.)
		if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
			pgr::dieWithError("pgr framework init failed, required OpenGL not supported?");
	}
}

using namespace mullemi5;

int main(int argc, char** argv) {
	std::cout << "Application started" << std::endl;
	//INITIALIZE APPLICATION
	glutInit(&argc, argv);
	init();

	//START THE APPLICATION LOOP
	glutMainLoop();
	return 0;
}

