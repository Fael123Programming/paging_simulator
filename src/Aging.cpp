#include "../include/Aging.hpp"

Aging::Aging(Disc disc, Ram ram) : PageSubstitutionAlgorithm(disc, ram), clockInterruptions(CLOCK_INTERRUPTIONS) {}

void Aging::execute() {
    int counter = 1;
    for (int i = 0; i < INSTRUCTIONS; i++) {
        this->nextInstruction();
        if (counter == this->clockInterruptions) {
            this->updateCounts();
            counter = 1;
        }
        this->ram.print();
        this->countOneForEachPage();
        counter++;
    }
}

void Aging::countOneForEachPage() {
    for (int i = 0; i < RLINES; i++) {
        this->counts[i].increment();
    }
}

void Aging::updateCounts() {
    for (int i = 0; i < RLINES; i++) {
        this->counts[i].shiftRight();  
        this->counts[i].putAsMostSignificantBit(this->ram.data[i][3]);
    }
}

int Aging::findPageInRam() {
    std::cout << "##### Instruction is not on ram #####\n";
    std::cout << "##### Loading it from disc... #####\n";
    int posSmallestCount = 0;
    for (int i = 1; i < RLINES; i++) {
        if (this->counts[i] < this->counts[posSmallestCount]) {
            posSmallestCount = i;
        }
    }
    return posSmallestCount;
}

void Aging::substitutePage(int pagePosOnDisc, int pagePosOnRam) {
    if (this->ram.data[pagePosOnRam][4]) {  // If page has been modified, synchronize it with disc.
        this->registerPageOnDisc(pagePosOnRam);
    }
    for (int i = 0; i < COLUMNS; i++) {
        this->ram.data[pagePosOnRam][i] = this->disc.data[pagePosOnDisc][i];
    }
}
