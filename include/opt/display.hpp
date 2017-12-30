#pragma once

namespace eRG::opt
{

	/*
	* @brief Enum class for display mode options.
	*/
	enum class Display
	{
		/* Display modes */
		RGBA,
		RGB,
		INDEX,
		SINGLE,
		DOUBLE,
		ACCUM,
		ALPHA,
		DEPTH,
		STENCIL,
		MULTISAMPLE,
		STEREO,
		LUMINANCE,
	}; /* enum class Display */

}; /* namespace eRG::opt */
