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
		//other functions
		static GLuint getShader(const std::string& shaderName);
		static void deleteShader(const std::string& shaderName);

	private:
		//map with all the programs
		static std::map<std::string, GLuint> s_programs;
		//helper functions
		static std::string readShader(const std::string& filename);
		static GLuint createShader(GLenum shaderType, const std::string& source, const std::string& name);
	};

}
