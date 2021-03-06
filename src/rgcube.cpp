#include <iostream>
#include <GL/glut.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "rgcube.hpp"
#include "rgimage.hpp"
#include "rgdefines.hpp"

namespace eRG
{

	/* Cube implementation: */
	/* @@{ */
	/* Static member initialization */
	const std::vector<std::vector<int>> Cube::indices_{	{0, 1, 5, 4, 1, 2, 6, 5, 2, 3, 7, 6, 3, 0, 4, 7},
														{0, 1, 2, 3},
														{4, 5, 6, 7}};
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
			handles_{eRG::util::generate_texture_array(paths)},
			tex_{eRG::util::texture_coords(vertices_[0], vertices_[1], vertices_[3], vertices_[4])},
			use_tex_{(handles_.size() >= 3) ? true : false}
	{ std::clog << "eRG::Cube: Default constructor" << std::endl; }

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
		return {lln_, urf_};
	}
	/* @} */

	/* Get delta: */
	/* @{ */
	/*
	* @brief Get movement delta.
	*/
	glm::vec3 Cube::delta() const
	{
		return glm::vec3(0);
	}
	/* @} */

	/* Draw model: */
	/* @{ */
	/*
	* @brief Draw the model.
	*/
	void Cube::draw() const
	{
		/* Cube center point */
		auto center_{(urf_ + lln_)/2.0f};

		/* Draw cube */
		for(int k = 0; k < 3; ++k)
		{
			if(use_tex_) {
				glBindTexture(GL_TEXTURE_2D, handles_[k]);
			}
				glBegin(GL_QUADS);
				for(size_t i = 0; i < indices_[k].size(); ++i)
				{
					glNormal3f(	vertices_[indices_[k][i]].x - center_.x,
								vertices_[indices_[k][i]].y - center_.y,
								vertices_[indices_[k][i]].z - center_.z);

					if(use_tex_) {
						glTexCoord2f(tex_[(i/4)%2 + 2*util::sgn(k)][i%4].s/3, tex_[(i/4)%2 + 2*util::sgn(k)][i%4].t/3);
					}

					glVertex3f(	vertices_[indices_[k][i]].x,
								vertices_[indices_[k][i]].y,
								vertices_[indices_[k][i]].z);
				}
				glEnd();
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	/* @} */

	/* Update position: */
	/*
	* @brief Update model state.
	*/
	/* @{ */
	void Cube::update()
	{}
	/* @} */
	/* @@} */

}; /* namespace eRG */
