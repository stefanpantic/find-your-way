#pragma once

#include <iostream>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include <vector>
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
			explicit PModel(glm::vec3 lln = {0, 0, 0},
							glm::vec3 urf = {1, 1, 1},
							const std::vector<std::string> &paths = {});
			explicit PModel(const PModel &other);
			explicit PModel(PModel &&other);
			~PModel();

			/* Draw */
			void draw() override;
	}; /* class eRG::PModel */
	/* @} */

}; /* namespace eRG */
