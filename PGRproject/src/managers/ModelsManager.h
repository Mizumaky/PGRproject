#pragma once
#include <map>
#include "ShaderManager.h"
#include "../rendering/IGameObject.h"
#include "../rendering/models/Triangle.h"

using namespace rendering;
namespace managers {

	class ModelsManager {
	public:
		ModelsManager();
		~ModelsManager();

		void draw();
		void update();
		void deleteModel(const std::string& gameModelName);
		const IGameObject& getModel(const std::string& gameModelName) const;

	private:
		std::map<std::string, IGameObject*> m_gameModelList;
		void checkModelExistence(const std::string& gameModelName) const;
	};

}