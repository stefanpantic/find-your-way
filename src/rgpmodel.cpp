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
	PModel::PModel(	glm::vec3 translate,
					glm::vec3 scale,
					glm::vec4 rotate)
		:	Model{translate, scale, rotate}
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
	* @brief Get model position as (x,y,z) coordinates.
	*/
	const glm::vec3& PModel::position()
	{
		return Model::translate_;
	}
	/* @} */

	/* Draw: */
	/* @{ */
	/*
	* @brief Draw the model.
	*/
	void PModel::draw()
	{
		glPushMatrix();
			glTranslatef(Model::translate_.x, Model::translate_.y, Model::translate_.z);
			glutSolidCube(0.95);
		glPopMatrix();
	}
	/* @} */

	/* @@} */

}; /* namespace eRG */
