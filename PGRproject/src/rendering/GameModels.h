#pragma once
#include <vector>
#include <map>
#include <GL/glew.h>

namespace models {
	//struct for a game model
	struct Model {
		GLuint vao;
		std::vector<GLuint> vbos;

		Model() = default;
	};
	//class holding all models
	class GameModels {
	public:
		GameModels();
		~GameModels();
		void createTriangleModel(const std::string& gameModelName);
		void deleteModel(const std::string& gameModelName);
		GLuint getModelVao(const std::string& gameModelName);
	private:
		std::map<std::string, Model> gameModelList;
	};
}
