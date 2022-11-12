#include <iostream>
#include "include/Disc.hpp"
#include "include/Ram.hpp"
#include "include/PageSubstitutionAlgorithm.hpp"
#include "include/WSClock.hpp"
#include "include/Aging.hpp"

int main() {
    Disc disc;
    Ram ram(disc);
    WSClock wsc(disc, ram);
    Aging ag(disc, ram);
    PageSubstitutionAlgorithm *psa;
    // psa = &wsc;
    psa = &ag;
    disc.print();
    ram.print();
    std::cout << "##### Starting execution #####\n";
    psa->execute();

    return 0;
}
