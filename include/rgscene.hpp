#pragma once

#include <vector>
#include <glm/vec3.hpp>
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
			explicit Scene();

			/* Get model */
			const Model* below(glm::vec3 pbox_lln, glm::vec3 pbox_urf) const;
			const Model* aabb(glm::vec3 pbox_lln, glm::vec3 pbox_urf) const;

			/* Read map from file */
			void read_map(std::string path);

			/* Render scene */
			void render() const;
		/* Private member variables */
		private:
			/* Model storage */
			std::vector<std::unique_ptr<Model>> models_;
	}; /* class eRG::Scene */
	/* @} */

}; /* namespace eRG */
