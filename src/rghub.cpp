#include <iostream>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include "rghub.hpp"
#include "rgview.hpp"
#include "rgdefines.hpp"
#include "option.hpp"
#include "debug.hpp"

namespace eRG
{

	/* Hub implementation: */
	/* @@{ */
	/* Static member initialization: */
	/* @{ */
	int Hub::width_{0}, Hub::height_{0};
	int Hub::d_x_{0}, Hub::d_y_{0};
	View Hub::mview{glm::vec3{0, 1, 0},
					glm::vec3{1, 1, 1},
					glm::vec3{0, 1, 0}};
	/* @} */

	/* Initializer: */
	/* @{ */
	/*
	* TODO: @brief decription
	*/
	void Hub::initialize()
	{
		/* Set clear color */
		glClearColor(0, 0, 0, 1);

		/* Enable depth test */
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		/* Set key repeat */
		glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	}
	/* @} */

	/* Display callbacks: */
	/* @{ */
	/*
	* TODO: @brief decription
	*/
	void Hub::reshape(int w, int h)
	{
		width_ = w;
		height_ = h;

		glutWarpPointer(w/2, h/2);

		View::matrix_mode(opt::Transform::PROJECTION);
		View::identity_matrix();

		View::viewport(	glm::vec2{0, 0},
						glm::vec2{w, h});

		View::perspective(60.0f, static_cast<float>(w)/h, 0.1f, 100.0f);
		View::matrix_mode(opt::Transform::MODELVIEW);
	}

	/*
	* TODO: @brief decription
	*/
	void Hub::display()
	{
		glClear(GL_COLOR_BUFFER_BIT |
				GL_DEPTH_BUFFER_BIT);

		View::identity_matrix();

		mview.reposition_view();
		mview.look_at();

		/* Temporary */
		glPushMatrix();
			glLineWidth(5);
				DEBUG::coordinate_system();
			glLineWidth(1);
			DEBUG::first_octant(5);
		glPopMatrix();

		glutSwapBuffers();
	}
	/* @} */

	/* Keyboard callbacks: */
	/* @{ */
	/*
	* TODO: @brief decription
	*/
	void Hub::keyboard(unsigned char key, int x, int y)
	{
		static_cast<void>(x);
		static_cast<void>(y);

		switch(key)
		{
			case 'w':
				mview.center_move(opt::View::UP);
				break;
			case 's':
				mview.center_move(opt::View::DOWN);
				break;
			case 'a':
				mview.center_move(opt::View::LEFT);
				break;
			case 'd':
				mview.center_move(opt::View::RIGHT);
				break;
		}
	}

	/*
	* TODO: @brief decription
	*/
	void Hub::keyboard_up(unsigned char key, int x, int y)
	{
		static_cast<void>(x);
		static_cast<void>(y);

		switch(key)
		{
			case 27:
				std::exit(0);
			case 'w':
			case 's':
				mview.center_move(opt::View::STOP_VERTICAL);
				break;
			case 'a':
			case 'd':
				mview.center_move(opt::View::STOP_HORIZONTAL);
				break;
		}
	}

	/*
	* TODO: @brief decription
	*/
	void Hub::special(int key, int x, int y)
	{
		static_cast<void>(x);
		static_cast<void>(y);

		switch(key)
		{
			case GLUT_KEY_UP:
				mview.eye_move(opt::Position::UP);
				break;
			case GLUT_KEY_DOWN:
				mview.eye_move(opt::Position::DOWN);
				break;
			case GLUT_KEY_LEFT:
				mview.eye_move(opt::Position::LEFT);
				break;
			case GLUT_KEY_RIGHT:
				mview.eye_move(opt::Position::RIGHT);
				break;
		}
	}

	/*
	* TODO: @brief decription
	*/
	void Hub::special_up(int key, int x, int y)
	{
		static_cast<void>(x);
		static_cast<void>(y);

		switch(key)
		{
			case GLUT_KEY_UP:
			case GLUT_KEY_DOWN:
				mview.eye_move(opt::Position::STOP_FORWARD);
				break;
			case GLUT_KEY_LEFT:
			case GLUT_KEY_RIGHT:
				mview.eye_move(opt::Position::STOP_SIDEWAYS);
				break;
		}
	}
	/* @} */

	/* Mouse callbacks: */
	/* @{ */
	/*
	* TODO: Implement mouse function.
	*/
	void Hub::mouse(int key, int state, int x, int y)
	{
		static_cast<void>(key);
		static_cast<void>(state);
		static_cast<void>(x);
		static_cast<void>(y);
	}

	/*
	* TODO: Implement motion function.
	*/
	void Hub::motion(int x, int y)
	{
		static_cast<void>(x);
		static_cast<void>(y);
	}

	/*
	* TODO: @brief decription.
	*/
	void Hub::passive_motion(int x, int y)
	{
		y = height_ - y;

		mview.d_theta_ = mview.get_lspeed() * (d_x_ - x);
		mview.d_phi_ = mview.get_lspeed() * (d_y_ - y);

		d_x_ = x;
		d_y_ = y;

		mview.reposition_view();

		mview.center_move(opt::View::STOP_VERTICAL);
		mview.center_move(opt::View::STOP_HORIZONTAL);
	}
	/* @} */

	/* Timer callbacks: */
	/* @{ */
	/*
	* TODO: @brief decription
	*/
	void Hub::timer(int timer_id)
	{
		switch(timer_id)
		{
			case TIMER0:
				glutPostRedisplay();
				glutTimerFunc(TIMER0_INTERVAL, timer, TIMER0);
				break;
		}
	}

	/*
	* TODO: Implement idle function.
	*/
	void Hub::idle()
	{}
	/* @} */
	/* @@} */

}; /* namespace eRG */
