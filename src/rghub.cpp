#include <iostream>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include "../include/option.hpp"
#include "../include/rghub.hpp"

namespace eRG
{

	/* Hub implementation: */
	/* @@{ */
	/* Static member initialization: */
	/* @{ */
	int Hub::width_{0}, Hub::height_{0};
	int Hub::d_x_{0}, Hub::d_y_{0};
	View Hub::view_{};
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
	void Hub::display()
	{
		glClear(GL_COLOR_BUFFER_BIT |
				GL_DEPTH_BUFFER_BIT);

		view_.reposition_view();
		view_.look_at();

		glPushMatrix();
			glColor3f(1,1,0);
			glutWireTeapot(2);
		glPopMatrix();

		glutSwapBuffers();
	}

	/*
	* TODO: @brief decription
	*/
	void Hub::reshape(int w, int h)
	{
		width_ = w;
		height_ = h;

		view_.matrix_mode(opt::Transform::PROJECTION);
		view_.identity_matrix();

		view_.viewport(
				glm::vec2{0, 0},
				glm::vec2{w, h}
				);

		view_.perspective(60.0f, static_cast<float>(w)/h, 1.0f, 100.0f);
		view_.matrix_mode(opt::Transform::MODELVIEW);
	}
	/* @} */

	/* Keyboard callbacks */
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
				view_.center_move(opt::View::UP);
				break;
			case 's':
				view_.center_move(opt::View::DOWN);
				break;
			case 'a':
				view_.center_move(opt::View::LEFT);
				break;
			case 'd':
				view_.center_move(opt::View::RIGHT);
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
				view_.center_move(opt::View::STOP_VERTICAL);
				break;
			case 'a':
			case 'd':
				view_.center_move(opt::View::STOP_HORIZONTAL);
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
				view_.eye_move(opt::Position::UP);
				break;
			case GLUT_KEY_DOWN:
				view_.eye_move(opt::Position::DOWN);
				break;
			case GLUT_KEY_LEFT:
				view_.eye_move(opt::Position::LEFT);
				break;
			case GLUT_KEY_RIGHT:
				view_.eye_move(opt::Position::RIGHT);
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
				view_.eye_move(opt::Position::STOP_FORWARD);
				break;
			case GLUT_KEY_LEFT:
			case GLUT_KEY_RIGHT:
				view_.eye_move(opt::Position::STOP_SIDEWAYS);
				break;
		}
	}
	/* @} */


	/* Timer functions */
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
	/* @} */
	/* @@} */

}; /* namespace eRG */
