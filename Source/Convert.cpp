/*
  ==============================================================================

    Convert.cpp
    Created: 25 Mar 2023 5:55:12pm
    Author:  Admin

  ==============================================================================
*/

#include "Convert.h"

const float Convert::error = 1e-6f;

float Convert::toNormalizedGain(float value)
{
	return powf(10.0f, value / 20.0f);
}

float Convert::fromNormalizedGain(float value)
{
	return 20.0f * log10f(value);
}

float Convert::toNormalizedFreq(float value)
{
	return log10f(value / 20.0f) / 3.0f;
}

float Convert::fromNormalizedFreq(float value)
{
	return 20.0f * powf(10.0f, 3.0f * value);
}

float Convert::toNormalizedFilterGain(float value)
{
	return value / 24.0f + 0.5f;
}

float Convert::fromNormalizedFilterGain(float value)
{
	return 24.0f * (value - 0.5f);
}

float Convert::toNormalizedQuality(float value)
{
	return 0.5f * log10f(value) + 1.0f;
}

float Convert::fromNormalizedQuality(float value)
{
	return powf(10.0f, 2.0f * value - 1.0f);
}

