#pragma once

#include <random>

class Random
{
    std::mt19937 generator;
    
public:
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    static Random& Get()
    {
        static Random instance;
        return instance;
    }
    
    int GetRandomNumber(int min, int max) //inclusive
    {
        std::uniform_int_distribution distribution(min, max);
        return distribution(generator);
    }

    float GetRandomNumber(float min, float max) //inclusive
    {
        std::uniform_real_distribution distribution(min, max);
        return distribution(generator);
    }

private:
    Random() : generator(std::random_device{}()) { }
};

