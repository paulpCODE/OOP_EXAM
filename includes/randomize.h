#ifndef RANDOMIZE_H
#define RANDOMIZE_H

#include <random>
#include <algorithm>

namespace Randomizing {

// shuffle given array
// @param myarray array( pointer to first element)
// @param size size of array
template <typename T>
void shuffleArray(T * myarray,int size);

// generates random integer from given range
// @param from begin of randomizing range
// @param to end of randomizing range
int generateRandomInt(int from,int to);

}

#endif // RANDOMIZE_H
