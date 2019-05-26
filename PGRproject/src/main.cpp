#include <iostream>
#include <string>
#include "pgr.h"
#include "settings.h"
#include "../res/hardcodedgraphics.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "Renderer.h"
#include "Texture.h"
#include "SkyboxRenderer.h"

// #include "external/imGui/imgui.h"
// #include "external/imGui/imgui_impl_glut.h"
// #include "external/imGui/imgui_impl_opengl3.h"


namespace mullemi5 {

	//Model model;

	float blue = 0.0f;
	float increment = 0.05f;

	Renderer* renderer;

	struct GameState {
		int windowWidth = -1;    // set by reshape callback
		int windowHeight = -1;   // set by reshape callback

		bool camLock = true;
		float camPitchAngle = 0.0f; // in degrees = initially 0.0f
		float camYawAngle = 0.0f; // in degrees = initially 0.0f
		float camRollAngle = 0.0f; // in degrees = initially 0.0f

		bool gameOver = false;              // false;
		bool keyMap[KEYS_COUNT] = {false};    // false

		float lastCallTime = 0.0f;
		float currentTime = 0.0f;
	} gameState;

	struct ObjectClasses { //TODO probably move to renderer
		SkyboxRenderer skybox;
	} objectClasses;

	struct GameObjectInstances {

	} gameObjectInstances;


	void restartGame() { //TODO TIME????
		gameState.lastCallTime = 0.001f * (float)glutGet(GLUT_ELAPSED_TIME); // milliseconds => seconds
		gameState.currentTime = gameState.lastCallTime;

		// if (gameState.freeCameraMode == true) {
		// 	gameState.freeCameraMode = false;
		// 	glutPassiveMotionFunc(NULL);
		// }
		gameState.camPitchAngle = 0.0f;
		gameState.camYawAngle = 0.0f;
		gameState.camRollAngle = 0.0f;

		// reset key map
		for (int i = 0; i < KEYS_COUNT; i++)
			gameState.keyMap[i] = false;

		gameState.gameOver = false;
	}

	void initApp() {
		//set default color when clearing view
		glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
		//enable stencil vuffer
		glClearStencil(0);
		//enable depth buffer support
		glEnable(GL_DEPTH_TEST);
		//renderer = new Renderer(); //TODO move stuff above to here
		
		// //prepare an array (object) for multiple buffer x attribpointer settings
		// vao = new VertexArray();
		// //prepare the vertex buffer to set
		// vbo = new VertexBuffer(vertexes, sizeof(vertexes));
		// //prepare layout for the buffer and bind it to the buffer using vao (needs to be done after vao and vbo)
		// auto layout = new VertexBufferLayout();
		// layout->push<float>(2); //our data structure is positions defined by 2 floats
		// layout->push<float>(2); //and texture coordinates by another 2 floats
		// vao->addBuffer(vbo, layout);
		//
		// //GLint positionLoc = glGetAttribLocation(shaderProgram, "position"); //TODO -- will i need this in the future?
		//
		// //prepare an index buffer
		// ibo = new IndexBuffer(indices, 6);
		//
		// //load up the shader
		// shaderProgram = new ShaderProgram("res/shaders/basic.vert", "res/shaders/basic.frag", "");
		// shaderProgram->bind();
		//
		//
		// //possibly set one-time uniforms (needs to be done after shader)
		// shaderProgram->setUniform4f("u_color", 1.0f, 0.7f, 1.0f, 1.0f);
		//
		// //prepare textures (needs to be done after shader)
		// texture = new Texture("res/textures/cogwheels.png");
		// texture->bind(); //bind a texture to a selected slot (default slot is zero)
		// shaderProgram->setUniform1i("u_texture", 0); //we need to tell the shader at which slot does the texture lie

		// //Unbind everything at the end (not needed)
		// shaderProgram->unbind();
		// vao->unbind();
		// vbo->unbind();
		// ibo->unbind();

		objectClasses.skybox.initShader();
		objectClasses.skybox.initGeometry();

		restartGame();
	}

