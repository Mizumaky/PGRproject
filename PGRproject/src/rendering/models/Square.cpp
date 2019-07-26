#include "Square.h"

using namespace rendering;
using namespace models;

Square::Square() = default;
Square::~Square() = default;

void Square::create() {
	//generate and bind vao
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//prepare vertex content
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(-0.25, 0.5, 0.0),//pos
		glm::vec4(0, 1, 0, 1)));   //color
	vertices.push_back(VertexFormat(glm::vec3(-0.25, 0.75, 0.0),//pos
		glm::vec4(0, 0, 0, 1)));   //color
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.5, 0.0),  //pos
		glm::vec4(1, 0, 0, 1)));   //color
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.75, 0.0),//pos
		glm::vec4(0, 0, 1, 1)));   //color
	//generate, bind and fill vbo(s)
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);            
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
		sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glBindVertexArray(0);
	//assign
	this->m_vao = vao;
	this->m_vbos.push_back(vbo);
}

void Square::update() {
	//nothing
}

void Square::draw() {
	glUseProgram(m_program);
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}