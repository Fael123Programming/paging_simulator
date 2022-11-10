#include "../include/WSClock.hpp"

WSClock::WSClock(Disc disc, Ram ram) : PageSubstitutionAlgorithm(disc, ram), agingInterval(AGING_INTERVAL), currentPage(0), cvt(1) {
    for (int i = 0; i < RLINES; i++) {
        this->lastAccessTime[i] = 0;
    }
}

void WSClock::execute() {
    int posPageChanged;
    for (int i = 0; i < INSTRUCTIONS; i++) {        // First page substitution algorithm.
        std::cout << "##### Current Virtual Time: " << this->cvt << " #####\n";
        posPageChanged = this->nextInstruction();
        if (posPageChanged != -1) {
            this->lastAccessTime[posPageChanged] = this->cvt;
        }
        this->ram.print();
        this->updateCvt();
    }
}   

void WSClock::updateCvt() {
    this->cvt++;
}

int WSClock::findPageInRam() {
    std::cout << "##### Instruction is not on ram #####\n";
    std::cout << "##### Loading it from disc... #####\n";
    int readBitCurrentPage, modificationBitCurrentPage, posOnRamOldestPage = this->currentPage, ageCurrentPage, ageOldestPage = this->cvt - this->lastAccessTime[this->currentPage];
    int counter = 0;
    while (true) {
        if (this->currentPage == RLINES) {
            this->currentPage = 0;
        }
        if (counter == RLINES) {                
            for (int j = 0; j < RLINES; j++) {
                if (this->currentPage == RLINES) {
                    this->currentPage = 0;
                }
                if (this->ram.data[this->currentPage][4] == 0) {
                    return this->currentPage;
                }
                this->currentPage++;
                j++;
            } 
            this->currentPage++;
            return posOnRamOldestPage;
        }
        readBitCurrentPage = this->ram.data[this->currentPage][3];
        if (readBitCurrentPage == 1) {          
            this->ram.data[this->currentPage][3] = 0;             // Set read bit to 0.
            this->lastAccessTime[this->currentPage] = this->cvt;  // Set page last access time to cvt.
            this->currentPage++;
            this->ram.print();
        } else if (readBitCurrentPage == 0) {
            if (this->cvt > 1) {
                ageCurrentPage = this->cvt - this->lastAccessTime[this->currentPage];
                if (ageCurrentPage <= this->agingInterval) {
                    ageOldestPage = this->cvt - this->lastAccessTime[posOnRamOldestPage];
                    if (ageCurrentPage > ageOldestPage) {
                        posOnRamOldestPage = this->currentPage;
                    }
                    this->currentPage++;
                } else {
                    modificationBitCurrentPage = this->ram.data[this->currentPage][4];
                    if (modificationBitCurrentPage == 0) { 
                        this->currentPage++;
                        return this->currentPage;
                    } else if (modificationBitCurrentPage == 1) {
                        this->registerPageOnDisc(this->currentPage);
                        this->currentPage++;
                        return this->currentPage;
                    } else {
                        std::cout << "##### ERROR: Modification bit has a value different of 0 and 1 (M = " << modificationBitCurrentPage << ") #####\n";
                        exit(-1);
                    }
                }
            }
        } else {
            std::cout << "##### ERROR: Read bit has a value different of 0 and 1 (R = " << readBitCurrentPage << ") #####\n";
            exit(-1);
        }
        counter++;
    }
}
