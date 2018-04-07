#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "rgdefines.hpp"

namespace eRG::util
{

	/*
	* @brief Generate normalized texture coordinate vector.
	*/
	std::vector<std::vector<glm::vec2>> texture_coords(	const glm::vec3 &ll,
														const glm::vec3 &lr,
														const glm::vec3 &ul,
														const glm::vec3 &ur)
	{
		return 	std::vector<std::vector<glm::vec2>>{
				{{0, 0}, {lr.z - ll.z, 0}, {lr.z - ll.z, ur.y - ll.y}, {0, ur.y - ll.y}},
				{{0, 0}, {ul.x - ll.x, 0}, {ul.x - ll.x, ur.y - ll.y}, {0, ur.y - ll.y}},
				{{0, 0}, {lr.z - ll.z, 0}, {lr.z - ll.z, ul.x - ll.x}, {0, ul.x - ll.x}}};
	}

}; /* namespace eRG::util */
