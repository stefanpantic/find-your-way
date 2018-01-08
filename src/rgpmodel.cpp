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

	/* Position: */
	/* @{ */
	/*
	* @brief Get model position as (x,y,z) coordinates.
	*/
	std::pair<Model::v3cr, Model::v3cr> PModel::position()
	{
		return std::make_pair(Model::lln_, Model::urf_);
	}
	/* @} */

	/* Draw: */
	/* @{ */
	/*
	* TODO: Implement draw function.
	*/
	void PModel::draw()
	{
		auto translate{(Model::urf_ + Model::lln_)/2.0f};
		glTranslatef(translate.x, translate.y, translate.z);
		glutSolidCube(0.95);
	}
	/* @} */

	/* @@} */

}; /* namespace eRG */
