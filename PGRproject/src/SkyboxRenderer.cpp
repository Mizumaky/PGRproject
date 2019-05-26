#include "SkyboxRenderer.h"
#include "Texture.h"
#include <iostream>

namespace mullemi5 {

	void SkyboxRenderer::initShader() {
		m_shader = new ShaderProgram("res/shaders/skybox.vert", "res/shaders/skybox.frag", "");
		// get handles to vertex attributes locations
		m_screenCoordLocation = glGetAttribLocation(m_shader->getId(), "screenCoord");
		// uniforms locations
		m_skyboxSamplerLocation = glGetUniformLocation(m_shader->getId(), "skyboxSampler");
		m_inversePVmatrixLocation = glGetUniformLocation(m_shader->getId(), "inversePVmatrix");
	}

	void SkyboxRenderer::initGeometry() {
		// GEOMETRY
		//m_shader->bind(); //TODO uncomment?
		// 2D coordinates of 2 triangles covering the whole screen (NDC), draw using triangle strip
		static const float screenCoords[] = {
		  -1.0f, -1.0f,
		   1.0f, -1.0f,
		  -1.0f,  1.0f,
		   1.0f,  1.0f
		};
		//prepare an array (object) for multiple buffer x attribpointer settings
		m_geometry.vao = new VertexArray();
		//prepare the vertex buffer to set
		m_geometry.vbo = new VertexBuffer(screenCoords, sizeof(screenCoords));
		//prepare layout for the buffer and bind it to the buffer using vao (needs to be done after vao and vbo)
		auto layout = new VertexBufferLayout();
		layout->push<float>(2); //our data structure is positions defined by 2 floats
		m_geometry.vao->addBuffer(m_geometry.vbo, layout);


		// TEXTURES //TODO REWRITE INTO MY CODE
		m_geometry.triangleCount = 2;

		glActiveTexture(GL_TEXTURE0);

		glGenTextures(1, &(m_geometry.texture));
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_geometry.texture);

		const char * suffixes[] = { "posx", "negx", "posy", "negy", "posz", "negz" };
		GLuint targets[] = {
		  GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		  GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		  GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
		};

		for (int i = 0; i < 6; i++) {
			std::string texName = std::string("res/textures/skybox_") + suffixes[i] + ".png";
			std::cout << "Loading cube map texture: " << texName << std::endl;
			if (!pgr::loadTexImage2D(texName, targets[i])) {
				pgr::dieWithError("Skybox cube map loading failed!");
			}
		}

		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

		// unbind the texture (just in case someone will mess up with texture calls later)
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		//m_shader->unbind();
	}

	void SkyboxRenderer::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
		m_shader->bind();

		// compose transformations
		glm::mat4 matrix = projectionMatrix * viewMatrix;

		// crate view rotation matrix by using view matrix with cleared translation
		glm::mat4 viewRotation = viewMatrix;
		viewRotation[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		// vertex shader will translate screen space coordinates (NDC) using inverse PV matrix
		glm::mat4 inversePVmatrix = glm::inverse(projectionMatrix * viewRotation);


		//TODO
		glUniformMatrix4fv(m_inversePVmatrixLocation, 1, GL_FALSE, glm::value_ptr(inversePVmatrix));
		glUniform1i(m_skyboxSamplerLocation, 0);

		// draw "skybox" rendering 2 triangles covering the far plane
		m_geometry.vao->bind();
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_geometry.texture); //TODO
		glDrawArrays(GL_TRIANGLE_STRIP, 0, m_geometry.triangleCount + 2);

		m_geometry.vao->unbind();
		m_shader->unbind();
	}


}
