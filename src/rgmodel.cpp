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
	* @brief Builds instance of %eRG::Model.
	*/
	Model::Model(	glm::vec3 translate,
					glm::vec3 scale,
					glm::vec4 rotate)
		:	translate_{translate},
			scale_{scale},
			rotate_{rotate}
	{
		std::clog << "eRG::Model: Default constructor" << std::endl;
	}

	/*
	* @brief Copy constructor.
	*/
	Model::Model(const Model &other)
		:	translate_{other.translate_},
			scale_{other.scale_},
			rotate_{other.rotate_}
	{
		std::clog << "eRG::Model: Copy constructor" << std::endl;
	}

	/*
	* @brief Move constructor.
	*/
	Model::Model(Model &&other)
		:	translate_{std::move(other.translate_)},
			scale_{std::move(other.scale_)},
			rotate_{std::move(other.rotate_)}
	{
		std::clog << "eRG::Model: Move constructor" << std::endl;
	}
	/* @} */

	/* Relative transformations: */
	/* @{ */
	/*
	* @brief Translate model relative to stored transformation.
	*/
	void Model::translate_r(glm::vec3 translate)
	{
		translate_ += std::move(translate);
	}

	/*
	* @brief Scale model relative to stored transformation.
	*/
	void Model::scale_r(glm::vec3 scale)
	{
		scale_ += std::move(scale);
	}

	/*
	* @brief Rotate model relative to stored transformation.
	*/
	void Model::rotate_r(glm::vec4 rotate)
	{
		rotate_ += std::move(rotate);
	}
	/* @} */

	/* Absolute transformations: */
	/* @{ */
	/*
	* @brief Set model translation.
	*/
	void Model::translate_a(glm::vec3 translate)
	{
		translate_ = std::move(translate);
	}

	/*
	* @brief Set model scale.
	*/
	void Model::scale_a(glm::vec3 scale)
	{
		scale_ = std::move(scale);
	}

	/*
	* @brief Set model rotation.
	*/
	void Model::rotate_a(glm::vec4 rotate)
	{
		rotate_ = std::move(rotate);
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
