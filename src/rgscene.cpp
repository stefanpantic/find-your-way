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
	Scene::Scene(const std::string &source)
		:	models_{std::vector<std::unique_ptr<Model>>{}}
	{
		static_cast<void>(source);

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
	* TODO: Implement model position check.
	*/
	const Model* Scene::model_at(glm::vec3 pbox) const
	{
		for(decltype(auto) e : models_) {
			auto pos{e->position()};
			if(	pbox.x >= pos.first.x && pbox.x <= pos.second.x &&
				pbox.z >= pos.first.z && pbox.z <= pos.second.z) {
				return e.get();
			}
		}

		return nullptr;
	}

	/*
	* TODO: Implement AABB colision checking.
	*/
	const Model* Scene::aabb(glm::vec3 pbox) const
	{
		static_cast<void>(pbox);

		return nullptr;
	}
	/* @} */

	/* Render scene */
	/* @{ */
	/*
	* TODO: Implement scene rendering.
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
