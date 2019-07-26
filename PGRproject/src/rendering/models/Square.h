#pragma once
#include "Model.h"

namespace rendering {
	namespace models {

		class Square : public Model {
		public:
			Square();
			~Square();

			void create();
			void draw() override final;
			void update() override final;
		};

	}
}