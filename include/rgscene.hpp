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
			explicit Scene(const std::string &source);

			/* Get model */
			const Model* model_at(glm::vec3 pbox) const;
			const Model* aabb(glm::vec3 pbox) const;

			/* Render scene */
			void render() const;
		/* Private member variables */
		private:
			/* Model storage */
			std::vector<std::unique_ptr<Model>> models_;
	}; /* class eRG::Scene */
	/* @} */

}; /* namespace eRG */
