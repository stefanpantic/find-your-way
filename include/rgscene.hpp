#pragma once

#include <vector>
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <glm/vec3.hpp>

namespace eRG
{

	/* Forward declaration of eRG::Cube */
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
			/* Construction */
			explicit Scene();

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

		/* Private member functions */
		private:
			/* Traverse property tree */
			void traverse_ptree(const boost::property_tree::ptree &root);

		/* Private member variables */
		private:
			/* Cube storage */
			std::vector<std::unique_ptr<Cube>> models_;

			/* Texture paths */
			std::vector<std::string> textures_;
	}; /* class eRG::Scene */
	/* @} */

}; /* namespace eRG */
