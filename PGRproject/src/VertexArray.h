#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
namespace mullemi5 {

	class VertexArray {
	private:
		unsigned int m_rendererId;
	public:
		VertexArray();
		~VertexArray();

		void bind() const;
		void unbind() const;
		void addBuffer(const VertexBuffer* vbo, const VertexBufferLayout* layout);
	};

}