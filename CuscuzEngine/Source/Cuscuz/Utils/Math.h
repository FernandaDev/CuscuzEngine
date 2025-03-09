#pragma once

#include <cmath>
#include "glm.hpp"

namespace Cuscuz
{
    namespace Math
    {
        constexpr float Pi = 3.1415926535f;
        constexpr float TwoPi = Pi * 2.0f;
        constexpr float PiOver2 = Pi / 2.0f;
        const float Infinity = std::numeric_limits<float>::infinity();
        const float NegInfinity = -std::numeric_limits<float>::infinity();
        constexpr float epsilon = 1e-6f;

#define FLOAT_EQUAL(a, b) (std::fabs((a) - (b)) <= (Cuscuz::Math::epsilon))

        inline float ToRadians(float degrees)
        {
            return degrees * Pi / 180.0f;
        }

        inline float ToDegrees(float radians)
        {
            return radians * 180.0f / Pi;
        }

        inline bool NearZero(float val, float epsilon = 0.001f)
        {
            if (fabs(val) <= epsilon)
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

        // static void PrintMatrix(const glm::mat4& matrix)
        // {
        //     for (int row = 0; row < 4; ++row)
        //     {
        //         for (int col = 0; col < 4; ++col)
        //         {
        //             std::cout << matrix[row][col] << " ";
        //         }
        //         std::cout << std::endl;
        //     }
        // }
    }
}