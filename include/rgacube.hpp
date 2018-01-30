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
	* @brief Class representing a moving model.
	*
	* @inherit Cube Abstract class that eRG::Scene works with.
	*/
	class ACube : public Cube
	{
		/* Public member functions */
		public:
			/* Construction */
			explicit ACube(glm::vec3 lln = {0, 0, 0},
							glm::vec3 urf = {1, 1, 1},
							std::vector<glm::vec3> &&points = {},
							const std::vector<std::string> &paths = {});
			explicit ACube(const ACube &other);
			explicit ACube(ACube &&other);
			~ACube();

			/* Draw */
			void draw() override;

		/* Private member variables */
		private:
			/* Points of movement */
			std::vector<glm::vec3> points_;

			/* Display list handle */
			size_t dlist_;

			/* Translation factor */
			glm::vec3 translate_;

			/* Direction of movement */
			glm::vec3 delta_;

			/* Current point */
			size_t index_;

			/* Distances from next point */
			float dold_, dnew_;
	}; /* class eRG::ACube */
	/* @} */

}; /* namespace eRG */
