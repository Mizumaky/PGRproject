#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace mullemi5 {

	class ShaderProgram {
	private:
		unsigned int m_rendererId;
		unsigned int m_shadersRendererIds[3];
		std::unordered_map<std::string, int> m_uniformLocationCache;

	public:
		/**
		 * \brief Creates program from defined shader files
		 * \param vs_filepath Path to the vertex buffer file if to be used, empty string otherwise
		 * \param fs_filepath Path to the fragment buffer file if to be used, empty string otherwise
		 * \param gs_filepath Path to the geometry buffer file if to be used, empty string otherwise
		 */
		ShaderProgram(const std::string& vs_filepath, const std::string& fs_filepath, const std::string& gs_filepath);
		~ShaderProgram();

		void bind() const;
		void unbind() const;

		void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
		int getUniformLocation(const std::string &name);
	};

}