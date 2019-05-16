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
#include "Renderer.h"
#include "Texture.h"


namespace mullemi5 {

	Model model;

	float blue = 0.0f;
	float increment = 0.05f;

	Renderer* renderer;
	ShaderProgram* shaderProgram;
	VertexArray* vao;
	VertexBuffer* vbo;
	IndexBuffer* ibo;
	Texture* texture;

	void initApp() {
		renderer = new Renderer();

		shaderProgram = new ShaderProgram("res/shaders/basic.vert", "res/shaders/basic.frag", "" );
		shaderProgram->bind();
		//possibly set one time uniforms
		shaderProgram->setUniform4f("u_color", 1.0f, 0.7f, 1.0f, 1.0f);

		//enable blending of alpha channel
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//prepare an array (object) for multiple buffer x attribpointer settings
		vao = new VertexArray();
		//prepare the vertex buffer to set
		vbo = new VertexBuffer(vertexes, sizeof(vertexes));
		//prepare layout for the buffer and bind it to the buffer using vao
		auto layout = new VertexBufferLayout();
		layout->push<float>(2); //our data structure is just positions defined by 2 floats
		layout->push<float>(2);
		vao->addBuffer(vbo, layout);

		//GLint positionLoc = glGetAttribLocation(shaderProgram, "position"); //TODO -- will i need this in the future?

		//prepare an index buffer
		ibo = new IndexBuffer(indices, 6);

		//prepare textures
		texture = new Texture("res/textures/cogwheels.png");
		texture->bind(); //bind a texture to a selected slot (default slot is zero)
		shaderProgram->setUniform1i("u_texture", 0); //we need to tell the shader at which slot does the texture lie

		//Unbind everything at the end (not needed)
		shaderProgram->unbind();
		vao->unbind();
		vbo->unbind();
		ibo->unbind();
	}

	void drawCallback() {
		renderer->clear();

		//set uniforms (needs to be done after shader binding by useProgram)
		shaderProgram->bind();
		shaderProgram->setUniform4f("u_color", 1.0f, 0.7f, blue, 1.0f);

		renderer->draw(*vao, *ibo, *shaderProgram);

		//change color over time
		if (blue > 1.0f || blue < 0.0f)
			increment = -increment;
		blue += increment;

		glutSwapBuffers();
	}
	
	void winResizeCallback(int width, int height) {

	}

	void timerCallback(int) {
		// set timeCallback next invocation
		glutTimerFunc(33, timerCallback, 0);
		//send request for a display function (multiple requests dont stack up)
		glutPostRedisplay();
	}

	void finalizeApplication() {
		delete shaderProgram;
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
	//SET WINDOW RESIZE CALLBACK FUNCTION
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
		pgr::dieWithError("pgr framework init failed, required OpenGL not supported?");
	//INITIALIZE APPLICATION (shaders and stuff)
	initApp();
	//SET A TIMER
	glutTimerFunc(33, timerCallback, 0);
	//START THE APPLICATION LOOP
	glutMainLoop();
	return 0;
}

