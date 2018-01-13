#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace eRG
{

	/* Forward declaration of eRG::Hub */
	class Hub;

	/* Forward declarations of eRG::opt enum classes */
	namespace opt
	{
		enum class Look;
		enum class Move;
		enum class View;
		enum class Transform;
	}; /* namespace eRG::opt */

	/* View declaration: */
	/* @{ */
	/*
	*	@brief Class used for handing MVP matrix options.
	*/
	class View
	{
		/* Friend class */
		friend class Hub;

		/* Public member functions */
		public:
			/* Construction */
			explicit View(	glm::vec3 eye 	 = {0, 0, -1},	/* Eye point */
							glm::vec3 center = {0, 0, 0},	/* To point */
							glm::vec3 normal = {0, 1, 0});	/* Normal vector */
			//explicit View(const View &other);

			/* Matrix mode */
			static void matrix_mode(opt::Transform mode);

			/* Set look at */
			void look_at();
			void look_at(glm::vec3 eye, glm::vec3 center, glm::vec3 normal);

			/* Get look and movement parameters */
			const glm::vec3& get_point(opt::View opt) const;
			const float& get_look_sensitivity() const;
			const float& get_move_speed() const;

			/* Set look and movement parameters */
			void set_look_parameter(opt::Look opt, float val);
			void set_move_parameter(opt::Move opt, float val);

			/* Set world height */
			void set_floor(float base);

			/* Redraw scene */
			void reposition();

		/* Private member functions */
		private:
			void __center();
			void __eyef();
			void __eyes();
			void __eyev();

		/* Private member variables */
		private:
			/* Eye position */
			glm::vec3 eye_;

			/* Look at point */
			glm::vec3 center_;

			/* Normal vector */
			glm::vec3 normal_;

			/* Theta, phi */
			float theta_, phi_;

			/* Delta theta, phi */
			float dtheta_, dphi_;

			/* Delta forward and strafe vectors */
			glm::vec3 dforward_, dstrafe_;

			/* Delta up */
			float dup_;

			/* Move speed and look sensitivity */
			float mspd_, lsen_;

			/* Y base - world height indicator */
			float y_base_, jump_base_;
	}; /* class eRG::View */
	/* @} */

}; /* namespace eRG */
