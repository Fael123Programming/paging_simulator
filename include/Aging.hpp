#pragma once

#include "Disc.hpp"
#include "Ram.hpp"
#include "PageSubstitutionAlgorithm.hpp"
#include "RandomNumberGenerator.hpp"

class Aging : PageSubstitutionAlgorithm {
    public:
        Aging(Disc d, Ram r, int x);

        void execute();
    private: 
        int x;

        int counts[RLINES];

        void countOneForEachPage();

        void updateCounts();

        void substitutePageFromDisc(int pageInstruction);

        void substitutePage(int pageInstruction, int pagePosOnRam);
};
