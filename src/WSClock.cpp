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

void WSClock::substitutePageFromDisc(int pageInstruction) {
    std::cout << "##### Instruction is not on ram #####\n";
    std::cout << "##### Loading it from disc... #####\n";
    int readBitCurrentPage, modificationBitCurrentPage, posOnRamOldestPage = this->currentPage, ageCurrentPage, ageOldestPage = this->cvt - this->lastAccessTime[this->currentPage];
    int counter = 0;
    while (true) {
        if (this->currentPage == RLINES) {
            this->currentPage = 0;
        }
        if (counter == RLINES) {                // Algoritmo deu uma volta completa.
            // std::cout << "##### FULL LAP #####\n";
            for (int j = 0; j < RLINES; j++) {
                if (this->currentPage == RLINES) {
                    this->currentPage = 0;
                }
                if (this->ram.data[this->currentPage][4] == 0) {
                    // std::cout << "this->currentPage=" << this->currentPage << std::endl;
                    this->substitutePage(pageInstruction, this->currentPage);
                    return;
                }
                this->currentPage++;
                j++;
            } 
            // Se nao ha pagina com M = 0, substitui a pagina com maior idade.
            this->substitutePage(pageInstruction, posOnRamOldestPage);
            this->currentPage++;
            return;
        }
        readBitCurrentPage = this->ram.data[this->currentPage][3];
        if (readBitCurrentPage == 1) {          
            this->ram.data[this->currentPage][3] = 0;             // Set read bit to 0.
            // std::cout << "TLU1: " << this->lastAccessTime[this->currentPage] << std::endl;
            this->lastAccessTime[this->currentPage] = this->cvt;  // Set page last access time to cvt.
            // std::cout << "TLU2: " << this->lastAccessTime[this->currentPage] << std::endl;
            this->currentPage++;
            // std::cout << "##### Read bit set to 0 #####\n";
            this->ram.print();
        } else if (readBitCurrentPage == 0) {
            if (this->cvt > 1) {
                ageCurrentPage = this->cvt - this->lastAccessTime[this->currentPage];
            // std::cout << "ageCurrentPage=" << ageCurrentPage << std::endl;
            // std::cout << "ageOldestPage=" << ageOldestPage << std::endl;
                if (ageCurrentPage <= this->agingInterval) {
                    ageOldestPage = this->cvt - this->lastAccessTime[posOnRamOldestPage];
                    if (ageCurrentPage > ageOldestPage) {
                        posOnRamOldestPage = this->currentPage;
                    }
                    this->currentPage++;
                } else {
                    modificationBitCurrentPage = this->ram.data[this->currentPage][4];
                    if (modificationBitCurrentPage == 0) { 
                        this->substitutePage(pageInstruction, this->currentPage);
                        this->currentPage++;
                        return;
                    } else if (modificationBitCurrentPage == 1) {
                        this->registerPageOnDisc(this->currentPage);
                        this->substitutePage(pageInstruction, this->currentPage);
                        this->currentPage++;
                        return;
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

void WSClock::substitutePage(int pageInstruction, int pagePosOnRam) {
    for (int i = 0; i < DLINES; i++) {
        if (this->disc.data[i][1] == pageInstruction) {
            std::cout << "##### Page " << this->ram.data[pagePosOnRam][0] << " substituted by " << i << " #####\n";
            for (int j = 0; j < COLUMNS; j++) {
                this->ram.data[pagePosOnRam][j] = this->disc.data[i][j];
            }
            this->ram.data[pagePosOnRam][3] = 1;             // Read bit is set to 1.
            this->lastAccessTime[pagePosOnRam] = this->cvt; 
            return;
        }
    }
    std::cout << "##### ERROR: Page with instruction '" << pageInstruction << "' wasn't found on disc #####\n";
    exit(-1);
}
