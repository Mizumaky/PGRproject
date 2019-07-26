#pragma once
#include <vector>
#include "VertexFormat.h"
#include <GL/glew.h>

namespace rendering {

	class IGameObject {
	public:
		virtual ~IGameObject() = 0;

		virtual void draw() = 0;
		virtual void update() = 0;
		virtual void setProgram(GLuint shaderName) = 0;
		virtual void destroy() = 0;

		virtual GLuint getVao() const = 0;
		virtual const std::vector<GLuint>& getVbos() const = 0;
	};

	inline IGameObject::~IGameObject(){
		//pure destructor
	}

}
