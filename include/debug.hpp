#pragma once

#include <GL/glut.h>

/*
* @brief Temporary header only file with some handy debugging functions.
*
* NOTE: Will be deleted.
*/
namespace eRG::DEBUG
{

	/*
	* @brief Draw the coordinate system.
	*/
	void coordinate_system()
	{
		glBegin(GL_LINES);
			/* X axis */
			glColor3f(1, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(1, 0, 0);

			/* Y axis */
			glColor3f(0, 1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 1, 0);

			/* Z axis */
			glColor3f(0, 0, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 1);
		glEnd();
	}

}; /* namespace eRG::DEBUG */
