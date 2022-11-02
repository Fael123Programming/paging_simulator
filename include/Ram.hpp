#pragma once

#include "Disc.hpp"
#include "Define.hpp"

class Ram {
    public:
        Ram(Disc disc);

        void print() const;
    private:
        int data[RLINES][COLUMNS];
};
