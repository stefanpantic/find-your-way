#pragma once

#include <iostream>
#include <vector>
#include <GL/glut.h>
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
			explicit AModel(glm::vec3 lln = {0, 0, 0},
							glm::vec3 urf = {1, 1, 1},
							std::vector<glm::vec3> &&points = {},
							const std::vector<std::string> &paths = {});
			explicit AModel(const AModel &other);
			explicit AModel(AModel &&other);

			/* Draw */
			void draw() override;
		/* Private member variables */
		private:
			/* Points of movement */
			std::vector<glm::vec3> points_;

			/* Translation factor */
			glm::vec3 translate_;

			/* Direction of movement */
			glm::vec3 delta_;

			/* Current point */
			size_t index_;

			/* Distances from next point */
			float dold_, dnew_;
	}; /* class eRG::AModel */
	/* @} */

}; /* namespace eRG */
