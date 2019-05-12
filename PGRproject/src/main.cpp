#include <iostream>;
#include <fstream>;
#include <sstream>;
#include "pgr.h";
#include "definitions.h";
#include "Model.h";
#include "../res/hardcodedgraphics.h";


	Model model;

	GLuint shaderProgram = 0;
	GLuint arrayBuffer = 0; // uint for storing the ID of the buffer
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

		//DRAW TRIANGLE
		//prepare buffer
		glGenBuffers(1, &arrayBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2D), triangle2D, GL_STATIC_DRAW); //STATIC DRAW indicates to opengl that the data will be written only like once, but read often, and will be used for drawing
		//prepare vao
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GLint positionLoc = glGetAttribLocation(shaderProgram, "position");
		glEnableVertexAttribArray(positionLoc);
		glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	void drawCallback() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glutSwapBuffers();
	}

	void winResizeCallback(int width, int height) {

	}

	void finalizeApplication() {
		pgr::deleteProgramAndShaders(shaderProgram);
	}

	int main(int argc, char** argv) {
		std::cout << "Application started" << std::endl;
		//GLUT LIBRARY INITIALIZATION
		glutInit(&argc, argv);
		glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
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
