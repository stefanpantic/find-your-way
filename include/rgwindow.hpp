#pragma once

#include <iostream>
#include <GL/glut.h>

namespace eRG
{

	/* Window declaration: */
	/* @{ */
	/*
	* @brief Abstraction of OpenGL and GLUT window manipulation.
	*
	* @param RGHub Mainframe class containing callbacks for OpenGL and GLUT.
	*/
	template<class RGHub>
	class Window
	{
		/* Public member functions */
		public:
			/* Construction */
			Window(	int &argc, char **argv, int display_mode,
					size_t width = 100, size_t height = 100,
					size_t x = 100, size_t y = 100);

			/* Show window */
			void show();
	}; /* class eRG::Window */
	/* @} */

	/* Window implementation: */
	/* @@{ */
	/* Construction: */
	/* @{ */
	/*
	* @brief Builds instance of %Window.
	*/
	template<class RGHub>
	Window<RGHub>::Window(	int &argc, char **argv, int display_mode,
							size_t width, size_t height,
							size_t x, size_t y)
	{
		/* Check command line arguments */
		if(argc < 5) {
			throw std::runtime_error{"Invalid command line arguments..."};
		}

		/* Initialize GLUT */
		glutInit(&argc, argv);
		glutInitDisplayMode(display_mode);
		glutInitWindowSize(width, height);
		glutInitWindowPosition(x, y);
		glutCreateWindow(argv[0] + 2);

		/* Initialize %RGHub */
		RGHub::initialize(argc, argv);

		/* Display callbacks */
		glutDisplayFunc(RGHub::display);
		glutReshapeFunc(RGHub::reshape);

		/* Keyboard callbacks */
		glutKeyboardFunc(RGHub::keyboard);
		glutKeyboardUpFunc(RGHub::keyboard_up);
		glutSpecialFunc(RGHub::special);
		glutSpecialUpFunc(RGHub::special_up);

		/* Mouse callbacks */
		glutMouseFunc(RGHub::mouse);
		glutMotionFunc(RGHub::motion);
		glutPassiveMotionFunc(RGHub::passive_motion);

		/* Timer registration */
		glutTimerFunc(RGHub::TIMER_REDISPLAY_INTERVAL, RGHub::timer, RGHub::TIMER_REDISPLAY);
		glutIdleFunc(RGHub::idle);
	}
	/* @} */

	/* Show window: */
	/* @{ */
	/*
	* @brief Enter the 'Game loop'.
	*/
	template<class RGHub>
	void Window<RGHub>::show()
	{
		/* Start GLUT Main Loop */
		glutMainLoop();
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
