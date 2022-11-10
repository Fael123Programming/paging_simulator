#pragma once

#include "Disc.hpp"
#include "Define.hpp"

class Ram {
    public:
        Ram();

        Ram(Disc disc);

        void print() const;
    
        int data[RLINES][COLUMNS];
};
