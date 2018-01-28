#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <glm/vec2.hpp>
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
	PModel::PModel(	glm::vec3 lln,
					glm::vec3 urf,
					const std::vector<std::string> &paths)
		:	Model{lln, urf, paths}
	{
		std::clog << "eRG::PModel: Default constructor" << std::endl;

		glNewList(dlist_, GL_COMPILE);
			Model::initialize_model();
		glEndList();
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
		glCallList(dlist_);
	}
	/* @} */

	/* @@} */

}; /* namespace eRG */
