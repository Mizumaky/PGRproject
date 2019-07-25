#include "GameModels.h"
#include "VertexFormat.h"
#include <GL/glew.h>
#include <string>
#include <iostream>

using namespace models;

GameModels::GameModels() = default;

GameModels::~GameModels() {
	//delete VAO and VBOs (if any)
	for (auto& iterator : gameModelList) {
		glDeleteVertexArrays(1, &iterator.second.vao); //glDeleteVertexArrays(GLsizei n, const GLuint* arrays);
		glDeleteBuffers(iterator.second.vbos.size(), &iterator.second.vbos[0]); //glDeleteBuffers(GLsizei n, const GLuint* buffers);
		iterator.second.vbos.clear();
	}
	gameModelList.clear();
}

void GameModels::createTriangleModel(const std::string& gameModelName) {
	//generate and bind vao
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//prepare vertex content
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(0.25, -0.25, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.25, 0.0)));
	//generate, bind and fill vbo(s)
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	//add model to the list
	Model myModel;
	myModel.vao = vao;
	myModel.vbos.push_back(vbo);
	gameModelList[gameModelName] = myModel;
}

void GameModels::deleteModel(const std::string& gameModelName) {
	const auto& programsIterator = gameModelList.find(gameModelName);
	if (programsIterator == gameModelList.end()) {
		std::cout << "ERROR: Model with name " << gameModelName << " doesn't exists" << std::endl;
		std::terminate();
	}
	Model model = gameModelList[gameModelName];
	glDeleteVertexArrays(1, &model.vao);
	glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
	model.vbos.clear();
	gameModelList.erase(gameModelName);
}

GLuint GameModels::getModelVao(const std::string& gameModelName) {
	const auto& programsIterator = gameModelList.find(gameModelName);
	if (programsIterator == gameModelList.end()) {
		std::cout << "ERROR: Model with name " << gameModelName << " doesn't exists" << std::endl;
		std::terminate();
	}
	return gameModelList[gameModelName].vao;
}
