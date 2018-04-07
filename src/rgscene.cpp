#include <fstream>
#include <sstream>
#include <algorithm>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include "external/nlohmann/json.hpp"
#include "rgscene.hpp"
#include "rgcube.hpp"
#include "rgacube.hpp"

namespace eRG
{

	/* Scene implementation: */
	/* @@{ */
	/* Get model: */
	/* @{ */
	/*
	* @brief Returns model underneath the player.
	*/
	const Cube* Scene::below(Box pbox) const
	{
		auto bpoint{((pbox.second + pbox.first)/2.0f)};

		for(const auto &e : models_)
		{
			/* Get the model box */
			auto model{e->position()};

			/* The boxes intersect on the X plane */
			bool xintersect{bpoint.x >= model.first.x - 1 && bpoint.x <= model.second.x + 1};

			/* The boxes intersect on the Y plane */
			bool yintersect{bpoint.y >= model.second.y};

			/* The boxes intersect on the Z plane */
			bool zintersect{bpoint.z >= model.first.z - 1 && bpoint.z <= model.second.z + 1};

			/* If all conditions are met return the model */
			if(	xintersect && zintersect && yintersect) {
				return e.get();
			}
		}

		/* There isn't a model underneath the player */
		return nullptr;
	}

	/*
	* @brief Collision detection using AABB.
	*/
	std::vector<const Cube*> Scene::aabb(Box pbox) const
	{
		/* Colided models */
		std::vector<const Cube*> colided;

		for(const auto &e : models_)
		{
			/* Get the model box */
			auto model{e->position()};

			/* The boxes intersect on the X plane */
			bool xintersect{(pbox.first.x <= model.first.x && model.first.x <= pbox.second.x) ||
							(model.first.x <= pbox.first.x && pbox.first.x <= model.second.x)};

			/* The boxes intersect on the Y plane */
			bool yintersect{(pbox.first.y <= model.first.y && model.first.y <= pbox.second.y) ||
							(model.first.y <= pbox.first.y && pbox.first.y <= model.second.y)};

			/* The boxes intersect on the Z plane */
			bool zintersect{(pbox.first.z <= model.first.z && model.first.z <= pbox.second.z) ||
							(model.first.z <= pbox.first.z && pbox.first.z <= model.second.z)};

			/* If the boxes intersect on all axis, a collision has occured */
			if(xintersect && yintersect && zintersect) {
				colided.push_back(e.get());
			}
		}

		/* Collisions */
		return colided;
	}
	/* @} */

	/* Read map: */
	/* @{ */
	/*
	* @brief Read map from passed file.
	*/
	void Scene::read_map(std::string path)
	{
		/* Try to construct the JSON file tree and traverse it*/
		try
		{
			/* Construct the JSON file tree */
			/* NOTE: the use of '=' here is intentional */
			nlohmann::json tree = nlohmann::json::parse(std::ifstream(path));

			/* Start traversal from root */
			for(const auto &scene : tree.at("scene"))
			{
				for(const auto &e : scene)
				{
					/* Get the corner points */
					glm::vec3 lln{e.at("x1"), e.at("y1"), e.at("z1")};
					glm::vec3 urf{e.at("x2"), e.at("y2"), e.at("z2")};

					/* Movement points */
					std::vector<glm::vec3> movement;

					/* If there are movement points place them in a vector */
					if(e.end() != e.find("movement")) {
						for(const auto &tripple : e.at("movement")) {
							movement.push_back(glm::vec3{tripple[0], tripple[1], tripple[2]});
						}
					}

					if(0 != movement.size()) { /* There are movement points, construct a movinc cube */
						models_.push_back(std::make_unique<ACube>(	std::move(lln), std::move(urf),
																	std::move(movement),
																	textures_));
					} else { /* There are no movement points, construct a stationary cube */
						models_.push_back(std::make_unique<Cube>(	std::move(lln), std::move(urf),
																	textures_));
					}
				}
			}

		} catch (const std::exception &e) {
			/* Tree construction failed */
			std::cerr << "\x1b[31mTree construction failed: " << e.what() << "\x1b[0m" << std::endl;
			std::exit(1);
		}

		/* Sort all models by y coordinate descending */
		std::sort(	models_.begin(), models_.end(),
					[] (const auto &lhs, const auto &rhs) { return lhs->position().second.y > rhs->position().second.y; });
	}
	/* @} */

	/* Set textures */
	/* @{ */
	/*
	* @brief Set texture paths.
	*/
	void Scene::set_textures(std::vector<std::string> paths)
	{
		if(3 == paths.size()) {
			textures_ = std::move(paths);
		}
	}
	/* @} */

	/* Update scene */
	/* @{ */
	/*
	* @brief Updates all stored models.
	*/
	void Scene::update()
	{
		for(const auto &e : models_) {
			e->update();
		}
	}
	/* @} */

	/* Render scene */
	/* @{ */
	/*
	* @brief Draws all stored models.
	*/
	void Scene::render() const
	{
		/* N. M. is the Zodiac Killer */
		for(const auto &e : models_) {
			e->draw();
		}
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
