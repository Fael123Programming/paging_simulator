#pragma once

#include "Disc.hpp"
#include "Ram.hpp"
#include "RandomNumberGenerator.hpp"

class PageSubstitutionAlgorithm {
    public:
        PageSubstitutionAlgorithm();

        PageSubstitutionAlgorithm(Disc d, Ram r);

        virtual void execute() = 0;
    protected:
        Disc disc;

        Ram ram;    

        /// @brief Finds a page in ram to be replaced by the new page from disc according to the algorithm's own implementation.
        /// @return the position of the page in ram to be replaced.
        virtual int findPageInRam() = 0;

        /// @brief Finds the page in disc that has 'pageInstruction' as its instruction number.
        /// @return the position of the corresponding page in disc.
        int findPageInDisc(int pageInstruction) const;

        /// @brief Replaces the page in ram at 'posPageRam' with the page in disc at 'posPageDisc'.
        /// @param posPageRam the position in ram of the page to be replaced.
        /// @param posPageDisc the position in disc of the new page.
        void substitutePage(int posPageRam, int posPageDisc);

        void registerPageOnDisc(int pagePosOnRam);

        int nextInstruction();

        int getPagePosFromRam(int instructionNumber) const;
};
