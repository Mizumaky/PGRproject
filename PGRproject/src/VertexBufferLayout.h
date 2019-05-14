#pragma once
#include <vector>
#include "pgr.h"

namespace mullemi5 {
	//one buffer element corresponds to one vertex attribute
	struct VertexBufferElement {
		unsigned int type;
		unsigned int type_size;
		unsigned int count;
		unsigned char normalized;
	};

	class VertexBufferLayout {
	private:
		std::vector<VertexBufferElement> m_elements;
		unsigned int m_stride = 0;
	public:

		template<typename T>
		void push(unsigned int count) {
			static_assert(false);
		}
		template<>
		void push<float>(unsigned int count) {
			m_elements.push_back({ GL_FLOAT, sizeof(GLfloat), count, GL_FALSE });
			m_stride += count * sizeof(GLfloat);
		}
		template<>
		void push<unsigned int>(unsigned int count) {
			m_elements.push_back({ GL_UNSIGNED_INT, sizeof(GLuint), count, GL_FALSE });
			m_stride += count * sizeof(GLuint);
		}
		template<>
		void push<unsigned char>(unsigned int count) {
			m_elements.push_back({ GL_UNSIGNED_BYTE, sizeof(GLubyte), count, GL_TRUE });
			m_stride += count * sizeof(GLubyte);
		}

		inline const std::vector<VertexBufferElement>& getElements() const { return m_elements; }
		inline unsigned int getStride() const { return m_stride; }
	};
}
