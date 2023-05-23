#include <random>
#include <iostream>

int getRandomInt(int min, int max)
{
    std::random_device rd;  // Seed the random number generator
    std::mt19937 rng(rd()); // Initialize the random number engine

    std::uniform_int_distribution<int> distribution(min, max); // Define the range

    return distribution(rng); // Generate a random integer within the range
}

int getRandomInt(int max)
{
    return getRandomInt(0, max);
}
