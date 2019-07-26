#pragma once
#include "../IGameObject.h"

namespace rendering {
	namespace models {

		class Model : public IGameObject {
		public:
			Model();
			virtual ~Model();
			// methods from interface
			void draw() override;
			void update() override;
			void setProgram(GLuint program) override;
			void destroy() override;

			GLuint getVao() const override;
			const std::vector<GLuint>& getVbos() const override;

		protected:
			GLuint m_vao;
			GLuint m_program;
			std::vector<GLuint> m_vbos;
		};

	}
}