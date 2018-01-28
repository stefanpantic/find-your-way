#pragma once

#include <iostream>
#include <vector>
#include <GL/glut.h>
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
							glm::vec3 upper_right_far = {1, 1, 1},
							const std::vector<std::string> &paths = {});
			explicit Model(const Model &other);
			explicit Model(Model &&other);

			/* Position */
			virtual std::pair<glm::vec3, glm::vec3> position() const;

			/* Create call list */
			void initialize_model() const;

			/* Draw */
			virtual void draw() = 0;

		/* Protected member variables */
		protected:
			/* Stored corners */
			glm::vec3 lln_;
			glm::vec3 urf_;

			/* Call list handle */
			GLuint dlist_;

			/* Texture handles */
			std::vector<GLuint> handles_;
	}; /* class eRG::Model */
	/* @} */

}; /* namespace eRG */
