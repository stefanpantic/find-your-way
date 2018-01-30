#include <iostream>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "rgacube.hpp"
#include "rgimage.hpp"

namespace eRG
{

	/* ACube declaration: */
	/* @@{ */
	/* Construction */
	/* @{ */
	/*
	* @brief Builds instance of %eRG::ACube.
	*/
	ACube::ACube(	glm::vec3 lln,
					glm::vec3 urf,
					std::vector<glm::vec3> &&points,
					const std::vector<std::string> &paths)
		:	Cube{lln, urf, paths},
			points_{std::move(points)},
			dlist_{glGenLists(1)},
			translate_{(urf_ + lln_)/2.0f},
			delta_{(translate_ != points_[0]) ? glm::normalize(points_[0] - translate_)/30.0f : glm::normalize(points_[1] - points_[0])/30.0f},
			index_{0},
			dold_{0.0f}, dnew_{0.0f}
	{
		std::clog << "eRG::ACube: Default constructor" << std::endl;

		glNewList(dlist_, GL_COMPILE);
			glTranslatef(-translate_.x, -translate_.y, -translate_.z);
			Cube::draw();
		glEndList();
	}

	/*
	* @brief Copy constructor.
	*/
	ACube::ACube(const ACube &other)
		:	Cube{other},
			points_{other.points_},
			dlist_{other.dlist_},
			translate_{other.translate_},
			delta_{other.delta_},
			index_{other.index_},
			dold_{other.dold_}, dnew_{other.dnew_}
	{
		std::clog << "eRG::ACube: Copy constructor" << std::endl;
	}

	/*
	* @brief Move constructor.
	*/
	ACube::ACube(ACube &&other)
		:	Cube{std::move(other)},
			points_{std::move(other.points_)},
			dlist_{std::move(other.dlist_)},
			translate_{std::move(other.translate_)},
			delta_{std::move(other.delta_)},
			index_{std::move(other.index_)},
			dold_{std::move(other.dold_)}, dnew_{std::move(other.dnew_)}
	{
		std::clog << "eRG::ACube: Move constructor" << std::endl;
	}

	/*
	* @brief Destructor.
	*/
	ACube::~ACube()
	{
		glDeleteLists(dlist_, 1);
	}
	/* @} */

	/* Draw: */
	/* @{ */
	/*
	* @brief Draw moving model.
	*
	* TODO: cleanup code, detailed description.
	*/
	void ACube::draw()
	{
		dold_ = dnew_;
		dnew_ = glm::distance(translate_, points_[index_]);

		if(dnew_ > dold_) {
			index_ = (index_ + 1) % points_.size();
			delta_ = glm::normalize(points_[index_] - translate_)/30.0f;
			dnew_ = glm::distance(points_[index_], translate_);
		}

		Cube::lln_ += delta_;
		Cube::urf_ += delta_;
		translate_ += delta_;

		glPushMatrix();
			glTranslatef(translate_.x, translate_.y, translate_.z);
			glCallList(dlist_);
		glPopMatrix();
	}
	/* @} */

	/* @@} */

}; /* namespace eRG */
