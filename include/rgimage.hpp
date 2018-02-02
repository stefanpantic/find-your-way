#pragma once

#include <vector>
#include <string>
#include <GL/glut.h>

namespace eRG::util
{

	/*
	* NOTE: Code from poincare.matf.bg.ac.rs/~ivan/?content=rg
	*/
	/* @{ */
	extern "C"
	{
		typedef struct {
			unsigned short type;
			unsigned int size;
			unsigned short reserved1;
			unsigned short reserved2;
			unsigned int offsetbits;
		} BITMAPFILEHEADER;

		typedef struct {
			unsigned int size;
			unsigned int width;
			unsigned int height;
			unsigned short planes;
			unsigned short bitcount;
			unsigned int compression;
			unsigned int sizeimage;
			int xpelspermeter;
			int ypelspermeter;
			unsigned int colorsused;
			unsigned int colorsimportant;
		} BITMAPINFOHEADER;

		typedef struct Image {
			int width, height;
			char *pixels;
		} Image;

		Image *image_init(int width, int height);
		void image_done(Image *image);
		void image_read(Image *image, const char *filename);
	}
	/* @} */

	/* Generate textures */
	/* @{ */
	GLuint generate_texture(const std::string &path);
	std::vector<GLuint> generate_texture_array(const std::vector<std::string>& paths);
	/* @} */

}; /* namespace eRG::util */
