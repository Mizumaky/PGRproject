#include <iostream>;
#include "pgr.h";
#include "defines.h";
#include "Model.h";

Model model;

GLuint shaderProgram = 0;
GLuint arrayBuffer = 0;
GLuint vao = 0;

std::string vertexShaderSrc =
"#version 140\n"
"in vec2 position;\n"
"void main() {\n"
"  gl_Position = vec4(position, 0.0f, 1.0f);\n"
"}\n"
;

std::string fragmentShaderSrc =
"#version 140\n"
"out vec4 color;"
"void main() {\n"
"  color = vec4(1.0f, 0.5f, 1.0f, 1.0f);\n"
"}\n"
;


void initApp() {
	//set default color when clearing view
	glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
	//enable depth buffer support
	glEnable(GL_DEPTH_TEST);
	//specify the rendering window
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));


	GLuint shaders[] = {
	  pgr::createShaderFromSource(GL_VERTEX_SHADER, vertexShaderSrc),
	  pgr::createShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderSrc),
	  0
	};
	shaderProgram = pgr::createProgram(shaders);

	//debug triangle
	static const float vertices[] = {
	  0.0f,  0.5f,
	  -0.5f, -0.5f,
	  0.5f, -0.5f,
	};

	//prepare buffer
	glGenBuffers(1, &arrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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