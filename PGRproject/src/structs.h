#include "pgr.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

namespace mullemi5 {
	typedef struct MeshGeometry { //meshgeometryobject
		// vertices
		VertexBuffer* vbo = nullptr;
		IndexBuffer* ibo = nullptr; //(ebo)
		VertexArray* vao = nullptr;
		unsigned int triangleCount = -1;

		// material
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
		GLuint texture;
	} MeshGeometry;

	typedef struct GameObject {
		glm::vec3 position;
		glm::vec3 direction;
		float speed;
		float size;

		bool destroyed;
	} GameObject;

	typedef struct PlayerObject : public GameObject {
		float viewAngle; // in degrees
	} PlayerObject;

}
