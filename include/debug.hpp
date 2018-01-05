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

	/*
	* @brief Draw cube of size %n in first octant.
	*/
	void first_octant(float n)
	{
		glPushMatrix();
			glColor3f(1, 1, 1);
			glTranslatef(n/2, n/2, n/2);
			glutWireCube(n);
		glPopMatrix();
	}

	/*
	* @brief Draw a floor.
	*/
	void floor(float size)
	{
		glBegin(GL_POLYGON);
			glColor3f(0.4, 0.4, 0.4);
			glVertex3f(size, 0, size);
			glVertex3f(size, 0, -size);
			glVertex3f(-size, 0, -size);
			glVertex3f(-size, 0, size);
		glEnd();
	
	}

}; /* namespace eRG::DEBUG */