	void drawCallback() {
		renderer->clear();

		// //set uniforms (needs to be done after shader binding by useProgram)
		// shaderProgram->bind();
		// shaderProgram->setUniform4f("u_color", 1.0f, 0.7f, blue, 1.0f);
		//
		// //set projection matrix
		// glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
		// //glm::mat4 projection = glm::ortho(0.0f, (float)glutGet(GLUT_WINDOW_WIDTH), 0.0f, (float)glutGet(GLUT_WINDOW_HEIGHT), -1.0f, 1.0f); //according to our window
		// glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f)); //posun kamery o 0.5 dolu (vsech modelu nahoru)
		//
		// //draw obejct A
		// glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.6f, 0.0f, 0.0f)); //posun modelu o 0.5 doleva ve svete
		// glm::mat4 MVP = projection * view * model;
		// shaderProgram->setUniformMat4f("u_MVP", MVP);
		// renderer->draw(*vao, *ibo, *shaderProgram);
		//
		// //draw object B
		// model = glm::translate(glm::mat4(1.0f), glm::vec3(0.6f, 0.0f, 0.0f)); //posun modelu o 0.5 doprava ve svete
		// MVP = projection * view * model;
		// shaderProgram->setUniformMat4f("u_MVP", MVP);
		// renderer->draw(*vao, *ibo, *shaderProgram);
		// shaderProgram->unbind();
		//
		// //change color over time
		// if (blue > 1.0f || blue < 0.0f)
		// 	increment = -increment;
		// blue += increment;

		//ORTOGRAPHIC
		//   // setup parallel projection
		// glm::mat4 orthoProjectionMatrix = glm::ortho(
		// 	-SCENE_WIDTH, SCENE_WIDTH,
		// 	-SCENE_HEIGHT, SCENE_HEIGHT,
		// 	-10.0f*SCENE_DEPTH, 10.0f*SCENE_DEPTH
		// );
		// // static viewpoint - top view
		// glm::mat4 orthoViewMatrix = glm::lookAt(
		// 	glm::vec3(0.0f, 0.0f, 1.0f),
		// 	glm::vec3(0.0f, 0.0f, 0.0f),
		// 	glm::vec3(0.0f, 1.0f, 0.0f)
		// );

		// SETUP CAMERA & PROJECTION TRANSFORM  x       y      z
		glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); //TODO position of player
		glm::vec3 cameraUpVector = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraCenter;
		glm::vec3 cameraViewDirection = glm::vec3(1.0f, 0.0f, 0.0f); //TODO look direction of player

		//CALCULATE ROTATION MATRIX
		glm::mat4 cameraTransform = glm::mat4(1.0f); //init diagonal matrix of ones
		//rotate matrix up / down
		glm::vec3 pitchAxis = glm::cross(cameraViewDirection, glm::vec3(0.0f, 1.0f, 0.0f)); //cross product of player direction and worlds up direction
		cameraTransform = glm::rotate(cameraTransform, glm::radians(gameState.camPitchAngle), pitchAxis);
		//rotate matrix left / right along y
		glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		cameraTransform = glm::rotate(cameraTransform, glm::radians(gameState.camYawAngle), rotationAxis);

		//MULTIPLY UP VECTOR AND VIEW DIRECTION BY THE MATRIX, and g
		cameraUpVector = glm::vec3(cameraTransform * glm::vec4(cameraUpVector, 0.0f));
		cameraViewDirection = glm::vec3(cameraTransform * glm::vec4(cameraViewDirection, 0.0f));
		cameraCenter = cameraPosition + cameraViewDirection;

		//CALCULATE VIEW MATRIX BASED ON PREVIOUS RESULTS
		glm::mat4 viewMatrix = glm::lookAt(
			cameraPosition,
			cameraCenter,
			cameraUpVector
		);

		glm::mat4 projectionMatrix = glm::perspective(glm::radians(CAMERA_FOV), (float)gameState.windowWidth / (float)gameState.windowHeight, 0.1f, 10.0f);

		//TODO common shader / renderer
		// glUseProgram(shaderProgram.program);
		// glUniform1f(shaderProgram.timeLocation, gameState.currentTime);
		//
		// glUniform3fv(shaderProgram.reflectorPositionLocation, 1, glm::value_ptr(gameObjects.spaceShip->position));
		// glUniform3fv(shaderProgram.reflectorDirectionLocation, 1, glm::value_ptr(gameObjects.spaceShip->direction));
		// glUseProgram(0)
		

		// disable stencil test before drawing skybox //TODO why? also, this is the only usage
		glDisable(GL_STENCIL_TEST);
		// draw skybox
		objectClasses.skybox.draw(viewMatrix, projectionMatrix);

