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
			d_theta_{0.0f}, d_phi_{0.0f},
			d_front_{0.0f}, d_side_{0.0f}, d_up_{0.0f},
			msp_{0.1f}, lsp_{util::pi/180.0f},
			y_base_{2.0f}, jump_base_{2.0f}
	{
		std::clog << "eRG::View: Default contructor" << std::endl;
	}

	/*
	* @brief Copy constructor.
	*/
	View::View(const View &other)
		:	eye_{other.eye_}, center_{other.center_}, normal_{other.normal_},
			msp_{other.msp_}, lsp_{other.lsp_},
			y_base_{other.y_base_}
	{
		std::clog << "eRG::View: Copy contructor" << std::endl;
	}
	/* @} */

	/* Set matrix transformations: */
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

	/* Get stored vectors */
	/* @{ */
	/*
	* @brief Return stored camera position vectors.
	*/
	const glm::vec3& View::get(opt::Point p)
	{
		switch(p)
		{
			case opt::Point::CENTER:
				return center_;
			case opt::Point::EYE:
				return eye_;
			case opt::Point::NORMAL:
				return normal_;
		}
	}
	/* @} */

	/* Get move/look speeds: */
	/* @{ */
	/*
	* @brief Get stored movement speed and look sensitivity.
	*/
	const float& View::get(opt::LMS s)
	{
		switch(s)
		{
			case opt::LMS::MOVE:
				return msp_;
			case opt::LMS::LOOK:
				return lsp_;
		}
	}
	/* @} */

