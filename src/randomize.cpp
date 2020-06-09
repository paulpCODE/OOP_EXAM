
#include"includes/randomize.h"

using namespace Randomizing;

// shuffle given array
// @param myarray array( pointer to first element)
// @param size size of array
template <typename T>
void Randomizing::shuffleArray(T * myarray,int size){
    std::random_device rd; // non-deterministic generator
    std::mt19937 gen(rd()); // to seed mersenne twister.
    std::shuffle(&(myarray[0]),&(myarray[size-1]),gen);
}

// generates random integer from given range
// @param from begin of randomizing range
// @param to end of randomizing range
int Randomizing::generateRandomInt(int from,int to){
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> dist(from,to);
    return dist(gen); // returns generated item
}


