#include "SceneManager.h"
#include <iostream>

using namespace managers;

SceneManager::SceneManager() {
	//set OpenGL
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//connect shader manager and load all shaders:
	//simple
	m_shaderManager = new ShaderManager();
	m_shaderManager->createProgram(
		"simple",
		"src/shaders/simple.vert",
		"src/shaders/simple.frag"
	);

	//connect model manager (and load all models in it):
	m_modelsManager = new ModelsManager();
}

SceneManager::~SceneManager() {
	delete m_shaderManager;
	delete m_modelsManager;
}

void SceneManager::notifyBeginFrame() {
	m_modelsManager->update(); //update models according to current state
}

void SceneManager::notifyDisplayFrame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_modelsManager->draw();
}

void SceneManager::notifyEndFrame() {
	//nothing here for the moment
}

void SceneManager::notifyReshape(
	int width, int height,
	int previous_width, int previous_height
) {
	//nothing here for the moment 

}