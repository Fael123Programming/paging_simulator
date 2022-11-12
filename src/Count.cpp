#include "../include/Count.hpp"

Count::Count() {
    this->zerofy();
}

void Count::increment() {
    int ones = 0, posRightmostZero = -1;
    // Find rightmost zero.
    for (int i = 0; i < COUNT_SIZE; i++) {
        if (this->bits[i] == 0) {
            posRightmostZero = i;
        }
    }
    if (posRightmostZero == -1) {  // If have reached all possible numbers with the given bits.
        this->zerofy();
        return;
    }
    // If there's a '1' after it, it must be switched over to '0'.
    for (int i = posRightmostZero + 1; i < COUNT_SIZE; i++) {
        if (this->bits[i] == 1) {
            this->bits[i] = 0;
        }
    }
    this->bits[posRightmostZero] = 1; // Switch the rightmost zero to one.
}

void Count::shiftRight() {
    int temp[COUNT_SIZE - 1];
    for (int i = 0; i < COUNT_SIZE - 1; i++) {
        temp[i] = this->bits[i];
    }
    this->bits[0] = 0;
    for (int i = 1; i < COUNT_SIZE; i++) {
        this->bits[i] = temp[i - 1];
    }
}

std::ostream& operator <<(std::ostream& out, const Count& count) {
    for (int i = 0; i < COUNT_SIZE; i++) {
        out << count.bits[i];
    }
    out << std::endl;
    return out;
}

void Count::zerofy() {
    for (int i = 0; i < COUNT_SIZE; i++) {
        this->bits[i] = 0;
    }
}

void Count::putAsMostSignificantBit(short value) {
    this->bits[0] = value;
}

bool Count::operator <(Count anotherCount) {
    for (int i = 0; i < COUNT_SIZE; i++) {
        if (this->bits[i] < anotherCount.bits[i]) {
            return true;
        } else if (this->bits[i] > anotherCount.bits[i]) {
            return false;
        }
    }
    return false;  // All bits from both counts were avaluated as equal.
}
