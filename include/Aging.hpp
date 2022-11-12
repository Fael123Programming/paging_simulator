#pragma once

#include "Disc.hpp"
#include "Ram.hpp"
#include "PageSubstitutionAlgorithm.hpp"
#include "Count.hpp"
#include "RandomNumberGenerator.hpp"

class Aging : public PageSubstitutionAlgorithm {
    public:
        Aging(Disc disc, Ram ram);

        void execute();
    private: 
        int clockInterruptions;

        Count counts[RLINES];

        void countOneForEachPage();

        void updateCounts();

        int findPageInRam();

        void substitutePage(int pageInstruction, int pagePosOnRam);
};
