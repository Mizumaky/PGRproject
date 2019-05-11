#include <iostream>;
#include "pgr.h";

const char *WIN_TITLE = "TestProject2";
const int WIN_WIDTH = 512;
const int WIN_HEIGHT = 512;

void initShaders() {

}

void draw() {

}

int main(int argc, char** argv) {
	std::cout << "Application started" << std::endl;
	//GLUT LIBRARY INITIALIZATION
	glutInit(&argc, argv);
	glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	//GLUT WINDOW INITIALIZATION
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutCreateWindow(WIN_TITLE);
	//SET THE DRAW FUNCTION
	glutDisplayFunc(draw);
	//CONTROL CHECK
	if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
		pgr::dieWithError("pgr init failed, required OpenGL not supported?");
	//INITIALIZE SHADERS
	initShaders();
	//START THE APPLICATION LOOP
	glutMainLoopEvent();
	//AFTER USER EXITS THE APP WINDOW
	std::cout << "Bye ^^" << std::endl;
	Sleep(2000);
	return 0;
}