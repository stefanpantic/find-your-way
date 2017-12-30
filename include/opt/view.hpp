#pragma once

namespace eRG::opt
{

	/*
	* @brief Enum containing viewpoint movemement options.
	*/
	enum class View
	{
		/* Direction options */
		UP,
		DOWN,
		LEFT,
		RIGHT,

		/* Stop movement */
		STOP_VERTICAL,
		STOP_HORIZONTAL,
	}; /* enum class eRG::opt::View */

}; /* namespace eRG::opt */
