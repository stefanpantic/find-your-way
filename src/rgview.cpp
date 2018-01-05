#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <GL/glut.h>
#include "rgdefines.hpp"
#include "rgview.hpp"
#include "option.hpp"

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
			msp_{0.1f}, lsp_{util::pi/180.0f},
			world_{1.0f}
	{
		std::clog << "eRG::View: Default contructor" << std::endl;
	}

	/*
	* @brief Copy constructor.
	*/
	View::View(const View &other)
		:	eye_{other.eye_}, center_{other.center_}, normal_{other.normal_},
			msp_{other.msp_}, lsp_{other.lsp_}
	{
		std::clog << "eRG::View: Copy contructor" << std::endl;
	}
	/* @} */

	/* Set matrix transformations: */
	/* @{ */
	/*
	* @brief Load the identity matrix.
	*/
	void View::identity_matrix()
	{
		glLoadIdentity();
	}

	/*
	* @brief Set gluLookAt with stored parameters.
	*/
	void View::look_at()
	{
		// TODO: find an elegant workaround.
		auto tmp{eye_ + center_};

		gluLookAt(	eye_.x, eye_.y, eye_.z,
					tmp.x, tmp.y, tmp.z,
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
		using namespace opt;

		switch(mode)
		{
			case Transform::MODELVIEW:
				glMatrixMode(GL_MODELVIEW);
				break;
			case Transform::PROJECTION:
				glMatrixMode(GL_PROJECTION);
				break;
			case Transform::TEXTURE:
				glMatrixMode(GL_TEXTURE);
				break;
		}
	}

	/*
	* @brief Set the viewport.
	*
	* First parameter is the new lower left corner of the window, second parameter is the new
	* upper right corner of the window.
	*/
	void View::viewport(glm::vec2 lower_left, glm::vec2 upper_right)
	{
		glViewport(lower_left.x, lower_left.y, upper_right.x, upper_right.y);
	}

	/*
	* @brief Set the perspective view frustrum.
	*
	* First parameter is the field of view, second is the aspect ratio of the display
	* and the final two parameters are the near and far clipping planes.
	*/
	void View::perspective(double fov, double aspect_ratio, double z_near, double z_far)
	{
		gluPerspective(fov, aspect_ratio, z_near, z_far);
	}

	/*
	* @brief Sets the paralel projection square.
	*
	* Parameters are as follows: left clipping plane, right clipping plane,
	* bottom clipping plane, top clipping plane.
	*/
	void View::ortho2D(double left, double right, double bottom, double top)
	{
		gluOrtho2D(left, right, bottom, top);
	}

	/*
	* @brief Sets the paralel projection volume.
	*
	* Parameters are as follows: left clipping plane, right clipping plane,
	* bottom clipping plane, top clipping plane, z near plane, z far plane.
	*/
	void View::ortho(double left, double right, double bottom, double top, double z_near, double z_far)
	{
		glOrtho(left, right, bottom, top, z_near, z_far);
	}
	/* @} */

	/* Get stored vectors */
	/* @{ */
	/*
	* @brief Return stored @eye_ point.
	*/
	const glm::vec3& View::get_eye()
	{
		return eye_;
	}

	/*
	* @brief Return stored @center_ point.
	*/
	const glm::vec3& View::get_center()
	{
		return center_;
	}

	/*
	* @brief Return stored @normal_ vector.
	*/
	const glm::vec3& View::get_normal()
	{
		return normal_;
	}
	/* @} */

	/* Get speeds: */
	/* @{ */
	/*
	* @brief Set @eye_ point movement speed.
	*/
	const float& View::get_mspeed()
	{
		return msp_;
	}

	/*
	* @brief Get @center_ point movement speed.
	*/
	const float& View::get_lspeed()
	{
		return lsp_;
	}

	/* Set speeds: */
	/* @{ */
	/*
	* @brief Set @eye_ point movement speed.
	*/
	void View::set_mspeed(float msp)
	{
		msp_ = std::move(msp);
	}

	/*
	* @brief Set @center_ point movement speed.
	*/
	void View::set_lspeed(float lsp)
	{
		lsp_ = std::move(lsp);
	}
	/* @} */

	/* Set world height */
	void View::set_world_height(float wh)
	{
		world_ = wh;
	}

	/* Move center point: */
	/* @{ */
	/*
	* @brief Handle @center_ point movement options.
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
	* @brief Handle @eye_ point movement options.
	*/
	void View::eye_move(opt::Position direction)
	{
		using namespace opt;

		switch(direction)
		{
			case Position::UP:
				d_front_ = msp_;
				break;
			case Position::DOWN:
				d_front_ = -msp_;
				break;
			case Position::LEFT:
				d_side_ = msp_;
				break;
			case Position::RIGHT:
				d_side_ = -msp_;
				break;
			case Position::STOP_FORWARD:
				d_front_ = 0;
				break;
			case Position::STOP_SIDEWAYS:
				d_side_ = 0;
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
		using namespace opt;

		switch(action)
		{
			case Special::JUMP:
				if(!jump_) {
					jump_ = true;
				}
				break;
			case Special::BLINK:
				if(!blink_) {
					d_front_ = 3.0f;
					blink_ = true;
				}
				break;
			case Special::TIME:
				break;
		}
	}

	/*
	* @brief Reset ability state.
	*/
	void View::reset_special(opt::Special action)
	{
		using namespace opt;

		switch(action)
		{
			case Special::JUMP:
				jump_ = false;
				break;
			case Special::BLINK:
				blink_ = false;
				break;
			case Special::TIME:
				time_ = false;
				break;
		}
	}
	/* @} */

	/* Redraw scene: */
	/* @{ */
	/*
	* @brief If necessary, reposition camera.
	*/
	void View::reposition_view()
	{
		if(d_phi_ || d_theta_) {
			__center();
		}

		if(d_front_) {
			__eyef();
		}

		if(d_side_) {
			__eyes();
		}

		if(!jump_ && eye_.y > world_ + 3*msp_) {
			eye_.y -= 3*msp_;
		} else if(jump_) {
			eye_.y += 3*msp_;
		}
	}
	/* @} */

	/* Center and eye point movement: */
	/* @{ */
	/*
	* @brief Move center point on imaginary sphere with @eye_ as ceneter of sphere.
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
	* @brief Translate @eye_ front/back.
	*/
	void View::__eyef()
	{
		eye_.x += d_front_ * std::sin(theta_);
		eye_.z += d_front_ * std::cos(theta_);

		if(blink_) {
			eye_.y += d_front_ * std::cos(phi_);
		}
	}

	/*
	* @brief Translate @eye_ left/right.
	*/
	void View::__eyes()
	{
		eye_.x += d_side_ * std::cos(theta_);
		eye_.z += d_side_ * -std::sin(theta_);
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
