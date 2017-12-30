#pragma once

#include <memory>
#include <GL/glut.h>

namespace eRG
{

	/* Window declaration : */
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
		/* Private member variables */
		private:
			/* Unique pointer to RGHub */
			std::unique_ptr<RGHub> mframe_;
	}; /* class Window */
	/* @} */

	/* Window implementation: */
	/* @@{ */
	/* Construction: */
	/* @{ */
	/*
	* @brief Builds instance of Window.
	*/
	template<class RGHub>
	Window<RGHub>::Window(	int &argc, char **argv, int display_mode,
							size_t width, size_t height,
							size_t x, size_t y)
		:	mframe_{new RGHub}
	{
		/* Initialize GLUT */
		glutInit(&argc, argv);
		glutInitDisplayMode(display_mode);
		glutInitWindowSize(width, height);
		glutInitWindowPosition(x, y);
		glutCreateWindow(argv[0] + 2);

		/* Initialize %mframe_ */
		mframe_->initialize();

		/* Display callbacks */
		glutDisplayFunc(mframe_->display);
		glutReshapeFunc(mframe_->reshape);

		/* Keyboard callbacks */
		glutKeyboardFunc(mframe_->keyboard);
		glutKeyboardUpFunc(mframe_->keyboard_up);
		glutSpecialFunc(mframe_->special);
		glutSpecialUpFunc(mframe_->special_up);

		///* Mouse callbacks */
		//glutMouseFunc(mframe_->mouse);
		//glutMotionFunc(mframe_->motion);
		//glutPassiveMotionFunc(mframe_->passive_motion);

		///* Timer registration */
		glutTimerFunc(mframe_->TIMER0_INTERVAL, mframe_->timer, mframe_->TIMER0);
		//glutIdleFunc(mframe_->idle);

		/*
		*	glutButtonBoxFunc(*mframe_->button_box);
		*	glutDialsFunc(*mframe_->dials);
		*	glutEntryFunc(*mframe_->entry);
		*	glutMenuStatusFunc(*mframe_->menu_status);
		*	glutSpaceballButtonFunc(*mframe_->spaceball_button);
		*	glutSpaceballMotionFunc(*mframe_->spaceball_motion);
		*	glutSpaceballRotateFunc(*mframe_->spaceball_rotate);
		*	glutTabletButtonFunc(*mframe_->tablet_button);
		*	glutTabletMotionFunc(*mframe_->tablet_motion);
		*	glutVisibilityFunc(*mframe_->visibility);
		*/
	}
	/* @} */

	/* Show window: */
	/* @{ */
	/*
	* @brief Show window.
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
