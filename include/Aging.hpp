#pragma once

#include "Disc.hpp"
#include "Ram.hpp"
#include "PageSubstitutionAlgorithm.hpp"
#include "RandomNumberGenerator.hpp"

class Aging : public PageSubstitutionAlgorithm {
    public:
        Aging(Disc disc, Ram ram);

        void execute();
    private: 
        int clockInterruptions;

        int counts[RLINES];

        void countOneForEachPage();

        void updateCounts();

        void substitutePageFromDisc(int pageInstruction);

        void substitutePage(int pageInstruction, int pagePosOnRam);
};
