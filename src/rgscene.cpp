#include <fstream>
#include <sstream>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "rgscene.hpp"
#include "rgpmodel.hpp"
#include "rgamodel.hpp"

namespace eRG
{

	/* Scene implementation: */
	/* @@{ */
	/* Construction: */
	/* @{ */
	/*
	* TODO: Implement scene constructor.
	*/
	Scene::Scene()
		:	models_{std::vector<std::unique_ptr<Model>>{}}
	{
		/* Scene test: */
		/* @{ */
		models_.push_back(std::unique_ptr<Model>{new AModel{glm::vec3{0, -1, 0},
															glm::vec3{2, 0, 2},
															std::vector<glm::vec3>{	glm::vec3{1, 0.5, 1},
																					glm::vec3{1, 10.5, 1}}}});
		models_.push_back(std::unique_ptr<Model>{new PModel{glm::vec3{-5, -1, -5},
															glm::vec3{0, 0, 0}}});
		models_.push_back(std::unique_ptr<Model>{new PModel{glm::vec3{9, -1, 9},
															glm::vec3{10, 0, 10}}});
		/* @} */
	}
	/* @} */

	/* Get model: */
	/* @{ */
	/*
	* @brief Returns model underneath the player.
	*/
	const Model* Scene::model_at(glm::vec3 pbox) const
	{
		for(decltype(auto) e : models_)
		{
			/* Get the model box */
			auto model{e->position()};

			/* Get intersections */
			bool 	xintersect{pbox.x >= model.first.x && pbox.x <= model.second.x},
					zintersect{pbox.z >= model.first.z && pbox.z <= model.second.z},
					yintersect{pbox.y < model.second.y};

			/* If all conditions are met return the model */
			if(	xintersect && zintersect && !yintersect) {
				return e.get();
			}
		}

		/* There isn't a model underneath the player */
		return nullptr;
	}

	/*
	* @brief Colision detection using AABB.
	*/
	const Model* Scene::aabb(glm::vec3 pbox) const
	{
		/* Get the player box */
		glm::vec3 pbox_lln{pbox - glm::vec3{1, 2, 1}};
		glm::vec3 pbox_urf{pbox + glm::vec3{1, 0, 1}};

		for(decltype(auto) e : models_)
		{
			/* Get the model box */
			auto model{e->position()};

			/* The boxes intersect on the X plane */
			bool xintersect{(pbox_lln.x <= model.first.x && model.first.x <= pbox_urf.x) ||
							(model.first.x <= pbox_lln.x && pbox_lln.x <= model.second.x)};

			/* The boxes intersect on the Y plane */
			bool yintersect{(pbox_lln.y <= model.first.y && model.first.y <= pbox_urf.y) ||
							(model.first.y <= pbox_lln.y && pbox_lln.y <= model.second.y)};

			/* The boxes intersect on the Z plane */
			bool zintersect{(pbox_lln.z <= model.first.z && model.first.z <= pbox_urf.z) ||
							(model.first.z <= pbox_lln.z && pbox_lln.z <= model.second.z)};

			/* If the boxes intersect on all axis, a colision has occured */
			if(xintersect && yintersect && zintersect) {
				return e.get();
			}
		}

		/* A colision hasn't occured */
		return nullptr;
	}
	/* @} */

	/* Read map: */
	/* @{ */
	/*
	* @brief Read map from passed file.
	*/
	void Scene::read_map(std::string path)
	{
		static_cast<void>(path);
	}
	/* @} */

	/* Render scene */
	/* @{ */
	/*
	* @brief Draws all stored models.
	*/
	void Scene::render() const
	{
		for(auto &e : models_) {
			e->draw();
		}
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
