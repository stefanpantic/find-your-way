#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "rgmodel.hpp"

namespace eRG
{

	/* Model implementation: */
	/* @@{ */
	/* Construction: */
	/* @{ */
	/*
	* @brief Builds %eRG::Model.
	*/
	Model::Model(	glm::vec3 lower_left_near,
					glm::vec3 upper_right_far)
		:	lln_{lower_left_near}, urf_{upper_right_far}
	{
		std::clog << "eRG::Model: Default constructor" << std::endl;
	}

	/*
	* @brief Copy constructor.
	*/
	Model::Model(const Model &other)
		:	lln_{other.lln_}, urf_{other.urf_}
	{
		std::clog << "eRG::Model: Copy constructor" << std::endl;
	}

	/*
	* @brief Move constructor.
	*/
	Model::Model(Model &&other)
		:	lln_{std::move(other.lln_)}, urf_{std::move(other.urf_)}
	{
		std::clog << "eRG::Model: Move constructor" << std::endl;
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
