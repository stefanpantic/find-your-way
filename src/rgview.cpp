#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "rgdefines.hpp"
#include "rgview.hpp"
#include "rgoption.hpp"

namespace eRG
{

	/* View implementation: */
	/* @@{ */
	/* Construction: */
	/* @{ */
	/*
	* @brief Builds %View from passed vectors.
	*/
	View::View(glm::vec3 eye, glm::vec3 center, glm::vec3 normal)
		:	eye_{std::move(eye)}, center_{std::move(center)}, normal_{std::move(normal)},
			theta_{util::pi/4}, phi_{util::pi/2},
			dtheta_{0.0f}, dphi_{0.0f},
			dforward_{0.0f}, dstrafe_{0.0f}, dup_{0.0f},
			mspd_{0.0f}, lsen_{0.0f},
			y_base_{0.0f}, jump_base_{0.0f}
	{
		std::clog << "eRG::View: Default contructor" << std::endl;
	}

	/*
	* @brief Set the current matrix mode.
	*/
	void View::matrix_mode(opt::Transform mode)
	{
		switch(mode)
		{
			case opt::Transform::MODELVIEW:
				glMatrixMode(GL_MODELVIEW);
				break;
			case opt::Transform::PROJECTION:
				glMatrixMode(GL_PROJECTION);
				break;
			case opt::Transform::TEXTURE:
				glMatrixMode(GL_TEXTURE);
				break;
		}
	}
	/* @} */

	/* Set look at: */
	/* @{ */
	/*
	* @brief Set gluLookAt with stored parameters.
	*/
	void View::look_at()
	{
		gluLookAt(	eye_.x, eye_.y, eye_.z,
					eye_.x + center_.x, eye_.y + center_.y, eye_.z + center_.z,
					normal_.x, normal_.y, normal_.z);
	}

	/*
	* @brief Set gluLookAt with passed parameters.
	*/
	void View::look_at(glm::vec3 eye, glm::vec3 center, glm::vec3 normal)
	{
		eye_ = eye;
		center_ = center;
		normal_ = normal;

		look_at();
	}
	/* @} */

/*
* @brief Supressing warning about control reaching end of non-void function.
*
* The functiions below return values based off the value of an enum class parameter.
* All of the enum class options have been covered, so the end of the function cannot be reached
* before a condition is met.
*/
/* @{ */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"

	/* Get stored camera parameters */
	/* @{ */
	/*
	* @brief Return stored camera position vectors.
	*/
	const glm::vec3& View::get_point(opt::View option) const
	{
		switch(option)
		{
			case opt::View::EYE:
				return eye_;
			case opt::View::CENTER:
				return center_;
			case opt::View::NORMAL:
				return normal_;
		}
	}
	/* @} */

#pragma GCC diagnostic pop
/* @} */

	/* Get move/look parameters: */
	/* @{ */
	/*
	* @brief Get stored movement speed.
	*/
	const float& View::get_move_speed() const
	{
		return mspd_;
	}

	/*
	* @brief Get stored movement speed.
	*/
	const float& View::get_look_sensitivity() const
	{
		return lsen_;
	}
	/* @} */

	/* Set view parameters: */
	/* @{ */
	/*
	* @brief Set parameters for moving center point.
	*/
	void View::set_look_parameter(opt::Look opt, float val)
	{
		switch(opt)
		{
			case opt::Look::HORIZONTAL:
				dtheta_ = val;
				break;
			case opt::Look::VERTICAL:
				dphi_ = val;
				break;
		}
	}

	/*
	* @brief Set parameters for moving eye point.
	*/
	void View::set_move_parameter(opt::Move opt, float val)
	{
		switch(opt)
		{
			case opt::Move::FORWARD:
				dforward_ = glm::vec3(val);
				break;
			case opt::Move::FORWARDX:
				dforward_.x = val;
				break;
			case opt::Move::FORWARDY:
				dforward_.y = val;
				break;
			case opt::Move::FORWARDZ:
				dforward_.z = val;
				break;
			case opt::Move::STRAFE:
				dstrafe_ = glm::vec3(val);
				break;
			case opt::Move::STRAFEX:
				dstrafe_.x = val;
				break;
			case opt::Move::STRAFEY:
				dstrafe_.y = val;
				break;
			case opt::Move::STRAFEZ:
				dstrafe_.z = val;
				break;
			case opt::Move::UP:
				dup_ = val;
				break;
		}
	}

