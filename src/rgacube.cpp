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
			index_{0},
			dold_{0.0f}, dnew_{0.0f}
	{
		std::clog << "eRG::ACube: Default constructor" << std::endl;

		if(points_.size() < 2) {
			return;
		}

		if((urf + lln)/2.0f != points_[0]) {
			delta_ = glm::normalize(points_[0] - (urf + lln)/2.0f)/30.0f;
		} else {
			delta_ = glm::normalize(points_[1] - points_[0])/30.0f;
		}
	}
	/* @} */

	/* Get delta: */
	/* @{ */
	/*
	* @brief Get movement delta.
	*/
	glm::vec3 ACube::delta() const
	{
		return glm::vec3(delta_);
	}
	/* @} */

	/* Update position: */
	/*
	* @brief Update model state.
	*
	* TODO: detailed description.
	*/
	/* @{ */
	void ACube::update()
	{
		auto center{(lln_ + urf_)/2.0f};

		dold_ = dnew_;
		dnew_ = glm::distance(center, points_[index_]);

		if(dnew_ > dold_) {
			index_ = (index_ + 1) % points_.size();
			delta_ = glm::normalize(points_[index_] - center)/30.0f;
			dnew_ = glm::distance(points_[index_], center);
		}

		lln_ += delta_;
		urf_ += delta_;

		for(auto &&e : vertices_) {
			e += delta_;
		}
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
