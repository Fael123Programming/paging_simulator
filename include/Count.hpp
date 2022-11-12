#pragma once

#include <iostream>
#include "Define.hpp"

class Count {
    public:
        Count();

        void increment();

        void shiftRight();

        void putAsMostSignificantBit(short value);

        friend std::ostream& operator <<(std::ostream& out, const Count& count);
        
        bool operator <(const Count another);
    private:
        short bits[COUNT_SIZE];

        void zerofy();
};
