#pragma once

#include <iostream>
#include <glm/vec3.hpp>

namespace eRG
{

	/* Model declaration: */
	/* @{ */
	/*
	* @brief Model abstract class.
	*/
	class Model
	{
		/* Public member functions */
		public:
			/* Construction */
			explicit Model( glm::vec3 lower_left_near = {0, 0, 0},
							glm::vec3 upper_right_far = {1, 1, 1});
			explicit Model(const Model &other);
			explicit Model(Model &&other);

			/* Position */
			virtual std::pair<glm::vec3, glm::vec3> position() const;

			/* Draw */
			virtual void draw() = 0;

		/* Protected member functions */
		protected:
			/* Apply stored transformations */
			void apply_transformations();

		/* Protected member variables */
		protected:
			/* Stored corners */
			glm::vec3 lln_;
			glm::vec3 urf_;

			/* Stored transformations */
			glm::vec3 translate_;
			glm::vec3 scale_;
	}; /* class eRG::Model */
	/* @} */

}; /* namespace eRG */
