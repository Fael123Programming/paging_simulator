#include "../include/Disc.hpp"
#include "../include/RandomNumberGenerator.hpp"
#include <iomanip>

Disc::Disc() {
    RandomNumberGenerator rng;
    for (int i = 0; i < DLINES; i++) {
        this->data[i][0] = i; // Page number will be from 0 to 99.
        this->data[i][1] = i + 1; // Instruction will be from 1 to 100.
        this->data[i][2] = rng.generateBetween(1, 50);  // Data will be a random number between 1-50.
        this->data[i][3] = 0;  // Access bit is set to zero.
        this->data[i][4] = 0;  // Modification bit is also set to zero.
    }
}

void Disc::print() const {
    row();
    std::cout << std::left << std::setw(SPACE_SIZE) << " " << "COLUMN\n";
    std::cout << std::left << std::setw(SPACE_SIZE) << " ";
    for (int j = 0; ; j++) {
        if (j < COLUMNS) {
            std::cout << std::left << std::setw(SPACE_SIZE) << j;
        }  else {
            std::cout << std::endl;
            break;
        }
    }
    row();
    std::cout << std::left << std::setw(SPACE_SIZE) << "ROW" 
        << std::left << std::setw(SPACE_SIZE) << "N" 
        << std::left << std::setw(SPACE_SIZE) << "I" 
        << std::left << std::setw(SPACE_SIZE) << "D" 
        << std::left << std::setw(SPACE_SIZE) << "R" 
        << std::left << std::setw(SPACE_SIZE) << "M";
    std::cout << std::endl;
    row();
    for (int i = 0; i < DLINES; i++) {
        std::cout << std::left << std::setw(SPACE_SIZE) << i    // Row number.
            << std::left << std::setw(SPACE_SIZE) << this->data[i][0]  // Page number. 
            << std::left << std::setw(SPACE_SIZE) << this->data[i][1]  // Instruction number.
            << std::left << std::setw(SPACE_SIZE) << this->data[i][2]  // Data value.
            << std::left << std::setw(SPACE_SIZE) << this->data[i][3]  // Read bit.
            << std::left << std::setw(SPACE_SIZE) << this->data[i][4]  // Modification bit. 
            << std::endl;
    }
    row();
}
