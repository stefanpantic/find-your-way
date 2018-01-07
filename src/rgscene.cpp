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
		:	scene_{Scene::wmap{}}
	{
		static_cast<void>(source);

		/* Scene test: */
		/* @{ */
		scene_.resize(25);
		for(auto &e: scene_) {
			e.resize(25);
		}

		for(float i = 0; i < 25; ++i) {
			for(float j = 0; j < 25; ++j) {
				scene_[i][j] = std::shared_ptr<Model>{new PModel{glm::vec3{i + 0.5, std::sin(i*j/5), j + 0.5}}};
			}
		}
		/* @} */
	}
	/* @} */

	/* Get model: */
	/* @{ */
	/*
	* @brief Get model with (x,y) coordinates.
	*/
	std::shared_ptr<Model>& Scene::model_at(int x, int y)
	{
		return scene_[x][y];
	}
	/* @} */

	/* Render scene */
	/* @{ */
	/*
	* TODO: Implement scene rendering.
	*/
	void Scene::render_scene()
	{
		for(auto &row : scene_) {
			for(auto &e : row) {
				e->draw();
			}
		}
	}
	/* @} */
	/* @@} */

}; /* namespace eRG */
