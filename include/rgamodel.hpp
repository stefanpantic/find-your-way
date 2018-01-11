#pragma once

#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include "rgmodel.hpp"

namespace eRG
{

	/* AModel declaration: */
	/* @{ */
	/*
	* @brief Class representing a moving model.
	*
	* @inherit Model Abstract class that eRG::Scene works with.
	*/
	class AModel : public Model
	{
		/* Public member functions */
		public:
			/* Construction */
			explicit AModel(glm::vec3 lower_left_near = {0, 0, 0},
							glm::vec3 upper_right_far = {1, 1, 1},
							std::vector<glm::vec3> &&points = {});
			explicit AModel(const AModel &other);
			explicit AModel(AModel &&other);

			/* Draw */
			void draw() override;
		/* Private member variables */
		private:
			/* Points of movement */
			std::vector<glm::vec3> points_;

			/* Direction of movement */
			glm::vec3 delta_;
	}; /* class eRG::AModel */
	/* @} */

}; /* namespace eRG */
