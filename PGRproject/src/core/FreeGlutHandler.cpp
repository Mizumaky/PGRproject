#include "FreeGlutHandler.h"
#include "IListener.h"
#include "WindowInfo.h"
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include <iostream>

using namespace core;

IListener* FreeGlutHandler::sp_listener = NULL;
WindowInfo FreeGlutHandler::s_windowInfo;

void FreeGlutHandler::init(
	const WindowInfo& windowInfo,
	const ContextInfo& contextInfo,
	const FrameBufferInfo& framebufferInfo)
{
	std::cout << "INFO: Initializing FreeGLUT..." << std::endl;
	//init with temporary fake arguments
	int fakeargc = 1;
	char *fakeargv[] = { const_cast<char*>("fake"), NULL };
	glutInit(&fakeargc, fakeargv);
	std::cout << "FreeGLUT version: " << std::to_string(glutGet(GLUT_VERSION)).insert(1, ".").insert(4, ".") << std::endl;

	//set up the window for opengl
	if (contextInfo.isCoreContext) {
		glutInitContextVersion(contextInfo.majorVersion, contextInfo.minorVersion);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	} else {
		// version is always the latest in compatibility profile
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}
	if (contextInfo.flags) {
		std::cout << "custom debug: setting context flags" << std::endl;
		glutInitContextFlags(contextInfo.flags);
	}
	glutInitDisplayMode(framebufferInfo.flags);
	glutInitWindowPosition(windowInfo.positionX, windowInfo.positionY);
	glutInitWindowSize(windowInfo.width, windowInfo.height);

	//create the window
	glutCreateWindow(windowInfo.name.c_str());
	s_windowInfo = windowInfo;
	std::cout << "INFO: GLUT window created" << std::endl;

	//these callbacks are used for rendering
	glutIdleFunc(idleCallback);
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);

	//setup cleanup
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

}

//MAIN FUNCTIONS

void FreeGlutHandler::setListener(IListener*& listener) {
	sp_listener = listener;
}


void FreeGlutHandler::run() {
	std::cout << "INFO: Starting FreeGLUT main loop..." << std::endl;
	glutMainLoop();
}

void FreeGlutHandler::close() {
	std::cout << "INFO: GLUT loop exit" << std::endl;
	glutLeaveMainLoop();
}

//CALLBACK FUNCTIONS

void FreeGlutHandler::idleCallback() {
	//update request for redrawing
	glutPostRedisplay();
}

void FreeGlutHandler::displayCallback() {
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (sp_listener) {
		sp_listener->notifyBeginFrame();
		sp_listener->notifyDisplayFrame();

		glutSwapBuffers();

		sp_listener->notifyEndFrame();
	} else {
		std::cout << "ERROR: Listener not registered before displayCallback" << std::endl;
	}
}

void FreeGlutHandler::reshapeCallback(int width, int height) {
	if (s_windowInfo.isReshapable) {
		if (sp_listener) {
			sp_listener->notifyReshape(
				width, height,
				s_windowInfo.width, s_windowInfo.height
			);
		}
		s_windowInfo.width = width;
		s_windowInfo.height = height;
	}
}

void FreeGlutHandler::closeCallback() {
	close();
}

//SIDE FUNCTIONS

void FreeGlutHandler::enterFullscreen() {
	glutFullScreen();
}

void FreeGlutHandler::exitFullscreen() {
	glutLeaveFullScreen();
}

void FreeGlutHandler::printOpenglInfo(const ContextInfo& contextInfo) {
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "*******************************************************************************" << std::endl;

	std::cout << "-- Current OpenGL context info --" << std::endl;
	std::cout << "GL:\tVendor : " << vendor << std::endl;
	std::cout << "GL:\tRenderer : " << renderer << std::endl;
	std::cout << "GL:\tOpenGL version: " << version << std::endl;
	std::cout << "GL:\tOpenGL context: " << contextInfo.majorVersion << "." << contextInfo.minorVersion;
	std::cout << " " << ((contextInfo.isCoreContext) ? "CORE" : "COMPATIBILITY") << " profile" << std::endl;

	std::cout << "*****************************************************************" << std::endl;
}