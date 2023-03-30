/*
  ==============================================================================

    Convert.h
    Created: 25 Mar 2023 5:55:12pm
    Author:  Admin

  ==============================================================================
*/

#pragma once
#include <iostream>
#include <cmath>



class Convert
{
private:
	static const float error;
public:
	// 将 enum class 转换为底层类型
	template<typename E>
	static constexpr auto toUType(E enumerator) noexcept
	{
		return static_cast<std::underlying_type_t<E>>(enumerator);
	}

	static float toNormalizedGain(float value);
	static float fromNormalizedGain(float value);

	static float toNormalizedFreq(float value);
	static float fromNormalizedFreq(float value);

	static float toNormalizedFilterGain(float value);
	static float fromNormalizedFilterGain(float value);

	static float toNormalizedQuality(float value);
	static float fromNormalizedQuality(float value);
};

