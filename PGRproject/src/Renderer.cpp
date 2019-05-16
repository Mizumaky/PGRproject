#include "Renderer.h"

namespace mullemi5 {

	Renderer::Renderer() {
		//set default color when clearing view
		glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
		//enable depth buffer support
		glEnable(GL_DEPTH_TEST);
		//specify the rendering window
		glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}

	void Renderer::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		CHECK_GL_ERROR();
	}

	
	void Renderer::draw(const VertexArray& vao, const IndexBuffer& ibo, const ShaderProgram& shader) const {
		//bind everything in every call
		shader.bind();
		vao.bind();
		ibo.bind();

		//draw
		//glDrawArrays(GL_TRIANGLES, 0, 3); //if we wanna draw arrays directly
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); //if we wanna draw using indexes
		CHECK_GL_ERROR();
	}


}