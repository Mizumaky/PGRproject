#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include <string>
#include "managers/ShaderManager.h"
#include "rendering/VertexFormat.h"
#include "rendering/GameModels.h"
#include <glm/glm.hpp>
#include "core/WindowInfo.h"
#include "core/ContextInfo.h"
#include "core/FrameBufferInfo.h"
#include "core/FreeGlutHandler.h"
#include "core/GlewHandler.h"
#include "managers/SceneManager.h"
#include "core/IListener.h"

/********************************************************
Miroslav Muller 2019
Inspired by http://in2gpu.com/opengl-3/
*********************************************************/

//models::GameModels* g_gameModels;

//void renderScene() {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	//code
//	glUseProgram(managers::ShaderManager::getShader("simple"));
//	glDrawArrays(GL_TRIANGLES, 0, 3);
//
//	glutSwapBuffers();
//}
//
//void initApp() {
//	g_gameModels = new models::GameModels();
//	g_gameModels->createTriangleModel("triangle1");
//
//	//load and compile shaders
//	managers::ShaderManager::createProgram("simple", "src/shaders/simple.vert", "src/shaders/simple.frag");
//}


int main(int argc, char** argv) {
	std::cout << "Application started" << std::endl;
	core::WindowInfo windowInfo(
		"SteampunkTheater",
		800, 600,
		400, 200,
		true
	);
	core::ContextInfo contextInfo(
		3, 1,
		true, false, true
	);
	core::FrameBufferInfo frameBufferInfo(
		true, true, true, true, true
	);

	//INITIALIZE FreeGLUT - init window and OpenGL context
	core::FreeGlutHandler::init(windowInfo, contextInfo, frameBufferInfo);
	core::FreeGlutHandler::printOpenglInfo(contextInfo);

	//INITIALIZE GLEW - init OpenGL extensions
	core::GlewHandler::init();

	//INITIALIZE APPLICATION - create game managers and prepare OpenGL
	core::IListener* scene = new managers::SceneManager();
	core::FreeGlutHandler::setListener(scene);

	//START THE APPLICATION LOOP
	core::FreeGlutHandler::run();

	//FINISHING CODE AND CLEANUP
	std::cout << "INFO: Finishing..." << std::endl;
	//delete g_gameModels;
	delete scene;
	Sleep(1000);
	return 0;
}