#pragma GCC diagnostic pop
/* @} */

	/* Set move/look speeds: */
	/* @{ */
	/*
	* @brief Set stored movement speed and look sensitivity.
	*/
	void View::set(opt::LMS s, float val)
	{
		switch(s)
		{
			case opt::LMS::MOVE:
				msp_ = std::move(val);
				break;
			case opt::LMS::LOOK:
				lsp_ = std::move(val);
				break;
		}
	}
	/* @} */

	/* Set world height: */
	/* @{ */
	/*
	* @brief Set y axis base height.
	*/
	void View::set_floor(float wh)
	{
		y_base_ = std::move(wh);
	}
	/* @} */

	/* Set deltas: */
	/* @{ */
	/*
	* @brief Set individual movement deltas. Allows for finer camera control.
	*/
	void View::set(opt::Delta delta, float val)
	{
		using namespace opt;

		switch(delta)
		{
			/* Center point deltas */
			case Delta::CENTERX:
				d_theta_ = std::move(val);
				break;
			case Delta::CENTERY:
				d_phi_ = std::move(val);
				break;
			/* Eye point front deltas */
			case Delta::EYEF:
				d_front_ = glm::vec3(std::move(val));
				break;
			case Delta::EYEFX:
				d_front_.x = std::move(val);
				break;
			case Delta::EYEFY:
				d_front_.y = std::move(val);
				break;
			case Delta::EYEFZ:
				d_front_.z = std::move(val);
				break;
			/* Eye point side deltas */
			case Delta::EYES:
				d_side_ = glm::vec3(std::move(val));
				break;
			case Delta::EYESX:
				d_side_.x = std::move(val);
				break;
			case Delta::EYESY:
				d_side_.y = std::move(val);
				break;
			case Delta::EYESZ:
				d_side_.z = std::move(val);
				break;
			/* Eye point up deltas */
			case Delta::EYEV:
				d_up_ = std::move(val);
				break;
		}
	}
	/* @} */

	/* Move center point: */
	/* @{ */
	/*
	* @brief Handle center point movement options.
	*/
	void View::center_move(opt::View direction)
	{
		switch(direction)
		{
			case opt::View::UP:
				d_phi_ = -lsp_;
				break;
			case opt::View::DOWN:
				d_phi_ = lsp_;
				break;
			case opt::View::LEFT:
				d_theta_ = lsp_;
				break;
			case opt::View::RIGHT:
				d_theta_ = -lsp_;
				break;
			case opt::View::STOP_HORIZONTAL:
				d_theta_ = 0;
				break;
			case opt::View::STOP_VERTICAL:
				d_phi_ = 0;
				break;
		}
	}
	/* @} */

	/* Move eye point */
	/* @{ */
	/*
	* @brief Handle eye point movement options.
	*/
	void View::eye_move(opt::Position direction)
	{
		switch(direction)
		{
			case opt::Position::UP:
				d_front_ = glm::vec3(msp_);
				break;
			case opt::Position::DOWN:
				d_front_ = glm::vec3(-msp_);
				break;
			case opt::Position::LEFT:
				d_side_ = glm::vec3(msp_);
				break;
			case opt::Position::RIGHT:
				d_side_ = glm::vec3(-msp_);
				break;
			case opt::Position::STOP_FORWARD:
				d_front_ = glm::vec3(0);
				break;
			case opt::Position::STOP_SIDEWAYS:
				d_side_ = glm::vec3(0);
				break;
		}
	}
	/* @} */

	/* Special motion: */
	/* @{ */
	/*
	* TODO: implement special camera actions.
	*/
	void View::special(opt::Special action)
	{
		switch(action)
		{
			case opt::Special::JUMP:
				d_up_ = msp_;
				break;
			case opt::Special::BLINK:
				if(!blink_) {
					d_front_ = glm::vec3(30*msp_);
					blink_ = true;
				}
				break;
			case opt::Special::TIME:
				// TODO: Implement time control.
				break;
		}
	}

	/*
	* @brief Reset ability state.
	*/
	void View::reset_special(opt::Special action)
	{
		switch(action)
		{
			case opt::Special::JUMP:
				// TODO: Jump reseter.
				break;
			case opt::Special::BLINK:
				blink_ = false;
				break;
			case opt::Special::TIME:
				// TODO: Time reseter.
				break;
		}
	}
	/* @} */

	/* Redraw scene: */
	/* @{ */
	/*
	* @brief If necessary, reposition camera.
	*
	* TODO: Detailed explanation of eye_.y operations.
	*/
	void View::reposition_view()
	{
		if(d_phi_ || d_theta_) {
			__center();
		}

		if(d_front_.x || d_front_.y || d_front_.z) {
			__eyef();
		}

		if(d_side_.x || d_side_.y || d_side_.z) {
			__eyes();
		}

		if(d_up_) {
			__eyev();
		} else if(eye_.y > y_base_) {
			/* Aproximate sin(x) = x for gravity */
			eye_.y -= 4*msp_;

			/* Make sure we don't fall through the floor */
			if(eye_.y < y_base_) {
				eye_.y = y_base_;
				jump_base_ = y_base_;
			}
		} else if(eye_.y >= y_base_ - 0.4 && eye_.y - y_base_ < 0) {
			eye_.y = y_base_;
			jump_base_ = y_base_;
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
		theta_ += d_theta_;
		if(theta_ >= 2*util::pi) {
			theta_ = 0;
		} else if(theta_ <= 0) {
			theta_ = 2*util::pi;
		}

		/* Update @phi and bind it to [0, pi] */
		phi_ += d_phi_;
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
		eye_.x += d_front_.x * std::sin(theta_);
		eye_.y += (blink_) ? d_front_.y * std::cos(phi_) : 0;
		eye_.z += d_front_.z * std::cos(theta_);
	}

	/*
	* @brief Translate eye left/right.
	*/
	void View::__eyes()
	{
		eye_.x += d_side_.x * std::cos(theta_);
		eye_.z += d_side_.z * -std::sin(theta_);
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
			d_up_ = 0;
			v = 0;
		} else if(jump_base_ != y_base_ && eye_.y == y_base_) {
			jump_base_ = y_base_;
		}

		eye_.y = 4*std::sin(v) + jump_base_;
		v += d_up_;

		if(v >= util::pi) {
			v = 0;
			d_up_ = 0;
		}
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
