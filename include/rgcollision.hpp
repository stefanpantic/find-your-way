#pragma once

#include <iostream>
#include <glm/vec3.hpp>
#include "rgoption.hpp"

namespace eRG::util
{

	/* Convenience: */
	using Box = std::pair<glm::vec3, glm::vec3>;
	using Collision = std::pair<opt::Move, opt::Move>;

	/* Helper functions for collision detection and handling */
	Box pbox(glm::vec3 eye, float h);
	Collision handle_collision(const Box &pbox, const Box &mbox);

}; /* namespace eRG::util */
