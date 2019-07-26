#include "GlewHandler.h"
#include <GL/glew.h>
#include <iostream>

using namespace core;

void GlewHandler::init() {
	std::cout << "INFO: Initializing GLEW..." << std::endl;
	glewExperimental = true;
	if (const GLenum err = glewInit() != GLEW_OK) {
		std::cout << "ERROR: " << glewGetErrorString(err) << std::endl;
		terminate();
	}
	std::cout << "GLEW version " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "GLEW check: Your GPU in current context fully supports features up to: ";
	if (glewIsSupported("GL_VERSION_4_6"))
		std::cout << "GL version 4.6" << std::endl;
	else if (glewIsSupported("GL_VERSION_4_5"))
		std::cout << "GL version 4.5" << std::endl;
	else if (glewIsSupported("GL_VERSION_4_4"))
		std::cout << "GL version 4.4" << std::endl;
	else if (glewIsSupported("GL_VERSION_4_3"))
		std::cout << "GL version 4.3" << std::endl;
	else if (glewIsSupported("GL_VERSION_4_2"))
		std::cout << "GL version 4.2" << std::endl;
	else if (glewIsSupported("GL_VERSION_4_1"))
		std::cout << "GL version 4.1" << std::endl;
	else if (glewIsSupported("GL_VERSION_4_0"))
		std::cout << "GL version 4.0" << std::endl;
	else if (glewIsSupported("GL_VERSION_3_3"))
		std::cout << "GL version 3.3" << std::endl;
	else if (glewIsSupported("GL_VERSION_3_2"))
		std::cout << "GL version 3.2" << std::endl;
	else if (glewIsSupported("GL_VERSION_3_1"))
		std::cout << "GL version 3.1" << std::endl;
	else if (glewIsSupported("GL_VERSION_3_0"))
		std::cout << "GL version 3.0" << std::endl;
	else if (glewIsSupported("GL_VERSION_2_1"))
		std::cout << "GL version 2.1" << std::endl;
	else if (glewIsSupported("GL_VERSION_2_0"))
		std::cout << "GL version 2.0" << std::endl;
	else if (glewIsSupported("GL_VERSION_1_5"))
		std::cout << "GL version 1.5" << std::endl;
	else if (glewIsSupported("GL_VERSION_1_4"))
		std::cout << "GL version 1.4" << std::endl;
	else if (glewIsSupported("GL_VERSION_1_3"))
		std::cout << "GL version 1.3" << std::endl;
	else
		std::cout << "N/A" << std::endl;
}
