#pragma once

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace eRG
{

	/* Cube declaration: */
	/* @{ */
	/*
	* @brief Cube abstract class.
	*/
	class Cube
	{
		/* Public member functions */
		public:
			/* Construction */
			explicit Cube( glm::vec3 lower_left_near = {0, 0, 0},
							glm::vec3 upper_right_far = {1, 1, 1},
							const std::vector<std::string> &paths = {});
			explicit Cube(const Cube &other);
			explicit Cube(Cube &&other);
			~Cube();

			/* Position */
			virtual std::pair<glm::vec3, glm::vec3> position() const;

			/* Draw */
			virtual void draw();

		/* Protected member variables */
		protected:
			/* Stored corners */
			glm::vec3 lln_;
			glm::vec3 urf_;

			/* Call list handle */
			GLuint dlist_;

			/* Vertices */
			std::vector<glm::vec3> vertices_;

			/* Texture handles */
			std::vector<GLuint> handles_;

			/* Indices */
			static const std::vector<std::vector<int>> indices_;

			/* Texture indices */
			static const std::vector<glm::vec2> tex_;
	}; /* class eRG::Cube */
	/* @} */

}; /* namespace eRG */