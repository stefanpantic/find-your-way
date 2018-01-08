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
		models_.resize(100);
		for(int i = 0; i < 100; ++i) {
			models_[i] = std::shared_ptr<Model>{new PModel{glm::vec3{i, 0.5, i}, glm::vec3{i, 0.5, i}}};
		}
		/* @} */
	}
	/* @} */

	/* Get model: */
	/* @{ */
	/*
	* TODO: Implement model position check.
	*/
	const std::shared_ptr<Model>& Scene::model_at(float x, float z)
	{
		static_cast<void>(x);
		static_cast<void>(z);

		/* Just to supress a warning */
		return models_[x];
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
			glPushMatrix();
				e->draw();
			glPopMatrix();
		}
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
