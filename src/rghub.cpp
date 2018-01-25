#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "rghub.hpp"
#include "rgview.hpp"
#include "rgscene.hpp"
#include "rgmodel.hpp"
#include "rgdefines.hpp"
#include "rgcolision.hpp"
#include "rgoption.hpp"
#include "debug.hpp"

namespace eRG
{

	/* Hub implementation: */
	/* @@{ */
	/* Static member initialization: */
	/* @{ */
	int Hub::width_{0}, Hub::height_{0};
	int Hub::dx_{0}, Hub::dy_{0};
	View Hub::mview{glm::vec3{2, 2, 2}};
	Scene Hub::mscene{};
	/* @} */

	/* Initializer: */
	/* @{ */
	/*
	* TODO: @brief decription
	*/
	void Hub::initialize(std::string path)
	{
		/* Basic OpenGL initializers: */
		/* @{ */
		/* Set clear color */
		glClearColor(0, 0, 0.1, 1);

		/* Enable depth test */
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		/* Hide cursor */
		glutSetCursor(GLUT_CURSOR_NONE);

		/* Set key repeat */
		glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
		/* @} */

		/* Initialize the View: */
		/* @{ */
		mview.set_move_speed(0.1f);
		mview.set_look_sensitivity(util::pi/180.0f);
		mview.set_floor(2.0f);
		/* @} */

		/* Initialize the Scene: */
		/* @{ */
		mscene.read_map(path);
		/* @} */

		/* Temporary light setup: */
		/* @{ */
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);

		/* Light parameters */
		float position[]{5, 5, 5, 1};
		float ambient[]{0.1, 0.1, 0.1, 1};
		float specular[]{0.5, 0.5, 0.5, 1};
		float diffuse[]{110/256.0f, 110/256.0f, 150/256.0f, 1};

		/* Material parameters */
		//float material_ambient[]{0.1, 0.1, 0.1, 1};
		//float material_specular[]{0.8, 0.8, 0.8, 1};
		//float material_diffuse[]{20/256.0f, 20/256.0f, 30/256.0f, 1};
		//float shininess{2};

		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

		//glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
		//glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
		//glMaterialf(GL_FRONT, GL_SHININESS, shininess);
		/* @} */
	}
	/* @} */

	/* Display callbacks: */
	/* @{ */
	/*
	* TODO: @brief decription
	*/
	void Hub::reshape(int w, int h)
	{
		/* Capture the width and height of the window */
		width_ = w;
		height_ = h;

		/* Center the cursor */
		dx_ = w/2;
		dy_ = h/2;
		glutWarpPointer(dx_, dy_);

		/* Set viewport to entire window */
		glViewport(0, 0, w, h);

		/* Enter projection mode */
		glMatrixMode(GL_PROJECTION);

		/* Reset projection matrix*/
		glLoadIdentity();

		/* Set perspective */
		gluPerspective(70.0f, (float)w/h, 0.1f, 100.0f);

		/* Enter modelview */
		glMatrixMode(GL_MODELVIEW);
	}

	/*
	* TODO: @brief decription
	*/
	void Hub::display()
	{
		/* Clear the depth and color buffers */
		glClear(GL_COLOR_BUFFER_BIT |
				GL_DEPTH_BUFFER_BIT);

		/* Reset all matrix transformations */
		glLoadIdentity();

		/* Colision handling: */
		/* @{ */
		/* Get player box */
		auto pbox{util::pbox(mview.get_eye(), 1.5)};

		/* Vertical */
		auto model{mscene.below(pbox)};
		if(model) {
			mview.set_floor(model->position().second.y + 2);
		} else {
			mview.set_floor(-10);
		}

		/* Horizontal */
		auto aabb{mscene.aabb(pbox)};
		if(aabb && aabb != model) {

			auto mbox{aabb->position()};
			auto package{util::handle_colision(pbox, mbox)};

			if(opt::Move::up != package.first) {
				mview.set_move_parameter(package.first, package.second);
				mview.reposition();
				mview.set_move_parameter(package.first, 0);
			}
		}
		/* @} */

		/* Reposition camera and set look at: */
		/* @{ */
		mview.reposition();
		mview.look_at();
		/* @} */

		/* World rendering: */
		/* @{ */
		glEnable(GL_LIGHTING);
		glColor3f(0.3, 0.3, 0.3);
		mscene.render();
		glDisable(GL_LIGHTING);
		/* @} */

		/* Coordinate system: */
		/* @{ */
		glPushMatrix();
			glScalef(10, 10, 10);
			glLineWidth(5);
			DEBUG::coordinate_system();
			glLineWidth(1);
		glPopMatrix();
		/* @} */

		/* Swap buffers */
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
			case 27:
				std::exit(0);
			case 'w':
				mview.set_look_parameter(opt::Look::vertical, -1);
				break;
			case 's':
				mview.set_look_parameter(opt::Look::vertical, 1);
				break;
			case 'a':
				mview.set_look_parameter(opt::Look::horizontal, -1);
				break;
			case 'd':
				mview.set_look_parameter(opt::Look::horizontal, 1);
				break;
			case 'b':
				mview.set_move_parameter(opt::Move::forward, 30);
				glutTimerFunc(TIMER_BLINK_INTERVAL, timer, TIMER_BLINK);
				break;
			case ' ':
				mview.set_move_parameter(opt::Move::up, util::pi/60.0f);
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
				mview.set_look_parameter(opt::Look::vertical, 0);
				break;
			case 'a':
			case 'd':
				mview.set_look_parameter(opt::Look::horizontal, 0);
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
				mview.set_move_parameter(opt::Move::forward, 1);
				break;
			case GLUT_KEY_DOWN:
				mview.set_move_parameter(opt::Move::forward, -1);
				break;
			case GLUT_KEY_LEFT:
				mview.set_move_parameter(opt::Move::strafe, 1);
				break;
			case GLUT_KEY_RIGHT:
				mview.set_move_parameter(opt::Move::strafe, -1);
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
				mview.set_move_parameter(opt::Move::forward, 0);
				break;
			case GLUT_KEY_LEFT:
			case GLUT_KEY_RIGHT:
				mview.set_move_parameter(opt::Move::strafe, 0);
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
			dx_ = width_/2;
			dy_ = height_/2;
			glutWarpPointer(dx_, dy_);

			return;
		}

		mview.set_look_parameter(opt::Look::horizontal, (dx_ - x)/2.0f);
		mview.set_look_parameter(opt::Look::vertical, (dy_ - y)/2.0f);

		mview.reposition();

		mview.set_look_parameter(opt::Look::horizontal, 0);
		mview.set_look_parameter(opt::Look::vertical, 0);

		dx_ = x;
		dy_ = y;
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
				mview.set_move_parameter(opt::Move::forward, 0);
				break;
		}
	}

	/*
	* TODO: Implement idle function.
	*/
	void Hub::idle()
	{
		glutPostRedisplay();
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
