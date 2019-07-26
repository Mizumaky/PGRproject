#include "ModelsManager.h"
#include <iostream>
#include "../rendering/models/Square.h"

using namespace managers;
using namespace rendering;

ModelsManager::ModelsManager() {
	//load all models:
	//triangle
	auto* triangle = new models::Triangle();
	triangle->setProgram(ShaderManager::getShader("simple"));
	triangle->create();
	m_gameModelList["triangle"] = triangle;
	//square
	auto* square = new models::Square();
	square->setProgram(ShaderManager::getShader("simple"));
	square->create();
	m_gameModelList["square"] = square;
}

ModelsManager::~ModelsManager() {
	for (const auto& model : m_gameModelList) {
		delete model.second;
	}
	m_gameModelList.clear();
}

void ModelsManager::update() {
	for (auto model : m_gameModelList) {
		model.second->update();
	}
}

void ModelsManager::draw() {
	for (auto model : m_gameModelList) {
		model.second->draw();
	}
}

void ModelsManager::deleteModel(const std::string& gameModelName) {
	checkModelExistence(gameModelName);
	IGameObject* model = m_gameModelList[gameModelName];
	model->destroy();
	m_gameModelList.erase(gameModelName);
}

const IGameObject& ModelsManager::getModel(const std::string& gameModelName) const {
	checkModelExistence(gameModelName);
	return (*m_gameModelList.at(gameModelName));
}

void ModelsManager::checkModelExistence(const std::string& gameModelName) const {
	const auto& modelsIterator = m_gameModelList.find(gameModelName);
	if (modelsIterator == m_gameModelList.end()) {
		std::cout << "ERROR: Model with name " << gameModelName << " doesn't exists" << std::endl;
		std::terminate();
	}
}