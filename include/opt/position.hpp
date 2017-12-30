#pragma once

namespace eRG::opt
{

	/*
	* @brief Enum containing eye point movement options.
	*/
	enum class Position
	{
		/* Direction options */
		UP,
		DOWN,
		LEFT,
		RIGHT,

		/* Stop movement */
		STOP_FORWARD,
		STOP_SIDEWAYS,
	}; /* enum class eRG::opt::Position */

}; /* namespace eRG::opt */
