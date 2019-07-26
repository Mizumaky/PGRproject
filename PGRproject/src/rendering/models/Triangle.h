#pragma once
#include "Model.h"

namespace rendering {
	namespace models {

		class Triangle : public Model {
		public:
			Triangle();
			~Triangle();

			void create();
			void draw() override final;
			void update() override final;
		};

	}
}

