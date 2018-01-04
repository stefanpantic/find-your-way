#pragma once

namespace eRG::util
{

	/* Constant expression for PI */
	constexpr float pi{3.14159265359};

	/*
	* @brief Typesafe signum function.
	*
	* @param T NumericType type.
	*/
	template<typename T>
	constexpr int sgn(T val)
	{
		return (T(0) < val) - (T(0) > val);
	}

}; /* namespace eRG::util */


