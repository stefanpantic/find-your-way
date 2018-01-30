#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "rghub.hpp"
#include "rgview.hpp"
#include "rgscene.hpp"
#include "rgcube.hpp"
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
	void Hub::initialize(const int &argc, char **argv)
	{
		/* Basic OpenGL initializers: */
		/* @{ */
		/* Set clear color */
		glClearColor(0, 0, 0.1, 1);

		/* Enable depth test */
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		/* Enable textures */
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

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
		std::vector<std::string> tmp;
		for(int i = 2; i < argc; ++i) {
			tmp.push_back(argv[i]);
		}

		mscene.set_textures(tmp);
		mscene.read_map(argv[1]);
		/* @} */

		/* Initialize fog */
		/* @{ */
		glEnable(GL_FOG);
		glFogf(GL_FOG_START, 10);
		glFogf(GL_FOG_END, 20);
		glFogf(GL_FOG_DENSITY, 0.07);
		/* @} */

		/* Temporary light setup: */
		/* @{ */
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);

		/* Light parameters */
		float position[]{2, 2, 2, 1};
		float ambient[]{0.1, 0.1, 0.1, 1};
		float specular[]{0.5, 0.5, 0.5, 1};
		float diffuse[]{110/265.0f, 110/256.0f, 150/256.0f, 1};

		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		/* @} */
	}
	/* @} */

	/* Display callbacks: */
	/* @{ */
	/*
	* @brief Called on window resize.
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
		Hub::__colision();
		/* @} */

		/* Reposition camera and set look at: */
		/* @{ */
		mview.reposition();
		mview.look_at();
		/* @} */

		/* Update lantern: */
		/* @{ */
		auto eye{mview.get_eye()};
		float position[]{eye.x, eye.y, eye.z, 1};
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		/* @} */

		/* World rendering: */
		/* @{ */
		glEnable(GL_LIGHTING);
		glColor3f(0.5, 0.5, 0.4);
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
				mview.set_move_parameter(opt::Move::up, util::pi/50);
				glutTimerFunc(TIMER_BLINK_INTERVAL, timer, TIMER_BLINK);
				break;
			case ' ':
				mview.set_move_parameter(opt::Move::up, util::pi/50);
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
	* @brief Move player on key press.
	*/
	void Hub::special(int key, int x, int y)
	{
		static_cast<void>(x);
		static_cast<void>(y);

		switch(key)
		{
			case GLUT_KEY_UP:
				mview.set_move_parameter(opt::Move::forward, 1);
				mview.set_move_parameter(opt::Move::forwardy, 0);
				break;
			case GLUT_KEY_DOWN:
				mview.set_move_parameter(opt::Move::forward, -1);
				mview.set_move_parameter(opt::Move::forwardy, 0);
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
	* @brief Stop player movement on key release.
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
	* @brief Move center point with mouse.
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
	* @brief Handle timers.
	*/
	void Hub::timer(int timer_id)
	{
		switch(timer_id)
		{
			case TIMER_REDISPLAY:
				glutPostRedisplay();
				glutTimerFunc(TIMER_REDISPLAY_INTERVAL, Hub::timer, TIMER_REDISPLAY);
				break;
			case TIMER_BLINK:
				mview.set_move_parameter(opt::Move::forward, 0);
				break;
		}
	}

	/*
	* @brief Whenever there's nothing to do call the display function to increase framerate.
	*/
	void Hub::idle()
	{
		glutPostRedisplay();
	}
	/* @} */

	/* Handle colisions between mview and mscene */
	/* @{ */
	/*
	* @brief Wrapper function for colision handing.
	*/
	void Hub::__colision()
	{
		/* Get player box */
		auto pbox{util::pbox(mview.get_eye(), 1.5)};

		/* Jumping */
		auto model{mscene.below(pbox)};
		if(model) {
			mview.set_floor(model->position().second.y + 2);
		} else {
			mview.set_floor(-100);
		}

		/* Walls */
		auto aabb{mscene.aabb(pbox)};
		if(aabb && aabb != model) {

			/* Get model box */
			auto mbox{aabb->position()};

			/* Get colision points */
			auto package{util::handle_colision(pbox, mbox)};

			if(opt::Move::up != package.first) {

				/* TODO: workaround */
				float 	front{(package.first == opt::Move::forwardx) ? -mview.dforward_.x : -mview.dforward_.z},
						strafe{(package.second == opt::Move::strafex) ? -mview.dstrafe_.x : -mview.dstrafe_.z};

				/* Set appropriate move parameters */
				mview.set_move_parameter(package.first, front);
				mview.set_move_parameter(package.second, strafe);

				/* Reposition the view */
				mview.reposition();

				/* Stop motion */
				mview.set_move_parameter(package.first, 0);
				mview.set_move_parameter(package.second, 0);
			}
		}
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
