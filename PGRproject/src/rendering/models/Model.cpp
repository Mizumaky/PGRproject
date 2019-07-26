#include "Model.h"

using namespace rendering;
using namespace models;

Model::Model() {}

Model::~Model() {
	destroy();
}

void Model::draw() {
	//this will be again overridden
}

void Model::update() {
	//this will be again overridden
}

void Model::setProgram(GLuint program) {
	this->m_program = program;
}

GLuint Model::getVao() const {
	return m_vao;
}

const std::vector<GLuint>& Model::getVbos() const {
	return m_vbos;
}

void Model::destroy() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(m_vbos.size(), &m_vbos[0]);
	m_vbos.clear();
}