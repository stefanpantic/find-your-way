#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace eRG
{

	/* Model declaration: */
	/* @{ */
	/*
	* @brief Model interface.
	*/
	class Model
	{
		/* Public member functions */
		public:
			/* Construction */
			explicit Model( glm::vec3 translate = {0, 0, 0},
							glm::vec3 scale		= {1, 1, 1},
							glm::vec4 rotate 	= {0, 0, 0, 0});
			explicit Model(const Model &other);
			explicit Model(Model &&other);

			/* Relative transformations */
			void translate_r(glm::vec3 translate);
			void scale_r(glm::vec3 scale);
			void rotate_r(glm::vec4 rotate);

			/* Absolute transformations */
			void translate_a(glm::vec3 translate);
			void scale_a(glm::vec3 scale);
			void rotate_a(glm::vec4 rotate);

			/* Position */
			virtual const glm::vec3& position() = 0;	

			/* Draw */
			virtual void draw() = 0;
		/* Protected member variables */
		protected:
			/* Transformations */
			glm::vec3 translate_;
			glm::vec3 scale_;
			glm::vec4 rotate_;
	}; /* class eRG::Model */
	/* @} */

}; /* namespace eRG */
