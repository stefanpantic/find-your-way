#pragma once

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include "rgcube.hpp"

namespace eRG
{

	/* ACube declaration: */
	/* @{ */
	/*
	* @brief Class representing a moving cube.
	*
	* @inherit Cube class used for representing stationary cubes.
	*/
	class ACube : public Cube
	{
		/* Public member functions */
		public:
			/* Construction */
			explicit ACube(	glm::vec3 lln = {0, 0, 0},
							glm::vec3 urf = {1, 1, 1},
							std::vector<glm::vec3> &&points = {},
							const std::vector<std::string> &paths = {});
			explicit ACube(const ACube &other);
			explicit ACube(ACube &&other);

			/* Draw */
			void draw() override;

			/* Get delta */
			glm::vec3 get_delta() const override;

		/* Private member variables */
		private:
			/* Points of movement */
			std::vector<glm::vec3> points_;

			/* Direction of movement */
			glm::vec3 delta_;

			/* Current point */
			size_t index_;

			/* Distances from next point */
			float dold_, dnew_;
	}; /* class eRG::ACube */
	/* @} */

}; /* namespace eRG */
