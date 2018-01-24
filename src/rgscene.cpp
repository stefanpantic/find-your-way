#include <fstream>
#include <sstream>
#include <algorithm>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <GL/glut.h>
#include <glm/vec3.hpp>
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
		std::clog << "eRG::Scene: Default constructor" << std::endl;
	}
	/* @} */

	/* Get model: */
	/* @{ */
	/*
	* @brief Returns model underneath the player.
	*/
	const Model* Scene::below(Box pbox) const
	{
		auto bpoint{((pbox.second + pbox.first)/2.0f)};

		for(auto &&e : models_)
		{
			/* Get the model box */
			auto model{e->position()};

			/* The boxes intersect on the X plane */
			bool xintersect{bpoint.x >= model.first.x && bpoint.x <= model.second.x};

			/* The boxes intersect on the Y plane */
			bool yintersect{bpoint.y >= model.second.y};

			/* The boxes intersect on the Z plane */
			bool zintersect{bpoint.z >= model.first.z && bpoint.z <= model.second.z};

			/* If all conditions are met return the model */
			if(	xintersect && zintersect && yintersect) {
				return e.get();
			}
		}

		/* There isn't a model underneath the player */
		return nullptr;
	}

	/*
	* @brief Colision detection using AABB.
	*/
	const Model* Scene::aabb(Box pbox) const
	{
		for(auto &&e : models_)
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
		/* Try to contruuct the property tree and traverse it*/
		try
		{
			boost::property_tree::ptree root;
			boost::property_tree::read_json(path, root);

			traverse_ptree(root);
		} catch (const std::exception &e) {
			std::cerr << e.what() << std::endl;
		}

		/* Sort all models by y coordinate descending */
		std::sort(	models_.begin(), models_.end(),
					[] (auto &&lhs, auto &&rhs) { return lhs->position().second.y > rhs->position().second.y; });
	}
	/* @} */

	/* Traverse property tree */
	/* @{ */
	/*
	* @brief Traverse property tree constructed by boost JSON parser.
	*/
	void Scene::traverse_ptree(const boost::property_tree::ptree &root)
	{
		/* If the tree is empty we don't go any further */
		if(root.empty()) {
			return;
		}

		/* Iterate through the entire tree */
		for(auto &&e : root)
		{
			if("pmodel" == e.first) { /* PModel node */

				/* Get all the boxes from the node */
				for(auto &&e1 : e.second)
				{
					int i{0};
					std::array<float, 6> tmp;
					for(auto &&e2 : e1.second) {
						tmp[i++] = std::stof(e2.second.data());
					}

					/* Create the model */
					models_.push_back(std::unique_ptr<Model>{	new PModel{	glm::vec3{tmp[0], tmp[1], tmp[2]},
																			glm::vec3{tmp[3], tmp[4], tmp[5]}}});
				}
			} else if("amodel" == e.first) { /* AModel node */

				/* Get all the boxes and movement points from the node */
				for(auto &&e1 : e.second)
				{
					std::vector<float> tmp;
					for(auto &&e2: e1.second) {
						if("" != e2.second.data()) {
							tmp.push_back(std::stof(e2.second.data()));
						} else {
							for(auto &&e3 : e2.second) {
								for(auto &&e4 : e3.second) {
									tmp.push_back(std::stof(e4.second.data()));
								}
							}
						}
					}

					/* Get the movement points */
					std::vector<glm::vec3> tmp1;
					for(auto &&it = tmp.begin() + 6; it < tmp.end(); it += 3) {
						tmp1.push_back(glm::vec3{*it, *(it + 1), *(it + 2)});
					}

					/* Create the model */
					models_.push_back(std::unique_ptr<Model>{	new AModel{	glm::vec3{tmp[0], tmp[1], tmp[2]},
																			glm::vec3{tmp[3], tmp[4], tmp[5]},
																			std::move(tmp1)}});
				}
			} else { /* Go with the flow */
				traverse_ptree(e.second);
			}
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
		for(auto &e : models_) {
			e->draw();
		}
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
