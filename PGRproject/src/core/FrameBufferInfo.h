#pragma once
#include <GL/freeglut.h>

namespace core {

	struct FrameBufferInfo {
		unsigned int flags;
		bool msaaEnabled;

		FrameBufferInfo() {
			flags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
			msaaEnabled = false;
		}

		FrameBufferInfo(bool color, bool alpha, bool depth, bool stencil, bool msaa) {
			flags = GLUT_DOUBLE; //this is a must
			if (color)
				flags |= GLUT_RGBA;
			if (alpha)
				flags |= GLUT_ALPHA;
			if (depth)
				flags |= GLUT_DEPTH;
			if (stencil)
				flags |= GLUT_STENCIL;
			if (msaa)
				flags |= GLUT_MULTISAMPLE;
			this->msaaEnabled = msaa;
		}
	};

}
