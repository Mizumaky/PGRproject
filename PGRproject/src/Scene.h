#pragma once
#include "GameObject.h"

namespace mullemi5 {

	class Scene {
	private:
		GameObject [] gameObjects;
		EventDispatcher eventDispatcher;
		SceneRenderer sceneRenderer;
	public:
		Scene();
		virtual ~Scene();


		void update(float timestep, InputState input) {
			eventDispatcher.sendEvent("update", timestep, input);
		}

		void render() {
			eventDispatcher.sentEvent("render", sceneRenderer);
		}

		void createGameObject() {
			GameObject result = new GameObject();
			gameObjects.add(result);
			result.addedToScene(this);

			// add any component in the gameObject to the eventDispatcher
			// so it can receive update and render messages
			// if the component doesn't have either method it isn't added
		}
	};

}
