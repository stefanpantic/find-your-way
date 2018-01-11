#pragma once

#include <iostream>
#include <glm/vec3.hpp>
#include "rgmodel.hpp"

namespace eRG
{

	/* PModel declaration: */
	/* @{ */
	/*
	* @brief Class representing a stationary model.
	*
	* @inherit Model Abstract class that eRG::Scene works with.
	*/
	class PModel : public Model
	{
		/* Public member functions */
		public:
			/* Construction */
			explicit PModel(glm::vec3 lower_left_near = {0, 0, 0},
							glm::vec3 upper_right_far = {1, 1, 1});
			explicit PModel(const PModel &other);
			explicit PModel(PModel &&other);

			/* Draw */
			void draw() override;

		private:
			/* Stored transformations */
			glm::vec3 translate_;
			glm::vec3 scale_;
	}; /* class eRG::PModel */
	/* @} */

}; /* namespace eRG */
