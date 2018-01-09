#include <iostream>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include "rgpmodel.hpp"

namespace eRG
{

	/* PModel declaration: */
	/* @@{ */
	/* Construction */
	/* @{ */
	/*
	* @brief Builds instance of %eRG::PModel.
	*/
	PModel::PModel(	glm::vec3 lower_left_near,
					glm::vec3 upper_right_far)
		:	Model{lower_left_near, upper_right_far},
			translate_{(lower_left_near + upper_right_far)/2.0f},
			scale_{upper_right_far - lower_left_near}
	{
		std::clog << "eRG::PModel: Default constructor" << std::endl;
	}

	/*
	* @brief Copy constructor.
	*/
	PModel::PModel(const PModel &other)
		:	Model{other}
	{
		std::clog << "eRG::PModel: Copy constructor" << std::endl;
	}

	/*
	* @brief Move constructor.
	*/
	PModel::PModel(PModel &&other)
		:	Model{std::move(other)}
	{
		std::clog << "eRG::PModel: Move constructor" << std::endl;
	}
	/* @} */

	/* Position: */
	/* @{ */
	/*
	* @brief Get model position as lower left near corner and upper far right corner coordinates.
	*/
	std::pair<glm::vec3, glm::vec3> PModel::position()
	{
		return {glm::vec3{Model::lln_}, glm::vec3{Model::urf_}};
	}
	/* @} */

	/* Draw: */
	/* @{ */
	/*
	* TODO: Implement draw function.
	*/
	void PModel::draw()
	{
		glPushMatrix();
			glTranslatef(translate_.x, translate_.y, translate_.z);
			glScalef(scale_.x, scale_.y, scale_.z);
			glutSolidCube(0.95);
		glPopMatrix();
	}
	/* @} */

	/* @@} */

}; /* namespace eRG */
