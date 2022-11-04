#include <iostream>
#include "include/Disc.hpp"
#include "include/Ram.hpp"
#include "include/PageSubstitutionAlgorithm.hpp"
#include "include/RandomNumberGenerator.hpp"

int main() {
    Disc disc;
    Ram ram(disc);
    disc.print();
    ram.print();
    
    return 0;
}
