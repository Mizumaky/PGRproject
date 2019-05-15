#include <iostream>
#include <string>
#include "pgr.h"
#include "definitions.h"
#include "Model.h"
#include "../res/hardcodedgraphics.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

namespace mullemi5 {

	Model model;

	float blue = 0.0f;
	float increment = 0.05f;

	ShaderProgram* program;
	VertexArray* vao;
	VertexBuffer* vbo;
	IndexBuffer* ibo;

	void initApp() {
		//set default color when clearing view
		glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
		//enable depth buffer support
		glEnable(GL_DEPTH_TEST);
		//specify the rendering window
		glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

		program = new ShaderProgram("res/shaders/basic.vert", "res/shaders/basic.frag", "" );
		program->bind();

		//prepare an array (object) for multiple buffer x attribpointer settings
		vao = new VertexArray();
		//prepare the vertex buffer to set
		vbo = new VertexBuffer(positions, sizeof(positions));
		//prepare layout for the buffer and bind it to the buffer using vao
		auto layout = new VertexBufferLayout();
		layout->push<float>(2); //our data structure is just positions defined by 2 floats
		vao->addBuffer(vbo, layout);

		//GLint positionLoc = glGetAttribLocation(shaderProgram, "position"); //TODO -- will i need this in the future?

		//prepare an index buffer
		ibo = new IndexBuffer(indices, 6);

		//possibly set one time uniforms

		//Unbind everything at the end (not needed)
		program->unbind();
		vao->unbind();
		vbo->unbind();
		ibo->unbind();
		CHECK_GL_ERROR();
	}

	void drawCallback() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//bind everything in every call
		program->bind();
		vao->bind();
		ibo->bind();

		//set uniforms (needs to be done after shader binding by useProgram)
		program->setUniform4f("u_Color", 1.0f, 0.7f, blue, 1.0f);

		//change color over time
		if (blue > 1.0f || blue < 0.0f)
			increment = -increment;
		blue += increment;

		//glDrawArrays(GL_TRIANGLES, 0, 3); //if we wanna draw arrays directly
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); //if we wanna draw using indexes

		CHECK_GL_ERROR();

		glutSwapBuffers();
	}
	
	void winResizeCallback(int width, int height) {

	}

	void finalizeApplication() {
		delete program;
	}
}

using namespace mullemi5;

int main(int argc, char** argv) {
	std::cout << "Application started" << std::endl;
	//GLUT LIBRARY INITIALIZATION
	glutInit(&argc, argv);
	glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR); //context = instance of opengl, think of it like object in which all states n stuff from opengl are
	glutInitContextProfile(GLUT_CORE_PROFILE); //to assert newer conventions n stuff - MY OWN ADDED LINE DONT FORGET!
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	//GLUT WINDOW INITIALIZATION
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	//glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//glutCloseFunc(finalizeApplication);
	glutCreateWindow(WIN_TITLE);

	//SET DRAW CALLBACK FUNCTION
	glutDisplayFunc(drawCallback);
	//SET WINDOW RESIZE CALLBACK FUNTION
	//glutReshapeFunc(winResizeCallback);
	//SET INPUT CALLBACK FUNCTIONS
	//glutKeyboardFunc(keyboardCallback);
	//glutKeyboardUpFunc(keyboardUpCallback);
	//glutSpecialFunc(specialKeyboardCallback);     // key pressed
	//glutSpecialUpFunc(specialKeyboardUpCallback); // key released
	//glutMouseFunc(mouseCallback);
	//SET TIMER CALLBACK FUNCTION
	//glutTimerFunc(33, timerCallback, 0);

	//PGR FRAMEWORK INITIALIZATION (GL, DevIl, etc.)
	if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
		pgr::dieWithError("pgr init failed, required OpenGL not supported?");
	//INITIALIZE APPLICATION (shaders and stuff)
	initApp();
	//START THE APPLICATION LOOP
	glutMainLoop();
	return 0;
}

