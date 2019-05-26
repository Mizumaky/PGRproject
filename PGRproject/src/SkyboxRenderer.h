#pragma once
#include "pgr.h"
#include "ShaderProgram.h"
#include "structs.h"

namespace mullemi5 {

	class SkyboxRenderer {
	private:
		//shader program
		ShaderProgram* m_shader = nullptr;
		// vertex attributes locations
		GLint m_screenCoordLocation = -1;      // = -1;
		// uniforms locations
		GLint m_inversePVmatrixLocation = -1; // = -1;
		GLint m_skyboxSamplerLocation = -1;    // = -1;

		//geometry and material
		MeshGeometry m_geometry;
	public:
		void initShader();
		void initGeometry();
		void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

		//ShaderProgram* shader() const { return m_shader; }

	};

}
