#pragma once

namespace nc
{
	const float Tau = 6.28318530718f;		//360
	const float Pi = 3.14159265359f;			//180
	const float HalfPi = 1.57079632679f;		//
	const float QuarterPi = 0.78539816339f;

	inline float RadToDeg(float radians)
	{
		return radians * 180.0f / Pi;
	}

	inline float DegToRad(float degrees)
	{
		return degrees * Pi / 180.0f;
	}

	template<typename T>
	inline T Clamp(T val, T min, T max) {
		if (val > max) return max;
		if (val < min) return min;

		return val;
	}
	template<typename T>
	inline T Wraparound(T val, T min, T max)
	{
		if (val > max) return min;
		if (val < min) return max;

		return val;
	}

	template<typename T>
	inline T Lerp(T a, T b, float t)
	{
		t = Clamp(t, 0.0f, 1.0f);
		return a + ((b-a)*t);
	}
}