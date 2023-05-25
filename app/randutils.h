#ifndef RANDUTILS_H
#define RANDUTILS_H

#include <random>
#include <algorithm>

namespace core {

int getRandomInt(int min, int max);
int getRandomInt(int max);
bool getRandomBool();

template<typename T>
void randomizeVector(std::vector<T>& vec)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(vec.begin(), vec.end(), gen);
}

} // namespace core

#endif // RANDUTILS_H
