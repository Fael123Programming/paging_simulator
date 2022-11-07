#include <iostream>
#include "include/Disc.hpp"
#include "include/Ram.hpp"
#include "include/WSClock.hpp"

int main() {
    Disc disc;
    Ram ram(disc);
    WSClock wsc(disc, ram, 10);
    disc.print();
    ram.print();
    std::cout << "##### Starting execution #####\n";
    wsc.execute();

    return 0;
}
