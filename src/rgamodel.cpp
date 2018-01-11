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
			points_{std::move(points)}
	{
		std::clog << "eRG::AModel: Default constructor" << std::endl;
	}

	/*
	* @brief Copy constructor.
	*/
	AModel::AModel(const AModel &other)
		:	Model{other},
			points_{other.points_}
	{
		std::clog << "eRG::AModel: Copy constructor" << std::endl;
	}

	/*
	* @brief Move constructor.
	*/
	AModel::AModel(AModel &&other)
		:	Model{std::move(other)},
			points_{std::move(other.points_)}

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
		static glm::vec3 delta{glm::normalize(points_[1] - points_[0])/10.0f};
		static glm::vec3 translate{(Model::urf_ + Model::lln_)/2.0f}, scale{Model::urf_ - Model::lln_};

		d_old = d_new;
		d_new = glm::distance(translate, points_[index % points_.size()]);

		if(d_new > d_old) {
			index++;
			delta = glm::normalize(points_[index % points_.size()] - translate)/10.0f;
			d_new = glm::distance(points_[index % points_.size()], translate);
		}

		Model::lln_ += delta;
		Model::urf_ += delta;

		translate = (Model::urf_ + Model::lln_)/2.0f;
		scale = Model::urf_ - Model::lln_;

		glPushMatrix();
			glTranslatef(translate.x, translate.y, translate.z);
			glScalef(scale.x, scale.y, scale.z);
			glutSolidCube(0.95);
		glPopMatrix();

	}
	/* @} */

	/* @@} */

}; /* namespace eRG */