	/*
	* @brief Set center point movement sensitivity/
	*/
	void View::set_look_sensitivity(float val)
	{
		lsen_ = val;
	}

	/*
	* @brief Eye point movement speed.
	*/
	void View::set_move_speed(float val)
	{
		mspd_ = val;
	}
	/* @} */

	/* Set world height: */
	/* @{ */
	/*
	* @brief Set y axis base height.
	*/
	void View::set_floor(float base)
	{
		y_base_ = std::move(base);
	}
	/* @} */

	/* Redraw scene: */
	/* @{ */
	/*
	* @brief If necessary, reposition camera.
	*
	* TODO: Detailed explanation of eye_.y operations.
	*/
	void View::reposition()
	{
		if(dphi_ || dtheta_) {
			__center();
		}

		if(dforward_.x || dforward_.y || dforward_.z) {
			__eyef();
		}

		if(dstrafe_.x || dstrafe_.y || dstrafe_.z) {
			__eyes();
		}

		if(dup_) {
			__eyev();
		} else {
			__gravity();
		}
	}
	/* @} */

	/* Center and eye point movement: */
	/* @{ */
	/*
	* @brief Move center point on imaginary sphere with eye as center of sphere.
	*/
	void View::__center()
	{
		/* Update @theta and bind it to [0, 2*pi] */
		theta_ += lsen_ * dtheta_;
		if(theta_ >= 2*util::pi) {
			theta_ = 0;
		} else if(theta_ <= 0) {
			theta_ = 2*util::pi;
		}

		/* Update @phi and bind it to [0, pi] */
		phi_ += lsen_ * dphi_;
		if(phi_ >= util::pi - util::pi/90) {
			phi_ = util::pi - util::pi/90;
		} else if(phi_ <= util::pi/90) {
			phi_ = util::pi/90;
		}

		/* Update center point */
		center_.x = std::sin(theta_)*std::sin(phi_);
		center_.y = std::cos(phi_);
		center_.z = std::cos(theta_)*std::sin(phi_);
	}

	/*
	* @brief Translate eye front/back.
	*/
	void View::__eyef()
	{
		eye_.x += mspd_ * dforward_.x * std::sin(theta_);
		//eye_.y += mspd_ * dforward_.y * std::cos(phi_);
		eye_.z += mspd_ * dforward_.z * std::cos(theta_);
	}

	/*
	* @brief Translate eye left/right.
	*/
	void View::__eyes()
	{
		eye_.x += mspd_ * dstrafe_.x * std::cos(theta_);
		eye_.z += mspd_ * dstrafe_.z * -std::sin(theta_);
	}

	/*
	* @brief Translate eye up/down.
	*
	* TODO: A detailed explanation.
	*/
	void View::__eyev()
	{
		static float v{0};

		if(jump_base_ != y_base_ && eye_.y <= y_base_ + 0.1) {
			jump_base_ = y_base_;
			dup_ = v = 0;
		}

		eye_.y = 4*std::sin(v) + jump_base_;
		v += dup_;

		if(v >= util::pi) {
			v = dup_ = 0;
		}
	}

	/*
	* @brief Apply gravity to view.
	*/
	void View::__gravity()
	{
		if(eye_.y > y_base_) {
			/* Aproximate sin(x) = x for gravity */
			eye_.y -= 4*mspd_;

			/* Make sure we don't fall through the floor */
			if(eye_.y < y_base_) {
				eye_.y = y_base_;
				jump_base_ = y_base_;
			}

		}
		else if(eye_.y >= y_base_ - 0.4 && eye_.y - y_base_ < 0) {
			eye_.y = y_base_;
			jump_base_ = y_base_;
		}
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
