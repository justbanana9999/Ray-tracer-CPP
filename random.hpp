#pragma once

#include <random>

inline double random_number(std::mt19937 & generator) {
    std::uniform_real_distribution<double> distribution(-1,1);
    return distribution(generator);
}
