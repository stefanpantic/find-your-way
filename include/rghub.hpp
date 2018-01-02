#pragma once

#include <GL/glut.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "rgview.hpp"

namespace eRG
{

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
			static void initialize();

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

		/* Public member variables */
		public:
			static const int TIMER0{0};
			static const int TIMER0_INTERVAL{16};

		/* Private member variables */
		private:
			/* Window width and height */
			static int width_, height_;

			/* Delta x, y */
			static int d_x_, d_y_;

			/* Camera */
			static View mview;
	}; /* class Hub */
	/* @} */

}; /* namespace eRG */
