#include <iostream>
#include "rgwindow.hpp"
#include "rghub.hpp"

int
main(int argc, char **argv)
{
	eRG::Window<eRG::Hub> w(argc, argv, GLUT_DOUBLE |
										GLUT_RGBA |
										GLUT_DEPTH);
	w.show();
	return 0;
}
