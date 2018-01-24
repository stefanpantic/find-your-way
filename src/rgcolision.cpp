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
				return std::make_pair(opt::Move::forwardz, -0.5);
			}

		} else if(pbox.first.z >= mbox.first.z && pbox.second.z <= mbox.second.z) {

			/* Bottom/Top */
			if(	pbox.second.x >= mbox.first.x ||
				pbox.first.x <= mbox.second.x) {
				return std::make_pair(opt::Move::forwardx, -0.5);
			}
		}

		/* Placeholder for no action */
		return std::make_pair(opt::Move::up, 0);
	}
	/* @} */

}; /* namespace eRG::util */
