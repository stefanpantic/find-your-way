#include <sstream>
#include <cmath>
#include <GL/glut.h>
#include "rgpmodel.hpp"
#include "rgscene.hpp"

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
		for(float i = 0; i < 10; ++i) {
			for(float j = 0; j < 10; ++j) {
				models_.push_back(std::shared_ptr<Model>{new PModel{glm::vec3{i, std::sin(i) - 1, j}, glm::vec3{i + 1, std::sin(i), j + 1}}});
			}
		}
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
		static std::shared_ptr<Model> abyss{new PModel{glm::vec3{0, 0, 0}, glm::vec3{0, -100, 0}}};

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
