#include <sstream>
#include <cmath>
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
		:	models_{std::vector<std::shared_ptr<Model>>{}}
	{
		static_cast<void>(source);

		/* Scene test: */
		/* @{ */
		models_.push_back(std::shared_ptr<Model>{new AModel{glm::vec3{0, -1, 0},
															glm::vec3{1, 0, 1},
															std::vector<glm::vec3>{	glm::vec3{0.5, -0.5, 0.5},
																					glm::vec3{5.5, -0.5, 5.5},
																					glm::vec3{5.5, -0.5, 0.0}}
															}});
		models_.push_back(std::shared_ptr<Model>{new PModel{glm::vec3{-1, -1, -1},
															glm::vec3{0, 0, 0}}});
		/* @} */
	}
	/* @} */

	/* Get model: */
	/* @{ */
	/*
	* TODO: Implement model position check.
	*/
	std::shared_ptr<Model>& Scene::model_at(float x, float z)
	{
		static std::shared_ptr<Model> abyss{new AModel{glm::vec3{0, 0, 0}, glm::vec3{0, -100, 0}}};

		for(auto &e : models_) {
			auto pos{e->position()};
			if(x >= pos.first.x && x <= pos.second.x && z >= pos.first.z && z <= pos.second.z) {
				return e;
			}
		}

		return abyss;
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
