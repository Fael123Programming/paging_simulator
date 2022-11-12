#pragma once

#include "Disc.hpp"
#include "Ram.hpp"
#include "RandomNumberGenerator.hpp"

class PageSubstitutionAlgorithm {
    public:
        PageSubstitutionAlgorithm();

        PageSubstitutionAlgorithm(Disc d, Ram r);

        /// @brief The main routine of each page substitution algorithm. This procedure should call
        /// nextInstruction() accordingly.
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

        /// @brief Synchronizes the page at 'pagePosOnRam' with the disc.
        /// @param pagePosOnRam the page position at ram.
        void registerPageOnDisc(int pagePosOnRam);

        /// @brief Generates a random page instruction number and verifies whether the corresponding
        /// page is loaded in ram or not. If so, the page is read and possibly modified (30% of chance).
        /// Else the findPageInRam, findPageInDisc and substitutePage members are called to substitute
        /// a certain page in ram by the page in disc that has the generated random page instruction as its
        /// instruction number.
        /// @return the next page instruction number needed by the simulated process being run. In case the page
        /// isn't in ram, -1 is returned.
        int nextInstruction();

        /// @brief Checks which page in ram has 'instructionNumber' as its intruction number and returns its position.
        /// @param instructionNumber the instruction number of the page in ram.
        /// @return the page instruction number or -1 if not found.
        int getPagePosFromRam(int instructionNumber) const;
};
