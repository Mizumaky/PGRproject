#include <iostream>;
#include <string>;
#include "pgr.h";
#include "definitions.h";
#include "Model.h";
#include "../res/hardcodedgraphics.h";

namespace mullemi5 {

	Model model;

	float blue = 0.0f;
	float increment = 0.05f;
	GLint colorUniLoc = 0;

	GLuint shaderProgram = 0;
	GLuint arrayBuffer = 0; // uint for storing the ID of the array buffer - vertices
	GLuint indexBuffer = 0; // uint for storing the ID of the index buffer - indexes of vertices, making triangles
	GLuint vao = 0; // uint for storing the ID of the vertex array object?

	void initApp() {
		//set default color when clearing view
		glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
		//enable depth buffer support
		glEnable(GL_DEPTH_TEST);
		//specify the rendering window
		glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

		GLuint shaders[] = {
		  pgr::createShaderFromFile(GL_VERTEX_SHADER, VERTEX_SHADER_FILE),
		  pgr::createShaderFromFile(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_FILE),
		  0
		};
		shaderProgram = pgr::createProgram(shaders);

		//prepare an array (object) for multiple buffer x attribpointer settings
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GLint positionLoc = glGetAttribLocation(shaderProgram, "position");

		//prepare an array buffer
		glGenBuffers(1, &arrayBuffer); //generate
		glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer); //bind - this is the buffer we will be currently setting stuff to 
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW); //prepare the storage for data, also STATIC DRAW indicates to opengl that the data will be written only like once, but read often, and will be used for drawing

		//tell opengl how to read the data from the buffer and enable it as an attribute
		glEnableVertexAttribArray(positionLoc); //enable the assignment of the specified vertex attribute for the currently bound vertex array object / buffer
		glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); //define how the attribute is stored in there - point to them the right way
		//             attribute, how much, of what does it take, normalize it?, offset between each vertex (size of each vertex), offset where inside the vertex should we find it

		//prepare an index buffer
		glGenBuffers(1, &indexBuffer); //generate
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer); //bind
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //prepare the storage for data

		//set uniform stuff
		colorUniLoc = glGetUniformLocation(shaderProgram, "u_Color");

		//Unbind everything at the end 
		glUseProgram(0);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		CHECK_GL_ERROR();
	}

	void drawCallback() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//bind everything in every call
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		//set uniforms (needs to be done after shader binding by useprogram)
		glUniform4f(colorUniLoc, 1.0f, 0.7f, blue, 1.0f);

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
		pgr::deleteProgramAndShaders(shaderProgram);
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

