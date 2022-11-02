#include "../include/Ram.hpp"
#include "../include/RandomNumberGenerator.hpp"
#include <set>
#include <iomanip>

Ram::Ram(Disc disc) {
    RandomNumberGenerator rng;
    int random;
    std::set<int> nums;
    for (int i = 0; i < RLINES; i++) {
        random = rng.generateBetween(0, 99);
        while (nums.contains(random)) {
            random = rng.generateBetween(0, 99);
        }
        nums.insert(random);
        for (int j = 0; j < COLUMNS; j++) {
            this->data[i][j] = disc.data[random][j];
        }
    }
}

void Ram::print() const {
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

