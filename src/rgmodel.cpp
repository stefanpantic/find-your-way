#include <iostream>
#include <GL/glut.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "rgimage.hpp"
#include "rgmodel.hpp"

namespace eRG
{

	/* Model implementation: */
	/* @@{ */
	/* Construction: */
	/* @{ */
	/*
	* @brief Builds %eRG::Model.
	*/
	Model::Model(	glm::vec3 lln,
					glm::vec3 urf,
					const std::vector<std::string> &paths)
		:	lln_{lln}, urf_{urf},
			dlist_{glGenLists(1)},
			handles_{eRG::util::generate_texture_array(paths)}
	{
		std::clog << "eRG::Model: Default constructor" << std::endl;
	}

	/*
	* @brief Copy constructor.
	*/
	Model::Model(const Model &other)
		:	lln_{other.lln_}, urf_{other.urf_},
			dlist_{other.dlist_},
			handles_{other.handles_}
	{
		std::clog << "eRG::Model: Copy constructor" << std::endl;
	}

	/*
	* @brief Move constructor.
	*/
	Model::Model(Model &&other)
		:	lln_{std::move(other.lln_)}, urf_{std::move(other.urf_)},
			dlist_{std::move(other.dlist_)},
			handles_{std::move(other.handles_)}
	{
		std::clog << "eRG::Model: Move constructor" << std::endl;
	}

	/* Initialize Model: */
	/* @{ */
	/*
	* @brief Initialy draw the model.
	*/
	void Model::initialize_model() const
	{
		std::vector<glm::vec3> vertices{glm::vec3{lln_.x, lln_.y, lln_.z},
										glm::vec3{lln_.x, lln_.y, urf_.z},
										glm::vec3{urf_.x, lln_.y, urf_.z},
										glm::vec3{urf_.x, lln_.y, lln_.z},
										glm::vec3{lln_.x, urf_.y, lln_.z},
										glm::vec3{lln_.x, urf_.y, urf_.z},
										glm::vec3{urf_.x, urf_.y, urf_.z},
										glm::vec3{urf_.x, urf_.y, lln_.z}};

		std::vector<int> 	side_indices{0, 1, 5, 4, 1, 2, 6, 5, 2, 3, 7, 6, 3, 0, 4, 7},
							bottom_indices{0, 1, 2, 3},
							top_indices{4, 5, 6, 7};
		std::vector<glm::vec2> tex_indices{{0, 0}, {1, 0}, {1, 1}, {0, 1}};

		/* Cube wrapper */
		glBindTexture(GL_TEXTURE_2D, handles_[0]);
			glBegin(GL_QUADS);
			for(size_t i = 0; i < side_indices.size(); ++i)
			{
				glNormal3f(	vertices[side_indices[i]].x,
							vertices[side_indices[i]].y,
							vertices[side_indices[i]].z);
				glTexCoord2f(10*tex_indices[i%4].s, 10*tex_indices[i%4].t);
				glVertex3f(	vertices[side_indices[i]].x,
							vertices[side_indices[i]].y,
							vertices[side_indices[i]].z);
			}
			glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);

		/* Cube top */
		glBindTexture(GL_TEXTURE_2D, handles_[1]);
			glBegin(GL_QUADS);
			for(size_t i = 0; i < top_indices.size(); ++i)
			{
				glNormal3f(	vertices[top_indices[i]].x,
							vertices[top_indices[i]].y,
							vertices[top_indices[i]].z);
				glTexCoord2f(4*tex_indices[i%4].x, 4*tex_indices[i%4].y);
				glVertex3f(	vertices[top_indices[i]].x,
							vertices[top_indices[i]].y,
							vertices[top_indices[i]].z);
			}
			glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);

		/* Cube bottom */
		glBindTexture(GL_TEXTURE_2D, handles_[2]);
			glBegin(GL_QUADS);
			for(size_t i = 0; i < bottom_indices.size(); ++i)
			{
				glNormal3f(	vertices[bottom_indices[i]].x,
							vertices[bottom_indices[i]].y,
							vertices[bottom_indices[i]].z);
				glTexCoord2f(2*tex_indices[i%4].x, 2*tex_indices[i%4].y);
				glVertex3f(	vertices[bottom_indices[i]].x,
							vertices[bottom_indices[i]].y,
							vertices[bottom_indices[i]].z);
			}
			glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	/* @} */

	/* Position: */
	/* @{ */
	/*
	* @brief Get model position as lower left near corner and upper far right corner coordinates.
	*/
	std::pair<glm::vec3, glm::vec3> Model::position() const
	{
		return {glm::vec3{Model::lln_}, glm::vec3{Model::urf_}};
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
