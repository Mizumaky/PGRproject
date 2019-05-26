#include "ShaderProgram.h"
#include "pgr.h"
#include <iostream>

namespace mullemi5 {

	ShaderProgram::ShaderProgram(const std::string& vs_filepath, const std::string& fs_filepath, const std::string& gs_filepath) {
		std::vector<GLuint> shaderList;
		if (!vs_filepath.empty()) {
			m_vsShaderId = pgr::createShaderFromFile(GL_VERTEX_SHADER, vs_filepath);
			shaderList.push_back(m_vsShaderId);
		} else {
			m_vsShaderId = 0;
		}
		if (!fs_filepath.empty()) {
			m_fsShaderId = pgr::createShaderFromFile(GL_FRAGMENT_SHADER, fs_filepath);
			shaderList.push_back(m_fsShaderId);
		} else {
			m_fsShaderId = 0;
		}
		if (!gs_filepath.empty()) {
			m_gsShaderId = pgr::createShaderFromFile(GL_GEOMETRY_SHADER, gs_filepath);
			shaderList.push_back(m_gsShaderId);
		} else {
			m_vsShaderId = 0;
		}
		m_id = pgr::createProgram(shaderList);
	}

	ShaderProgram::~ShaderProgram() {
		if (glIsShader(m_vsShaderId))
			glDeleteShader(m_vsShaderId);
		if (glIsShader(m_fsShaderId))
			glDeleteShader(m_fsShaderId);
		if (glIsShader(m_gsShaderId))
			glDeleteShader(m_gsShaderId);
		glDeleteProgram(m_id);
	}

	void ShaderProgram::bind() const {
		glUseProgram(m_id);
	}

	void ShaderProgram::unbind() const {
		glUseProgram(0);
	}
	//
	// void ShaderProgram::setUniform1i(const std::string& name, int v0) {
	// 	glUniform1i(getUniformLocation(name), v0);
	// }
	// void ShaderProgram::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	// 	glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
	// }
	// void ShaderProgram::setUniformMat4f(const std::string& name, glm::mat4& matrix) {
	// 	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	// }

	// int ShaderProgram::getUniformLocation(const std::string& name) {
	// 	//check if we havent already cached it
	// 	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
	// 		return m_uniformLocationCache[name];
	// 	//otherwise retrieve it
	// 	const int location = glGetUniformLocation(m_id, name.c_str());
	// 	if (location == -1)
	// 		std::cout << "OpenGL Warning: uniform \"" + name + "\" not found in the shader program" << std::endl;
	// 	else
	// 		m_uniformLocationCache[name] = location;
	//
	// 	return location;
	// }

}
