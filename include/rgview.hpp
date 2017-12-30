#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <cmath>
#include "option.hpp"

namespace eRG
{

	/* View declaration: */
	/* @{ */
	/*
	*	@brief Class used for handing visual rendering options.
	*/
	class View
	{
		/* Public member functions */
		public:
			/* Construction */
			explicit View(	glm::vec3 eye 	 = {0, 0, -1},	/* Eye point */
							glm::vec3 center = {0, 0, 0},	/* To point */
							glm::vec3 normal = {0, 1, 0});	/* Normal vector */
			explicit View(const View &other);

			/* Set matrix transformations */
			void identity_matrix();
			void look_at();
			void look_at(glm::vec3 eye, glm::vec3 center, glm::vec3 normal);
			void matrix_mode(opt::Transform mode);
			void viewport(glm::vec2 lower_left, glm::vec2 upper_right);
			void perspective(double fov, double aspect_ratio, double z_near, double z_far);

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

			/* Move center point */
			virtual void center_move(opt::View direction);

			/* Move eye point */
			virtual void eye_move(opt::Position direction);

			/* Special motion */
			virtual void special(opt::Special action);

			/* Redraw scene */
			virtual void reposition_view();

		/* Protected member functions */
		protected:
			virtual void __center();
			virtual void __eyef();
			virtual void __eyes();

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

			/* Delta front, side */
			float d_front_, d_side_;

			/* Speeds */
			float msp_, lsp_;
	}; /* class eRG::View */
	/* @} */

}; /* namespace eRG */
