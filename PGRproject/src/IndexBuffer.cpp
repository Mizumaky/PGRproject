#include "IndexBuffer.h"
#include "pgr.h"
namespace mullemi5 {

	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) {
		//prepare an array buffer
		glGenBuffers(1, &m_rendererId); //generate
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId); //bind - this is the buffer we will be currently setting stuff to 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW); //prepare the storage for data, also STATIC DRAW indicates to opengl that the data will be written only like once, but read often, and will be used for drawing
		m_count = count;
	}

	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &m_rendererId);
	}

	void IndexBuffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
	}

	void IndexBuffer::unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}