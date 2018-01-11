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
			virtual std::pair<glm::vec3, glm::vec3> position();

			/* Draw */
			virtual void draw() = 0;
		/* Protected member variables */
		protected:
			/* Stored corners */
			glm::vec3 lln_;
			glm::vec3 urf_;
	}; /* class eRG::Model */
	/* @} */

}; /* namespace eRG */
