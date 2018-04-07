#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace eRG::util
{

	/* Constant expression for PI */
	constexpr float pi{3.14159265359};

	/*
	* @brief Typesafe signum function.
	*
	* @param T NumericType type.
	*/
	template<typename T>
	constexpr int sgn(T val)
	{
		return (T(0) < val) - (T(0) > val);
	}

	/* Syntax sugar for texture coordinate initializer */
	std::vector<std::vector<glm::vec2>> texture_coords(	const glm::vec3 &ll,
														const glm::vec3 &lr,
														const glm::vec3 &ul,
														const glm::vec3 &ur);

}; /* namespace eRG::util */


