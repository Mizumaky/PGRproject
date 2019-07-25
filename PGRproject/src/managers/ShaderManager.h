#pragma once
#include <string>
#include <map>
#include <GL/glew.h>

namespace managers {

	class ShaderManager {
	public:
		ShaderManager();
		virtual ~ShaderManager();
		//custom constructor for an OpenGL program
		static void createProgram(const std::string& shaderName, const std::string& vsFilename, const std::string& fsFilename);
		//returns GLuint of selected shader
		static GLuint getShader(const std::string& shaderName);
		static void deleteShader(const std::string& shaderName);

	private:
		static std::string readShader(const std::string& filename);
		static GLuint createShader(GLenum shaderType, const std::string& source, const std::string& name);
		static std::map<std::string, GLuint> s_programs;
	};

}
