#include <sstream>
#include <GL/glut.h>
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
	Scene::Scene(const std::string &source)
		:	models_{std::vector<std::unique_ptr<Model>>{}}
	{
		static_cast<void>(source);

		/* Scene test: */
		/* @{ */
		models_.push_back(std::unique_ptr<Model>{new AModel{glm::vec3{0, -1, 0},
															glm::vec3{2, 0, 2},
															std::vector<glm::vec3>{	glm::vec3{0.5, -0.5, 0.5},
																					glm::vec3{8.5, -0.5, 8.5}}}});
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
	* TODO: Implement model position check.
	*/
	const Model* Scene::model_at(glm::vec3 player)
	{
		for(auto &e : models_) {
			auto pos{e->position()};
			if(	player.x >= pos.first.x && player.x <= pos.second.x &&
				player.z >= pos.first.z && player.z <= pos.second.z) {
				return e.get();
			}
		}

		return nullptr;
	}
	/* @} */

	/* Render scene */
	/* @{ */
	/*
	* TODO: Implement scene rendering.
	*/
	void Scene::render_scene()
	{
		for(auto &e : models_) {
			e->draw();
		}
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
