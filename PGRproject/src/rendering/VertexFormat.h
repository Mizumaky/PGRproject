#pragma once
#include <glm/glm.hpp>

struct VertexFormat {
	glm::vec3 position;

	//constructor
	VertexFormat(const glm::vec3 &pos) {
		position = pos;
	}
};