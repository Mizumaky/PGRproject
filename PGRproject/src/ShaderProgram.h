#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "pgr.h"

namespace mullemi5 {

	class ShaderProgram {
	protected:
		GLuint m_id;
		GLuint m_vsShaderId;
		GLuint m_fsShaderId;
		GLuint m_gsShaderId;
		//std::unordered_map<std::string, int> m_uniformLocationCache;

	public:
		/**
		 * \brief Creates program from defined shader files
		 * \param vs_filepath Path to the vertex buffer file if to be used, empty string otherwise
		 * \param fs_filepath Path to the fragment buffer file if to be used, empty string otherwise
		 * \param gs_filepath Path to the geometry buffer file if to be used, empty string otherwise
		 */
		ShaderProgram(const std::string& vs_filepath, const std::string& fs_filepath, const std::string& gs_filepath);
		virtual ~ShaderProgram();

		void bind() const;
		void unbind() const;


		GLuint getId() const { return m_id; }
		// void setUniform1i(const std::string &name, int v0);
		// void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
		// void setUniformMat4f(const std::string &name, glm::mat4& matrix);
		// int getUniformLocation(const std::string &name);
	};

}