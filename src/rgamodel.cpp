#include <iostream>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "rgamodel.hpp"

namespace eRG
{

	/* AModel declaration: */
	/* @@{ */
	/* Construction */
	/* @{ */
	/*
	* @brief Builds instance of %eRG::AModel.
	*/
	AModel::AModel(	glm::vec3 lower_left_near,
					glm::vec3 upper_right_far,
					std::vector<glm::vec3> &&points)
		:	Model{lower_left_near, upper_right_far},
			points_{std::move(points)},
			delta_{glm::normalize(points_[1] - points_[0])/30.0f}
	{
		std::clog << "eRG::AModel: Default constructor" << std::endl;
	}

	/*
	* @brief Copy constructor.
	*/
	AModel::AModel(const AModel &other)
		:	Model{other},
			points_{other.points_},
			delta_{other.delta_}
	{
		std::clog << "eRG::AModel: Copy constructor" << std::endl;
	}

	/*
	* @brief Move constructor.
	*/
	AModel::AModel(AModel &&other)
		:	Model{std::move(other)},
			points_{std::move(other.points_)},
			delta_{std::move(other.delta_)}

	{
		std::clog << "eRG::AModel: Move constructor" << std::endl;
	}
	/* @} */

	/* Draw: */
	/* @{ */
	/*
	* @brief Draw moving model.
	*
	* TODO: cleanup code, detailed description.
	*/
	void AModel::draw()
	{
		static double d_old{0}, d_new{glm::distance(points_[1], points_[0])};
		static size_t index{1};

		d_old = d_new;
		d_new = glm::distance(translate_, points_[index]);

		if(d_new > d_old) {
			index = (index + 1) % points_.size();
			delta_ = glm::normalize(points_[index] - translate_)/30.0f;
			d_new = glm::distance(points_[index], translate_);
		}

		Model::lln_ += delta_;
		Model::urf_ += delta_;
		translate_ += delta_;

		glPushMatrix();
			Model::apply_transformations();
			glutSolidCube(1);
		glPopMatrix();

	}
	/* @} */

	/* @@} */

}; /* namespace eRG */
