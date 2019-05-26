#pragma once
namespace mullemi5 {

	//rectangle 2f position 2D, 2f texture coordinates
	float vertexes[] = {
	  -0.5f, -0.5f, 0.0f, 0.0f, //0 //at this point sample from left bottom of the texture
	   0.5f, -0.5f, 1.0f, 0.0f, //1 //from right bottom
	   0.5f,  0.5f, 1.0f, 1.0f, //2 //from top right
	  -0.5f,  0.5f, 0.0f, 1.0f  //3 //from top left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

}