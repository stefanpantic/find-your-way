#pragma once

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
			explicit PModel(glm::vec3 translate = {0, 0, 0},
							glm::vec3 scale 	= {1, 1, 1},
							glm::vec4 rotate 	= {0, 0, 0, 0});
			explicit PModel(const PModel &other);
			explicit PModel(PModel &&other);

			/* Position */
			const glm::vec3& position() override;

			/* Draw */
			void draw() override;
	}; /* class eRG::PModel */
	/* @} */

}; /* namespace eRG */
