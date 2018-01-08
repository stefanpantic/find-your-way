#pragma once

#include <vector>
#include <memory>

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
		/* Public member functions */
		public:
			/* Construction */
			explicit Scene(const std::string &source);

			/* Get model */
			const std::shared_ptr<Model>& model_at(float x, float z);

			/* Render scene */
			void render_scene();
		/* Private member variables */
		private:
			/* Model storage */
			std::vector<std::shared_ptr<Model>> models_;
	}; /* class eRG::Scene */
	/* @} */

}; /* namespace eRG */
