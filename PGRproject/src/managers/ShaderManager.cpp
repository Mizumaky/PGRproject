#include "ShaderManager.h"
#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <vector>

using namespace managers;

std::map<std::string, GLuint> ShaderManager::s_programs; //yes i need this

ShaderManager::ShaderManager() = default;

ShaderManager::~ShaderManager() {
	//iterate through the program map (.second = the GLuint) and delete everything
	for (auto& program : s_programs) {
		glDeleteProgram(program.second);
	}
	s_programs.clear();
}


std::string ShaderManager::readShader(const std::string& filename) {
	//prepare file
	std::string shaderCode;
	std::ifstream file(filename.c_str(), std::ios::in);
	if (!file.good()) {
		std::cout << "ERROR: Can't read file " << filename << std::endl;
		std::terminate();
	}
	//find start and end
	file.seekg(0, std::ios::end);
	shaderCode.resize(static_cast<unsigned int>(file.tellg()));
	file.seekg(0, std::ios::beg);
	//read
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint ShaderManager::createShader(const GLenum shaderType, const std::string& source, const std::string& name) {
	//create shader handle and prepare the string
	const GLuint shader = glCreateShader(shaderType);
	const char* p_shaderSource = source.c_str();
	const int shaderCodeSize = source.size();
	//load source into opengl and compile
	glShaderSource(shader, 1, &p_shaderSource, &shaderCodeSize);
	glCompileShader(shader);
	int compileResult = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	//check for errors
	if (compileResult == GL_FALSE) {
		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, nullptr, &shaderLog[0]);
		std::cout << "ERROR: Can't compile shader: " << name << std::endl << &shaderLog[0] << std::endl;
		std::terminate();
	}
	return shader;
}

void ShaderManager::createProgram(const std::string& shaderName, const std::string& vsFilename, const std::string& fsFilename) {
	//check if program with this name already exists
	const std::map<std::string, GLuint>::iterator programsIterator = s_programs.find(shaderName);
	if (programsIterator != s_programs.end()) {
		std::cout << "ERROR: Shader program with name '" << shaderName << "' already exists" << std::endl;
		std::terminate();
	}
	//read the shader files and save the code
	const std::string vertexShaderCode = readShader(vsFilename);
	const std::string fragmentShaderCode = readShader(fsFilename);
	//compile the shaders
	const GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
	const GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");

	//create the program handle
	const GLuint program = glCreateProgram();
	//attach shaders
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	//link it
	glLinkProgram(program);
	int linkResult = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	//check for link errors
	if (linkResult == GL_FALSE) {
		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		std::cout << "ERROR: Can't link program" << std::endl << &programLog[0] << std::endl;
		std::terminate();
	}
	//add the shader program to the list (if not already present)
	s_programs[shaderName] = program;
}

GLuint ShaderManager::getShader(const std::string& shaderName) {
	const std::map<std::string, GLuint>::iterator programsIterator = s_programs.find(shaderName);
	if (programsIterator == s_programs.end()) {
		std::cout << "ERROR: Shader program with name '" << shaderName << "' doesn't exists" << std::endl;
		std::terminate();
	}
	return s_programs[shaderName];
}

void ShaderManager::deleteShader(const std::string& shaderName) {
	const auto& programsIterator = s_programs.find(shaderName);
	if (programsIterator == s_programs.end()) {
		std::cout << "ERROR: Shader program with name '" << shaderName << "' doesn't exists" << std::endl;
		std::terminate();
	}
	s_programs.erase(shaderName);
}

