#pragma once

#include "Disc.hpp"
#include "Ram.hpp"
#include "RandomNumberGenerator.hpp"

class PageSubstitutionAlgorithm {
    public:
        PageSubstitutionAlgorithm();

        PageSubstitutionAlgorithm(Disc d, Ram r);

        virtual void execute();
    protected:
        Disc disc;

        Ram ram;    

        virtual void substitutePageFromDisc(int pageInstruction);

        virtual void substitutePage(int pageInstruction, int pagePosOnRam);

        void registerPageOnDisc(int pagePosOnRam);

        int nextInstruction();

        int getPagePos(int instructionNumber) const;
};
