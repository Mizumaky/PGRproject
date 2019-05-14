#include "VertexBuffer.h"
#include "pgr.h"
namespace mullemi5 {

	VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
		//prepare an array buffer
		glGenBuffers(1, &m_rendererID); //generate
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID); //bind - this is the buffer we will be currently setting stuff to 
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); //prepare the storage for data, also STATIC DRAW indicates to opengl that the data will be written only like once, but read often, and will be used for drawing
		CHECK_GL_ERROR();
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_rendererID);
		CHECK_GL_ERROR();
	}

	void VertexBuffer::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		CHECK_GL_ERROR();
	}

	void VertexBuffer::unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		CHECK_GL_ERROR();
	}

}