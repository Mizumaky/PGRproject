#include "VertexArray.h"

namespace mullemi5 {
	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_rendererId);
		CHECK_GL_ERROR();
	}
	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &m_rendererId);
		CHECK_GL_ERROR();
	}

	void VertexArray::bind() const {
		glBindVertexArray(m_rendererId);
		CHECK_GL_ERROR();
	}
	void VertexArray::unbind() const {
		glBindVertexArray(0);
		CHECK_GL_ERROR();
	}

	void VertexArray::addBuffer(const VertexBuffer* vbo, const mullemi5::VertexBufferLayout* layout) {
		bind(); //bind this VAO
		vbo->bind(); //bind the VBO we want it to bind to
		//setup the layout for the vertex attributes (elements) in it
		const auto& elements = layout->getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];
			//tell opengl how to read the data from the buffer and enable it for an attribute
			glEnableVertexAttribArray(i); //enable the assignment of the specified vertex attribute for the currently bound vertex array object / buffer
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout->getStride(), reinterpret_cast<const void*>(offset)); //define how the attribute is stored in there - point to them the right way
			//             attribute, how much, of what does it take, normalize it?, offset between each vertex (size of each vertex), offset where inside the vertex should we find it
			offset += element.count * element.type_size;
		}
		CHECK_GL_ERROR();
	}
}