		glutSwapBuffers();
	}
	
	void winResizeCallback(int width, int height) {
		gameState.windowWidth = width;
		gameState.windowHeight = height;
		glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	}

	void passiveMouseMotionCallback(int mouseX, int mouseY) {
		if (mouseX != gameState.windowWidth / 2) { // if mouse not in the middle
			float camYawAngleDelta = 0.2f * (gameState.windowWidth / 2 - mouseX);
			if (fabs(gameState.camYawAngle + camYawAngleDelta) < CAMERA_ROTATION_MAX)
				gameState.camYawAngle += camYawAngleDelta;
		}
		if (mouseY != gameState.windowHeight / 2) { // if mouse not in the middle
			float camPitchAngleDelta = 0.2f * (gameState.windowHeight / 2 - mouseY);
			if (fabs(gameState.camPitchAngle + camPitchAngleDelta) < CAMERA_ELEVATION_MAX)
				gameState.camPitchAngle += camPitchAngleDelta;
		}
		// set mouse pointer to the window center
		glutWarpPointer(gameState.windowWidth / 2, gameState.windowHeight / 2);
	}

	void keyboardCallback(unsigned char keyPressed, int mouseX, int mouseY) {

		switch (keyPressed) {
			case 27: // escape
				glutLeaveMainLoop();
				break;
			case 'r': // restart game
				restartGame();
				break;
			case 'c': // switch camera
				gameState.camLock = !gameState.camLock;
				if (gameState.camLock == true) {
					glutPassiveMotionFunc(NULL);
				}
				else {
					glutPassiveMotionFunc(passiveMouseMotionCallback);
					glutWarpPointer(gameState.windowWidth / 2, gameState.windowHeight / 2);
				}
				break;
			default:
				; // printf("Unrecognized key pressed\n");
		}
	}

	void updateGame() { //TODO
		gameState.currentTime = 0.001f * (float)glutGet(GLUT_ELAPSED_TIME); // milliseconds => seconds
		float timeDelta = gameState.currentTime - gameState.lastCallTime;
	}

	void timerCallback(int) {
		//update objects over time
		updateGame();

		// set timeCallback next invocation
		glutTimerFunc(REFRESH_INTERVAL, timerCallback, 0);
		//send request for a display function (multiple requests dont stack up)
		glutPostRedisplay();
	}

	void finalizeApplication() {
		//delete shaderProgram;
	}
}

using namespace mullemi5;

int main(int argc, char** argv) {
	std::cout << "Application started" << std::endl;

	glutInit(&argc, argv);
	//GLUT OPENGL STUFF INITIALIZATION
	glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR); //context = instance of opengl, think of it like object in which all states n stuff from opengl are
	glutInitContextProfile(GLUT_CORE_PROFILE); //to assert newer conventions n stuff - MY OWN ADDED LINE DONT FORGET!
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextFlags(GLUT_DEBUG); //MY OWN ADDED FOR ALLOWING DEBUG MESSAGES (also needed to change in pgr.h)

	//GLUT WINDOW INITIALIZATION
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	//glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutCreateWindow(WIN_TITLE);

	//GLUT CALLBACK FUNCTIONS ASSIGNING
	glutDisplayFunc(drawCallback);
	glutReshapeFunc(winResizeCallback);
	glutKeyboardFunc(keyboardCallback);
	//glutKeyboardUpFunc(keyboardUpCallback);
	//glutSpecialFunc(specialKeyboardCallback);     // key pressed
	//glutSpecialUpFunc(specialKeyboardUpCallback); // key released
	glutPassiveMotionFunc(passiveMouseMotionCallback); //mouse moved without click
	glutWarpPointer(gameState.windowWidth / 2, gameState.windowHeight / 2); //move mouse position ^^
	//glutMouseFunc(mouseCallback);
	glutCloseFunc(finalizeApplication);
	glutTimerFunc(REFRESH_INTERVAL, timerCallback, 0);

	//PGR FRAMEWORK / OPENGL CONTEXT INITIALIZATION (GL, DevIl, etc.)
	if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
		pgr::dieWithError("pgr framework init failed, required OpenGL not supported?");

	//INITIALIZE APPLICATION DATA (shaders and stuff)
	initApp();

	//START THE APPLICATION LOOP
	glutMainLoop();
	return 0;
}

