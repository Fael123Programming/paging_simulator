#include "../include/WSClock.hpp"

WSClock::WSClock(Disc disc, Ram ram, int t) : PageSubstitutionAlgorithm(disc, ram), t(t), currentPos(0), cvt(0) {
    for (int i = 0; i < RLINES; i++) {
        this->lastAccessTime[i] = 0;
    }
}

void WSClock::updateData() {
    this->cvt++;
}

void WSClock::substitutePageFromDisc() {
    
}
