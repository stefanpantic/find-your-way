#include <iostream>
#include <array>
#include <cmath>
#include <cassert>
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
	* @brief Initialize eRG::Hub and its static members.
	*/
	void Hub::initialize(const int &argc, char **argv)
	{
		/* Check command line arguments */
		assert(argc > 1);

		/* Set clear color */
		glClearColor(0, 0, 0.1, 1);

		/* Enable depth test */
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		/* Hide cursor */
		glutSetCursor(GLUT_CURSOR_NONE);

		/* Set key repeat */
		glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

		/* Initialize fog */
		glEnable(GL_FOG);
		glFogf(GL_FOG_START, 9);
		glFogf(GL_FOG_END, 20);
		glFogf(GL_FOG_DENSITY, 0.09);

		/* Light setup */
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);

		/* Light parameters */
		std::array<float, 4> position{{2, 2, 2, 1}};
		std::array<float, 4> ambient{{0.1, 0.1, 0.1, 1}};
		std::array<float, 4> specular{{0.5, 0.5, 0.5, 1}};
		std::array<float, 4> diffuse{{170/265.0f, 160/256.0f, 150/256.0f, 1}};

		glLightfv(GL_LIGHT0, GL_POSITION, position.data());
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient.data());
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular.data());
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse.data());

		/* Initialize the View */
		mview.set_move_speed(0.1f);
		mview.set_look_sensitivity(util::pi/180.0f);
		mview.set_floor(2.0f);

		/* Initialize the Scene */
		if(argc > 2) {
			/* Enable textures */
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			/* Get texture paths */
			std::vector<std::string> tmp;
			for(int i = 2; i < argc; ++i) {
				tmp.push_back(argv[i]);
			}

			/* Give paths to Scene */
			mscene.set_textures(tmp);
		} else {
			/* Enable color material */
			glEnable(GL_COLOR_MATERIAL);
		}

		mscene.read_map(argv[1]);
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
		gluPerspective(70.0f, static_cast<float>(w)/h, 0.1f, 100.0f);

		/* Enter modelview */
		glMatrixMode(GL_MODELVIEW);
	}

	/*
	* @brief Function in charge od redrawing the scene.
	*/
	void Hub::display()
	{
		/* Clear the depth and color buffers */
		glClear(GL_COLOR_BUFFER_BIT |
				GL_DEPTH_BUFFER_BIT);

		/* Reset all matrix transformations */
		glLoadIdentity();

		/* Colision handling */
		Hub::__colision();

		/* Update lantern */
		auto eye{mview.get_eye()};
		glLightfv(GL_LIGHT0, GL_POSITION, std::array<float, 4>{{eye.x, eye.y, eye.z, 1}}.data());

		/* Reposition camera and set look at */
		mview.reposition();
		mview.look_at();

		/* World rendering */
		mscene.render();

		/* Swap buffers */
		glutSwapBuffers();
	}
	/* @} */

	/* Keyboard callbacks: */
	/* @{ */
	/*
	* @brief Move camera with wasd and jump with space.
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
				mview.set_look_parameter(opt::Look::horizontal, 1);
				break;
			case 'd':
				mview.set_look_parameter(opt::Look::horizontal, -1);
				break;
			case 'b':
				mview.set_move_parameter(opt::Move::forward, 10);
				glutTimerFunc(TIMER_BLINK_INTERVAL, timer, TIMER_BLINK);
				break;
			case ' ':
				mview.set_move_parameter(opt::Move::up, util::pi/50);
				break;
			case 'r':
				mview.look_at(	{3, 3, 3,},
								{1, 0, 1},
								{0, 1, 0});
				break;
		}
	}

	/*
	* @brief Stop camera motion on release of wasd keys.
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

	/*
	* @brief Move center point with mouse.
	*/
	void Hub::passive_motion(int x, int y)
	{
		y = height_ - y;

		/* Keep pointer in window */
		if (std::sqrt(std::pow(x - width_/2, 2) + std::pow(y - height_/2, 2)) > width_/4) {
			dx_ = width_/2;
			dy_ = height_/2;
			glutWarpPointer(dx_, dy_);

			return;
		}

		/* Move center point according to mouse movement */
		mview.set_look_parameter(opt::Look::horizontal, (dx_ - x)/3.0f);
		mview.set_look_parameter(opt::Look::vertical, (dy_ - y)/3.0f);

		auto forward{mview.dforward_}, strafe{mview.dstrafe_};
		mview.set_move_parameter(opt::Move::forward, 0);
		mview.set_move_parameter(opt::Move::strafe, 0);

		mview.reposition();

		mview.set_look_parameter(opt::Look::horizontal, 0);
		mview.set_look_parameter(opt::Look::vertical, 0);

		mview.dstrafe_ = strafe;
		mview.dforward_ = forward;

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
			case TIMER_RAVE:
				glClearColor(	static_cast<float>(std::rand())/RAND_MAX,
								static_cast<float>(std::rand())/RAND_MAX,
								static_cast<float>(std::rand())/RAND_MAX,
								1);
				glutTimerFunc(TIMER_RAVE_INTERVAL, Hub::timer, TIMER_RAVE);
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
		auto eye{mview.get_eye()};

		/* You won */
		if(eye.y > 20) {
			glDisable(GL_FOG);
			glutTimerFunc(TIMER_RAVE_INTERVAL, Hub::timer, TIMER_RAVE);
		}

		auto pbox{util::pbox(eye, 1.5)};

		/* Jumping */
		auto model{mscene.below(pbox)};
		if(model) {

			auto base{model->position().second.y};
			mview.set_floor(base + 2);

			/* If we are standing on a moving model, move us with it */
			if(eye.y == base + 2) {
				mview.eye_ += model->get_delta();
			}

		} else {
			mview.set_floor(-100);
		}

		/* Walls */
		auto aabb{mscene.aabb(pbox)};
		if(0 != aabb.size()) {

			/* Check all colided models */
			for(auto &&e : aabb) {

				/* Get movement vectors */
				auto dforward{mview.dforward_}, dstrafe{mview.dstrafe_};

				if(e != model) {

					/* Get model box */
					auto mbox{e->position()};

					/* Get colision points */
					auto package{util::handle_colision(pbox, mbox)};

					if(opt::Move::up != package.first) {

						/* Stop motion */
						mview.set_move_parameter(package.first, 0);
						mview.set_move_parameter(package.second, 0);

						/* Reposition the view */
						mview.reposition();

						/* TODO: workaround */
						float 	front{(package.first == opt::Move::forwardx) ? -dforward.x : -dforward.z},
								strafe{(package.second == opt::Move::strafex) ? -dstrafe.x : -dstrafe.z};

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
		}
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
