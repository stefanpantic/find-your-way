#pragma once

#include <iostream>
#include <glm/vec3.hpp>
#include "rgoption.hpp"

namespace eRG::util
{

	/* Convenience: */
	using Box = std::pair<glm::vec3, glm::vec3>;

	/* Helper functions for colision detection and handling */
	Box pbox(glm::vec3 eye, float h);
	std::pair<opt::Move, float> handle_colision(const Box &pbox, const Box &mbox);

}; /* namespace eRG::util */
