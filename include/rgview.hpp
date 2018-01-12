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
		enum class Transform;
		enum class View;
		enum class Position;
		enum class Special;
		enum class Delta;
		enum class Point;
		enum class LMS;
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
			explicit View(const View &other);

			/* Set matrix transformations */
			void look_at();
			void look_at(glm::vec3 eye, glm::vec3 center, glm::vec3 normal);

			/* Matrix mode */
			static void matrix_mode(opt::Transform mode);

			/* Get stored vectors */
			const glm::vec3& get(opt::Point p);

			/* Get/set look/move speed */
			const float& get(opt::LMS s);
			void set(opt::LMS s, float val);
			void set(opt::Delta delta, float val);

			/* Set world height */
			void set_floor(float wh);

			/* Main point transformmations */
			void center_move(opt::View direction);
			void eye_move(opt::Position direction);

			/* Special motion */
			void special(opt::Special action);
			void reset_special(opt::Special action);

			/* Redraw scene */
			void reposition_view();

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
			float d_theta_, d_phi_;

			/* Delta front, side vectors */
			glm::vec3 d_front_, d_side_;

			/* Delta up */
			float d_up_;

			/* Move, look speed */
			float msp_, lsp_;

			/* Blink indicator */
			bool blink_;

			/* Y base - world height indicator */
			float y_base_, jump_base_;
	}; /* class eRG::View */
	/* @} */

}; /* namespace eRG */
