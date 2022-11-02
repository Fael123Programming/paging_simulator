#include <random>
#include "../include/RandomNumberGenerator.hpp"

int RandomNumberGenerator::generateBetween(int min, int max) {
    std::random_device rd;
    std::uniform_int_distribution<int> uid(min, max);
    return uid(rd);
}
