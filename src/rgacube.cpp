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
			delta_{((urf + lln)/2.0f != points_[0]) ? glm::normalize(points_[0] - (urf + lln)/2.0f)/30.0f : glm::normalize(points_[1] - points_[0])/30.0f},
			index_{0},
			dold_{0.0f}, dnew_{0.0f}
	{
		std::clog << "eRG::ACube: Default constructor" << std::endl;
	}

	/*
	* @brief Copy constructor.
	*/
	ACube::ACube(const ACube &other)
		:	Cube{other},
			points_{other.points_},
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
			delta_{std::move(other.delta_)},
			index_{std::move(other.index_)},
			dold_{std::move(other.dold_)}, dnew_{std::move(other.dnew_)}
	{
		std::clog << "eRG::ACube: Move constructor" << std::endl;
	}
	/* @} */

	/* Get delta: */
	/* @{ */
	/*
	* @brief Get movement delta.
	*/
	glm::vec3 ACube::get_delta() const
	{
		return glm::vec3(delta_);
	}
	/* @} */

	/* Draw: */
	/* @{ */
	/*
	* @brief Draw moving model.
	*
	* TODO: detailed description.
	*/
	void ACube::draw()
	{
		auto center{(lln_ + urf_)/2.0f};

		dold_ = dnew_;
		dnew_ = glm::distance(center, points_[index_]);

		if(dnew_ > dold_) {
			index_ = (index_ + 1) % points_.size();
			delta_ = glm::normalize(points_[index_] - center)/30.0f;
			dnew_ = glm::distance(points_[index_], center);
		}

		Cube::lln_ += delta_;
		Cube::urf_ += delta_;

		for(auto &&e : vertices_) {
			e += delta_;
		}

		Cube::draw();
	}
	/* @} */

	/* @@} */

}; /* namespace eRG */
