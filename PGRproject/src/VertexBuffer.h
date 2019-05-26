#pragma once
namespace mullemi5 {

	class VertexBuffer {
	private:
		unsigned int m_rendererId; //id of the buffer in our renderer aka opengl
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void bind() const;
		void unbind() const;
	};

}