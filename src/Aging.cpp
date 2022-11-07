#include "../include/Aging.hpp"

Aging::Aging(Disc d, Ram r, int x) : PageSubstitutionAlgorithm(d, r), x(x) {
    for (int i = 0; i < RLINES; i++) {
        this->counts[i] = 0;
    }
}

void Aging::execute() {
    int counter = 1;
    for (int i = 0; i < INSTRUCTIONS; i++) {
        this->nextInstruction();
        if (counter == this->x) {
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
        this->counts[i]++;
    }
}

void Aging::updateCounts() {
    for (int j = 0; j < RLINES; j++) {
        this->counts[j] >>= 1;  
        this->counts[j] |= this->ram.data[j][3];
    }
}

void Aging::substitutePageFromDisc(int pageInstruction) {
    std::cout << "##### Instruction is not on ram #####\n";
    std::cout << "##### Loading it from disc... #####\n";
    int posSmallestCount = 0;
    for (int i = 0; i < RLINES; i++) {
        if (i == 0) {
            posSmallestCount = 0;
        } else if (this->counts[i] < this->counts[posSmallestCount]) {
            posSmallestCount = i;
        }
    }
    int posDisc;
    for (int i = 0; i < DLINES; i++) {
        if (this->disc.data[i][1] == pageInstruction) {
            this->substitutePage(i, posSmallestCount);
            return;
        }
    }
    std::cout << "##### ERROR: Page with instruction '" << pageInstruction << "' wasn't found on disc #####\n";
    exit(-1);
}

void Aging::substitutePage(int pagePosOnDisc, int pagePosOnRam) {
    if (this->ram.data[pagePosOnRam][4]) {  // If page has been modified, synchronize it with disc.
        this->registerPageOnDisc(pagePosOnRam);
    }
    for (int i = 0; i < COLUMNS; i++) {
        this->ram.data[pagePosOnRam][i] = this->disc.data[pagePosOnDisc][i];
    }
}
