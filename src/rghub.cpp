#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <glm/vec2.hpp>
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

		/* Hide cursor */
		glutSetCursor(GLUT_CURSOR_NONE);

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

		d_x_ = w/2;
		d_y_ = h/2;
		glutWarpPointer(d_x_, d_y_);

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

		/* Set stairs - temporary colision test: */
		/* @{ */
		auto eye{mview.get_eye()};
		if(eye.x <= 10 && eye.x >= 0 && eye.z >= 0 && eye.z <= 10) {
			mview.set_ybase(std::round(eye.x) + 1);
		} else {
			mview.set_ybase(1);
		}
		/* @} */

		mview.reposition_view();
		mview.look_at();

		/* Draw stairs - temporary: */
		/* @{ */
		glPushMatrix();
			glEnable(GL_COLOR_MATERIAL);
			glEnable(GL_NORMALIZE);

			float light[]{-1, -1, -1, 0};
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glLightfv(GL_LIGHT0, GL_POSITION, light);

			for(float i = 1.5; i < 10; ++i)
			{
				glPushMatrix();
					glColor3f(0.3,0.3,0.3);
					glTranslatef(i, i - 1, 0);
						for(float i = 0.5; i < 10; ++i)
						{
							glPushMatrix();
								glTranslatef(0, 0, i);
								glutSolidCube(0.95);
							glPopMatrix();
						}
				glPopMatrix();
			}

			glDisable(GL_LIGHTING);

			/* Coordinate system */
			glPushMatrix();
				glScalef(10, 10, 10);
				glLineWidth(5);
				DEBUG::coordinate_system();
				glLineWidth(1);
			glPopMatrix();

			DEBUG::first_octant(10);

			glPushMatrix();
				glTranslatef(5, 0, 5);
				DEBUG::floor(5);
			glPopMatrix();
		glPopMatrix();
		/* @} */

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
			/* Exit the game */
			case 27:
				std::exit(0);
			/* Manual camera movement controls */
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
			/* Ability controls */
			case 'b':
				mview.special(opt::Special::BLINK);
				glutTimerFunc(TIMER_BLINK_INTERVAL, timer, TIMER_BLINK);
				break;
			case ' ':
				mview.special(opt::Special::JUMP);
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

		if (std::sqrt(std::pow(x - width_/2, 2) + std::pow(y - height_/2, 2)) > width_/4) {
			d_x_ = width_/2;
			d_y_ = height_/2;
			glutWarpPointer(d_x_, d_y_);

			return;
		}

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
			case TIMER_REDISPLAY:
				glutPostRedisplay();
				glutTimerFunc(TIMER_REDISPLAY_INTERVAL, timer, TIMER_REDISPLAY);
				break;
			case TIMER_BLINK:
				mview.eye_move(opt::Position::STOP_FORWARD);
				mview.reset_special(opt::Special::BLINK);
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
