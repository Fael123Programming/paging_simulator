#include "../include/PageSubstitutionAlgorithm.hpp"
#include "../include/RandomNumberGenerator.hpp"

PageSubstitutionAlgorithm::PageSubstitutionAlgorithm(Disc d, Ram r) : disc(d), ram(r) {}

void PageSubstitutionAlgorithm::simulate() {
    RandomNumberGenerator rng;
    int nextInstruction;
    int pagePos;
    for (int i = 0; i < INSTRUCTIONS; i++) {        // First page substitution algorithm.
        nextInstruction = rng.generateBetween(1, 100);
        pagePos = this->getPagePos(nextInstruction);
        if (pagePos != -1) {                        // Instruction is loaded on RAM.
            this->ram.data[pagePos][3] = 1;         // Read bit is set to 1.
            if (rng.generateBetween(1, 10) <= 3) {  // 30% of chance of being modified.
                this->ram.data[pagePos][2]++;       // Data is incremented.
                this->ram.data[pagePos][4] = 1;     // Modification bit is set to 1.
            }
        } else {  // Instruction isn't loaded on RAM, so it'll be needed to fetch it from disc.
            this->substitutePageFromDisc();
        }
        this->updateCvt();
    }
}

int PageSubstitutionAlgorithm::getPagePos(int instructionNumber) const {
    for (int i = 0; i < RLINES; i++) {
        if (this->ram.data[i][1] == instructionNumber) {
            return i;
        }
    }
    return -1;
}
