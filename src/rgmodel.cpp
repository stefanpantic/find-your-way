#include <iostream>
#include <GL/glut.h>
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
		:	lln_{lower_left_near}, urf_{upper_right_far},
			translate_{(lower_left_near + upper_right_far)/2.0f},
			scale_{upper_right_far - lower_left_near}
	{
		std::clog << "eRG::Model: Default constructor" << std::endl;
	}

	/*
	* @brief Copy constructor.
	*/
	Model::Model(const Model &other)
		:	lln_{other.lln_}, urf_{other.urf_},
			translate_{other.translate_},
			scale_{other.scale_}
	{
		std::clog << "eRG::Model: Copy constructor" << std::endl;
	}

	/*
	* @brief Move constructor.
	*/
	Model::Model(Model &&other)
		:	lln_{std::move(other.lln_)}, urf_{std::move(other.urf_)},
			translate_{std::move(other.translate_)},
			scale_{std::move(other.scale_)}
	{
		std::clog << "eRG::Model: Move constructor" << std::endl;
	}

	/* Position: */
	/* @{ */
	/*
	* @brief Get model position as lower left near corner and upper far right corner coordinates.
	*/
	std::pair<glm::vec3, glm::vec3> Model::position() const
	{
		return {glm::vec3{Model::lln_}, glm::vec3{Model::urf_}};
	}
	/* @} */

	/* Apply stored transformations */
	/* @{ */
	/*
	* @brief Apply stored translation and scale to model.
	*/
	void Model::apply_transformations()
	{
		glTranslatef(translate_.x, translate_.y, translate_.z);
		glScalef(scale_.x, scale_.y, scale_.z);
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
