#pragma once

#include <vector>
#include <memory>
#include <glm/vec3.hpp>

namespace eRG
{

	/* Forward declaration: */
	class Cube;

	/* Scene declaration: */
	/* @{ */
	/*
	* @brief Class used for creating, handling and manipulating the virtual world.
	*/
	class Scene
	{
		/* Convenience */
		using Box = std::pair<glm::vec3, glm::vec3>;

		/* Public member functions */
		public:
			/* Get model */
			const Cube* below(Box pbox) const;
			std::vector<const Cube*> aabb(Box pbox) const;

			/* Read map from file */
			void read_map(std::string path);

			/* Set textures */
			void set_textures(std::vector<std::string> path);

			/* Update scene */
			void update();

			/* Render scene */
			void render() const;

		/* Private member variables */
		private:
			/* Cube storage */
			std::vector<std::unique_ptr<Cube>> models_;

			/* Texture paths */
			std::vector<std::string> textures_;
	}; /* class eRG::Scene */
	/* @} */

}; /* namespace eRG */
