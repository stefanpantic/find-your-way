#pragma once

#include <iostream>

namespace eRG
{

	/* Forward declarations: */
	/* @{ */
	class View;
	class Scene;
	class Cube;
	/* @} */

	/* Hub declaration: */
	/* @{ */
	/*
	* @brief Central Hub in charge of handling OpenGL functionality.
	*/
	class Hub
	{
		/* Public member functions */
		public:
			/* Initializer */
			static void initialize(const int &argc, char **argv);

			/* Display callbacks */
			static void reshape(int w, int h);
			static void display();

			/* Keyboard callbacks */
			static void keyboard(unsigned char key, int x, int y);
			static void keyboard_up(unsigned char key, int x, int y);
			static void special(int key, int x, int y);
			static void special_up(int key, int x, int y);

			/* Mouse callbacks */
			static void mouse(int key, int state, int x, int y);
			static void motion(int x, int y);
			static void passive_motion(int x, int y);

			/* Timer callbacks */
			static void timer(int timer_id);
			static void idle();

		/* Private member functions */
		private:
			/* Handle collisions between mview and mscene */
			static void collision();

		/* Public member variables */
		public:
			/* Redisplay timer */
			static const int TIMER_REDISPLAY{0};
			static const int TIMER_REDISPLAY_INTERVAL{16};

			/* Ability timer */
			static const int TIMER_BLINK{1};
			static const int TIMER_BLINK_INTERVAL{20*TIMER_REDISPLAY_INTERVAL};

			/* Update timer */
			static const int TIMER_UPDATE{2};
			static const int TIMER_UPDATE_INTERVAL{TIMER_REDISPLAY_INTERVAL/2};

			/* Bonus timer */
			static const int TIMER_RAVE{3};
			static const int TIMER_RAVE_INTERVAL{100*TIMER_REDISPLAY_INTERVAL};

		/* Private member variables */
		private:
			/* Window width and height */
			static int width_, height_;

			/* Delta x, y */
			static int dx_, dy_;

			/* Camera */
			static View mview;

			/* Scene */
			static Scene mscene;

			/* Model underneath player */
			static const Cube *mcube;
	}; /* class Hub */
	/* @} */

}; /* namespace eRG */
