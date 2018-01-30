#include <iostream>
#include <GL/glut.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "rgimage.hpp"
#include "rgcube.hpp"

namespace eRG
{

	/* Cube implementation: */
	/* @@{ */
	/* Static member initialization */
	const std::vector<std::vector<int>> Cube::indices_{{0, 1, 5, 4, 1, 2, 6, 5, 2, 3, 7, 6, 3, 0, 4, 7},
														{0, 1, 2, 3},
														{4, 5, 6, 7}};
	const std::vector<glm::vec2> Cube::tex_{{0, 0}, {1, 0}, {1, 1}, {0, 1}};
	/* Construction: */
	/* @{ */
	/*
	* @brief Builds %eRG::Cube.
	*/
	Cube::Cube(	glm::vec3 lln,
					glm::vec3 urf,
					const std::vector<std::string> &paths)
		:	lln_{lln}, urf_{urf},
			vertices_{	{lln_.x, lln_.y, lln_.z},
						{lln_.x, lln_.y, urf_.z},
						{urf_.x, lln_.y, urf_.z},
						{urf_.x, lln_.y, lln_.z},
						{lln_.x, urf_.y, lln_.z},
						{lln_.x, urf_.y, urf_.z},
						{urf_.x, urf_.y, urf_.z},
						{urf_.x, urf_.y, lln_.z}},
			handles_{eRG::util::generate_texture_array(paths)}
	{
		std::clog << "eRG::Cube: Default constructor" << std::endl;
	}

	/*
	* @brief Copy constructor.
	*/
	Cube::Cube(const Cube &other)
		:	lln_{other.lln_}, urf_{other.urf_},
			vertices_{other.vertices_},
			handles_{other.handles_}
	{
		std::clog << "eRG::Cube: Copy constructor" << std::endl;
	}

	/*
	* @brief Move constructor.
	*/
	Cube::Cube(Cube &&other)
		:	lln_{std::move(other.lln_)}, urf_{std::move(other.urf_)},
			vertices_{std::move(other.vertices_)},
			handles_{std::move(other.handles_)}
	{
		std::clog << "eRG::Cube: Move constructor" << std::endl;
	}

	/*
	* @brief Destructor.
	*/
	Cube::~Cube()
	{
		glDeleteTextures(handles_.size(), handles_.data());
	}
	/* @} */

	/* Position: */
	/* @{ */
	/*
	* @brief Get model position as lower left near corner and upper far right corner coordinates.
	*/
	std::pair<glm::vec3, glm::vec3> Cube::position() const
	{
		return {glm::vec3{Cube::lln_}, glm::vec3{Cube::urf_}};
	}
	/* @} */

	/* Draw model: */
	/* @{ */
	/*
	* @brief Draw the model.
	*/
	void Cube::draw()
	{
		/* Cube center point */
		auto center_{(urf_ + lln_)/2.0f};

		/* Draw cube */
		for(int k = 0; k < 3; ++k)
		{
			glBindTexture(GL_TEXTURE_2D, handles_[k]);
				glBegin(GL_QUADS);
				for(size_t i = 0; i < indices_[k].size(); ++i)
				{
					glNormal3f(	vertices_[indices_[k][i]].x - center_.x,
								vertices_[indices_[k][i]].y - center_.y,
								vertices_[indices_[k][i]].z - center_.z);
					glTexCoord2f(10*tex_[i%4].s, 10*tex_[i%4].t);
					glVertex3f(	vertices_[indices_[k][i]].x,
								vertices_[indices_[k][i]].y,
								vertices_[indices_[k][i]].z);
				}
				glEnd();
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */