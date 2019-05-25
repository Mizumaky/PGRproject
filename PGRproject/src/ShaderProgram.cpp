#include "ShaderProgram.h"
#include "pgr.h"
#include <iostream>

namespace mullemi5 {

	ShaderProgram::ShaderProgram(const std::string& vs_filepath, const std::string& fs_filepath, const std::string& gs_filepath) {
		m_shadersRendererIds[0] = vs_filepath.empty() ? 0 : pgr::createShaderFromFile(GL_VERTEX_SHADER, vs_filepath);
		m_shadersRendererIds[1] = fs_filepath.empty() ? 0 : pgr::createShaderFromFile(GL_FRAGMENT_SHADER, fs_filepath);
		m_shadersRendererIds[2] = gs_filepath.empty() ? 0 : pgr::createShaderFromFile(GL_GEOMETRY_SHADER, gs_filepath);
		m_rendererId = pgr::createProgram(m_shadersRendererIds);
	}

	ShaderProgram::~ShaderProgram() {
		for (unsigned int shaderId : m_shadersRendererIds) {
			if (glIsShader(shaderId))
				glDeleteShader(shaderId);
		}
		glDeleteProgram(m_rendererId);
	}

	void ShaderProgram::bind() const {
		glUseProgram(m_rendererId);
	}

	void ShaderProgram::unbind() const {
		glUseProgram(0);
	}

	void ShaderProgram::setUniform1i(const std::string& name, int v0) {
		glUniform1i(getUniformLocation(name), v0);
	}
	void ShaderProgram::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
		glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
	}
	void ShaderProgram::setUniformMat4f(const std::string& name, glm::mat4& matrix) {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	int ShaderProgram::getUniformLocation(const std::string& name) {
		//check if we havent already cached it
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];
		//otherwise retrieve it
		const int location = glGetUniformLocation(m_rendererId, name.c_str());
		if (location == -1)
			std::cout << "OpenGL Warning: uniform \"" + name + "\" not found in the shader program" << std::endl;
		else
			m_uniformLocationCache[name] = location;

		return location;
	}

}
