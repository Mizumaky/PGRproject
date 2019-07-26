#pragma once
#include "../core/IListener.h"
#include "ShaderManager.h"
#include "ModelsManager.h"

namespace managers {

	class SceneManager : public core::IListener {
	public:
		SceneManager();
		~SceneManager();

		void notifyBeginFrame() override;
		void notifyDisplayFrame() override;
		void notifyEndFrame() override;
		void notifyReshape(
			int width, int height,
			int previous_width, int previous_height
		) override;
	private:
		ShaderManager* m_shaderManager;
		ModelsManager* m_modelsManager;
	};

}
