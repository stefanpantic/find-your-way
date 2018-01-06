#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <cmath>
#include "option.hpp"

namespace eRG
{

	/* Forward declaration of eRG::Hub */
	class Hub;

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
			static void identity_matrix();
			static void matrix_mode(opt::Transform mode);
			static void viewport(glm::vec2 lower_left, glm::vec2 upper_right);
			static void perspective(double fov, double aspect_ratio, double z_near, double z_far);
			static void ortho2D(double left, double right, double bottom, double top);
			static void ortho(double left, double right, double bottom, double top, double z_near, double z_far);

			/* Get stored vectors */
			const glm::vec3 &get_eye();
			const glm::vec3 &get_center();
			const glm::vec3 &get_normal();

			/* Get speeds */
			const float &get_mspeed();
			const float &get_lspeed();

			/* Set speeds */
			void set_mspeed(float msp);
			void set_lspeed(float lsp);

			/* Set world height */
			void set_ybase(float wh);

			/* Move center point */
			void center_move(opt::View direction);

			/* Move eye point */
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

			/* Delta front, side, vertical */
			float d_front_, d_side_, d_vert_;

			/* Move, look speed */
			float msp_, lsp_;

			/* Blink indicator */
			bool blink_;

			/* Y base - world height indicator */
			float y_base_, jump_base_;
	}; /* class eRG::View */
	/* @} */

}; /* namespace eRG */
