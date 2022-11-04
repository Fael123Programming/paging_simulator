#pragma once

#include "Disc.hpp"
#include "Ram.hpp"

class PageSubstitutionAlgorithm {
    public:
        PageSubstitutionAlgorithm(Disc disc, Ram ram);

        void simulate();
    protected:
        Disc disc;

        Ram ram;

        virtual void substitutePageFromDisc();

        int getPagePos(int instructionNumber) const;  
};
