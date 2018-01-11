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
		:	Model{lower_left_near, upper_right_far}
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

	/* Draw: */
	/* @{ */
	/*
	* @brief Draw the stored stationary model.
	*/
	void PModel::draw()
	{
		glPushMatrix();
			Model::apply_transformations();
			glutSolidCube(1);
		glPopMatrix();
	}
	/* @} */

	/* @@} */

}; /* namespace eRG */
