#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include <string>
#include "managers/ShaderManager.h"
#include "rendering/VertexFormat.h"
#include "rendering/GameModels.h"
#include <glm/glm.hpp>

/********************************************************
Miroslav Muller 2019
Inspired by http://in2gpu.com/opengl-3/
*********************************************************/

#define WIN_WIDTH   800
#define WIN_HEIGHT  600

models::GameModels* g_gameModels;

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//code
	glUseProgram(managers::ShaderManager::getShader("simple"));
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void initApp() {
	g_gameModels = new models::GameModels();
	g_gameModels->createTriangleModel("triangle1");

	//load and compile shaders
	managers::ShaderManager::createProgram("simple", "src/shaders/simple.vert", "src/shaders/simple.frag");
}

void closeCallback() {
	glutLeaveMainLoop();
	std::cout << "INFO: GLUT loop exit" << std::endl;
}

int main(int argc, char** argv) {
	std::cout << "Application started" << std::endl;

	//INITIALIZE GLUT
	glutInit(&argc, argv);
	std::cout << "FreeGLUT version: " << std::to_string(glutGet(GLUT_VERSION)).insert(1, ".").insert(4, ".") << std::endl;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT); 
	glutInitContextVersion(4, 5);
	glutInitContextProfile(GLUT_CORE_PROFILE); //CORE or COMPATIBILITY (with some of the removed functions back)
	glutInitContextFlags(GLUT_DEBUG); //also possibly | GLUT_FORWARD_COMPATIBLE which disallows any function that is marked deprecated in this version
	glutCreateWindow("Steampunk Theater");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//INITIALIZE GLEW
	if (GLenum err = glewInit() != GLEW_OK) {
		std::cout << "ERROR: " << glewGetErrorString(err) << std::endl;
	}
	std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
	if (!glewIsSupported("GL_VERSION_4_5")) {
		std::cout << "WARNING: GLEW reports OpenGL 4.5 is not fully supported by your video card driver" << std::endl;
	}

	//INITIALIZE OPENGL
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//INITIALIZE APPLICATION
	initApp();

	//REGISTER GLUT CALLBACKS
	glutDisplayFunc(renderScene);
	glutCloseFunc(closeCallback);

	//START THE APPLICATION LOOP
	glutMainLoop();

	//FINISHING CODE AND CLEANUP
	std::cout << "INFO: Finishing..." << std::endl;
	delete g_gameModels;
	Sleep(1000);
	return 0;
}