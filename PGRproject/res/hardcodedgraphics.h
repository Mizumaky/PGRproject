#pragma once
namespace mullemi5 {

	//triangle
	float positions[] = {
	  -0.5f, -0.5f, //0
	   0.5f, -0.5f, //1
	   0.5f,  0.5f, //2
	  -0.7f,  0.5f  //3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

}