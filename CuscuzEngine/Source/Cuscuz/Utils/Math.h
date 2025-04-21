#pragma once

#include <cmath>
#include "glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/matrix_decompose.hpp>

namespace Cuscuz::Math
{
    constexpr float Pi = 3.1415926535f;
    constexpr float TwoPi = Pi * 2.0f;
    constexpr float PiOver2 = Pi / 2.0f;
    const float Infinity = std::numeric_limits<float>::infinity();
    const float NegInfinity = -std::numeric_limits<float>::infinity();

#define FLOAT_EQUAL(a, b) (std::fabs((a) - (b)) <= (glm::epsilon<float>()))

    inline float ToRadians(float degrees)
    {
        return degrees * Pi / 180.0f;
    }

    inline float ToDegrees(float radians)
    {
        return radians * 180.0f / Pi;
    }

    inline bool NearZero(float val)
    {
        if (fabs(val) <= glm::epsilon<float>())
        {
            return true;
        }
        return false;
    }

    template <typename T>
    T Max(const T& a, const T& b)
    {
        return (a < b ? b : a);
    }

    template <typename T>
    T Min(const T& a, const T& b)
    {
        return (a < b ? a : b);
    }

    template <typename T>
    T Clamp(const T& value, const T& lower, const T& upper)
    {
        return Min(upper, Max(lower, value));
    }

    inline float Abs(float value)
    {
        return fabs(value);
    }

    inline float Cos(float angle)
    {
        return cosf(angle);
    }

    inline float Sin(float angle)
    {
        return sinf(angle);
    }

    inline float Tan(float angle)
    {
        return tanf(angle);
    }

    inline float Acos(float value)
    {
        return acosf(value);
    }

    inline float Atan2(float y, float x)
    {
        return atan2f(y, x);
    }

    inline float Cot(float angle)
    {
        return 1.0f / Tan(angle);
    }

    inline float Lerp(float a, float b, float f)
    {
        return a + f * (b - a);
    }

    inline float Sqrt(float value)
    {
        return sqrtf(value);
    }

    inline float Fmod(float numer, float denom)
    {
        return fmod(numer, denom);
    }

    inline float LengthSq(float x, float y)
    {
        return x * x + y * y;
    }

    inline bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale)
	{
		// From glm::decompose in matrix_decompose.inl
		glm::mat4 LocalMatrix(transform);

		// Normalize the matrix.
		if (glm::epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), glm::epsilon<float>()))
			return false;

		// First, isolate perspective.  This is the messiest.
		if (glm::epsilonNotEqual(LocalMatrix[0][3], static_cast<float>(0), glm::epsilon<float>()) ||
			glm::epsilonNotEqual(LocalMatrix[1][3], static_cast<float>(0), glm::epsilon<float>()) ||
			glm::epsilonNotEqual(LocalMatrix[2][3], static_cast<float>(0), glm::epsilon<float>()))
		{
			// Clear the perspective partition
			LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<float>(0);
			LocalMatrix[3][3] = static_cast<float>(1);
		}

		// Next take care of translation (easy).
		translation = glm::vec3(LocalMatrix[3]);
		LocalMatrix[3] = glm::vec4(0, 0, 0, LocalMatrix[3].w);

		glm::vec3 Row[3];

		// Now get scale and shear.
		for (glm::length_t i = 0; i < 3; ++i)
			for (glm::length_t j = 0; j < 3; ++j)
				Row[i][j] = LocalMatrix[i][j];

		// Compute X scale factor and normalize first row.
		scale.x = length(Row[0]);
		Row[0] = glm::detail::scale(Row[0], static_cast<float>(1));
		scale.y = length(Row[1]);
		Row[1] = glm::detail::scale(Row[1], static_cast<float>(1));
		scale.z = length(Row[2]);
		Row[2] = glm::detail::scale(Row[2], static_cast<float>(1));

		rotation.y = asin(-Row[0][2]);
		if (cos(rotation.y) != 0)
		{
			rotation.x = atan2(Row[1][2], Row[2][2]);
			rotation.z = atan2(Row[0][1], Row[0][0]);
		}
		else
		{
			rotation.x = atan2(-Row[2][0], Row[1][1]);
			rotation.z = 0;
		}

		return true;
	}
}
