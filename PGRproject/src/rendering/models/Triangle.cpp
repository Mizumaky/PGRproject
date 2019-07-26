#include "Triangle.h"
#include "../VertexFormat.h"

using namespace rendering;
using namespace models;

Triangle::Triangle() = default;
Triangle::~Triangle() = default; //deletion in Models.cpp (inheritance)

void Triangle::create() {
	//generate and bind vao
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//prepare vertex content
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(0.25, -0.25, 0.0),
		glm::vec4(1, 0, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0),
		glm::vec4(0, 1, 0, 1)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.25, 0.0),
		glm::vec4(0, 0, 1, 1)));
	//generate, bind and fill vbo(s)
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
		(void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 
		(void*)(offsetof(VertexFormat, VertexFormat::color))); //gets offset of a struct up to specified field
	glBindVertexArray(0);
	//assign the values
	this->m_vao = vao;
	this->m_vbos.push_back(vbo);
}

void Triangle::update() {
	//nothing
}

void Triangle::draw() {
	glUseProgram(m_program);
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}