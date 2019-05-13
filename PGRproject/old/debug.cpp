#include <iostream>;
#include <pgr.h>;

bool glCheckErrors() {
	bool ret = true;
	while (unsigned int error = glGetError()) {
		printf("OpenGL Error: %d\n", error);
		ret = false;
	}
	return ret;
}