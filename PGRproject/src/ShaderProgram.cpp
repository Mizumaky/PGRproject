#include "ShaderProgram.h"
#include "pgr.h"
#include <iostream>

namespace mullemi5 {

	ShaderProgram::ShaderProgram(const std::string& vs_filepath, const std::string& fs_filepath, const std::string& gs_filepath) {
		m_shadersRendererIds[0] = vs_filepath.empty() ? 0 : pgr::createShaderFromFile(GL_VERTEX_SHADER, vs_filepath);
		m_shadersRendererIds[1] = fs_filepath.empty() ? 0 : pgr::createShaderFromFile(GL_FRAGMENT_SHADER, fs_filepath);
		m_shadersRendererIds[2] = gs_filepath.empty() ? 0 : pgr::createShaderFromFile(GL_GEOMETRY_SHADER, gs_filepath);
		m_rendererId = pgr::createProgram(m_shadersRendererIds);
		CHECK_GL_ERROR();
	}

	ShaderProgram::~ShaderProgram() {
		for (unsigned int shaderId : m_shadersRendererIds) {
			if (glIsShader(shaderId))
				glDeleteShader(shaderId);
		}
		glDeleteProgram(m_rendererId);
		CHECK_GL_ERROR();
	}

	void ShaderProgram::bind() const {
		glUseProgram(m_rendererId);
		CHECK_GL_ERROR();
	}

	void ShaderProgram::unbind() const {
		glUseProgram(0);
		CHECK_GL_ERROR();
	}

	void ShaderProgram::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
		glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
		CHECK_GL_ERROR();
	}

	int ShaderProgram::getUniformLocation(const std::string& name) {
		//check if we havent already cached it
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];
		//otherwise retrieve it
		const int location = glGetUniformLocation(m_rendererId, name.c_str());
		if (location == -1)
			std::cout << "OpenGL Warning: uniform" + name + " not found in the shader program" << std::endl;
		else
			m_uniformLocationCache[name] = location;

		CHECK_GL_ERROR();
		return location;
	}

}
