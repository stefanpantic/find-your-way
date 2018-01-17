#include "rgcolision.hpp"

namespace eRG::util
{

	/* Helper functions for colision detection and handling: */
	/* @{ */
	/*
	* @brief Return player box from eye point.
	*/
	Box pbox(glm::vec3 eye, float h)
	{
		return std::make_pair(eye - glm::vec3{0.5, h, 0.5}, eye + glm::vec3{0.5, 0, 0.5});
	}

	/*
	* @brief Handle a colision.
	*/
	std::pair<opt::Move, float> handle_colision(const Box &pbox, const Box &mbox)
	{
		if(pbox.second.x <= mbox.second.x && pbox.first.x >= mbox.first.x) {

			/* Left/Right */
			if(	pbox.second.z >= mbox.first.z ||
				pbox.first.z <= mbox.second.z) {
				return std::make_pair(opt::Move::FORWARDZ, -0.1);
			}

		} else if(pbox.first.z >= mbox.first.x && pbox.second.z <= mbox.second.z) {

			/* Bottom/Top */
			if(	pbox.second.x >= mbox.first.z ||
				pbox.first.x <= mbox.second.x) {
				return std::make_pair(opt::Move::FORWARDX, -0.1);
			}
		}

		/* Placeholder for no action */
		return std::make_pair(opt::Move::UP, 0);
	}
	/* @} */

}; /* namespace eRG::util */