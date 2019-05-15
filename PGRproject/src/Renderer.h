#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

namespace mullemi5 {

	class Renderer {


	public:
		void draw(const VertexArray& vao, const IndexBuffer& ibo, const ShaderProgram& shader) const;
	};

}