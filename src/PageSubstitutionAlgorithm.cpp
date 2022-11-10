#include "../include/PageSubstitutionAlgorithm.hpp"

PageSubstitutionAlgorithm::PageSubstitutionAlgorithm() {}

PageSubstitutionAlgorithm::PageSubstitutionAlgorithm(Disc d, Ram r) : disc(d), ram(r) {}

int PageSubstitutionAlgorithm::findPageInDisc(int pageInstruction) const {
    for (int i = 0; i < DLINES; i++) {
        if (this->disc.data[i][1] == pageInstruction) {
            return i;
        }
    }
    std::cout << "##### ERROR: Page with instruction '" << pageInstruction << "' wasn't found on disc #####\n";
    exit(-1);
}

void PageSubstitutionAlgorithm::substitutePage(int posPageRam, int posPageDisc) {
    for (int i = 0; i < COLUMNS; i++) {
        this->ram.data[posPageRam][i] = this->disc.data[posPageDisc][i];
    }
}

void PageSubstitutionAlgorithm::registerPageOnDisc(int pagePosOnRam) {  
    int pageNumber = this->ram.data[pagePosOnRam][0];
    for (int i = 0; i < DLINES; i++) {
        if (this->disc.data[i][0] == pageNumber) {
            this->disc.data[i][2] = this->ram.data[pagePosOnRam][2];
            this->ram.data[pagePosOnRam][4] = 0;  // Page is equal to what's on disc.
            std::cout << "##### Disc written #####\n";
            this->disc.print();
            return;
        }
    }
    std::cout << "##### ERROR: Page with number '" << pageNumber << "' wasn't found on disc #####\n";
    exit(-1);
}

int PageSubstitutionAlgorithm::nextInstruction() {
    RandomNumberGenerator rng;
    int nextInstruction = rng.generateBetween(1, 100), posPageRam, posPageDisc;
    std::cout << "##### Next instruction: " << nextInstruction << " #####\n";
    int pagePos = this->getPagePosFromRam(nextInstruction);
    if (pagePos != -1) {                        // Instruction is loaded on RAM.
        this->ram.data[pagePos][3] = 1;         // Read bit is set to 1.
        if (rng.generateBetween(1, 10) <= 3) {  // 30% of chance of being modified.
            this->ram.data[pagePos][2]++;       // Data is incremented by one.
            this->ram.data[pagePos][4] = 1;     // Modification bit is set to 1.
        }
    } else {  // Instruction isn't loaded on RAM, so it'll be needed to fetch it from disc.
        posPageRam = this->findPageInRam();
        posPageDisc = this->findPageInDisc(nextInstruction);
        this->substitutePage(posPageRam, posPageDisc);
    }
    return pagePos;
}

int PageSubstitutionAlgorithm::getPagePosFromRam(int instructionNumber) const {
    for (int i = 0; i < RLINES; i++) {
        if (this->ram.data[i][1] == instructionNumber) {
            return i;
        }
    }
    return -1;
}

