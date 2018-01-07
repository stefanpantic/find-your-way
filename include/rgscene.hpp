#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <glm/vec4.hpp>

namespace eRG
{

	/* Forward declaration of eRG::Model */
	class Model;

	/* Scene declaration: */
	/* @{ */
	/*
	* @brief Class used for creating, handling and manipulating the virtual world.
	*/
	class Scene
	{
		/* Convenience */
		using wmap = std::vector<std::vector<std::shared_ptr<Model>>>;

		/* Public member functions */
		public:
			/* Construction */
			explicit Scene(const std::string &source);

			/* Get model */
			std::shared_ptr<Model>& model_at(int x, int y);

			/* Render scene */
			void render_scene();
		/* Private member variables */
		private:
			/* Main scene */
			wmap scene_;
	}; /* class eRG::Scene */
	/* @} */

}; /* namespace eRG */
