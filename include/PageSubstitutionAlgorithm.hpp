#pragma once

#include "Disc.hpp"
#include "Ram.hpp"
#include "RandomNumberGenerator.hpp"

class PageSubstitutionAlgorithm {
    public:
        PageSubstitutionAlgorithm(Disc d, Ram r);

        virtual void execute() = 0;
    protected:
        Disc disc;

        Ram ram;

        virtual void substitutePageFromDisc(int pageInstruction) = 0;

        virtual void substitutePage(int pageInstruction, int pagePosOnRam) = 0;

        void registerPageOnDisc(int pagePosOnRam);

        int nextInstruction();

        int getPagePos(int instructionNumber) const;
};
