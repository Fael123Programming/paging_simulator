#include <iostream>
#include "include/Disc.hpp"
#include "include/RandomNumberGenerator.hpp"

int getPagePos(int instructionNumber);

int main() {
    std::cout << "##### DISC #####\n";
    std::cout << std::endl;
    std::cout << "##### RAM #####\n";
    printMemory(ram, RLINES);
    std::cout << std::endl;
    int nextInstruction;
    int pagePos;
    for (int i = 0; i < INSTRUCTIONS; i++) {  // First page substitution algorithm.
        nextInstruction = rng.generateBetween(1, 100);
        pagePos = getPagePos(nextInstruction);
        if (pagePos != -1) {  // Instruction is loaded on RAM.
            ram[pagePos][3] = 1;  // Read bit is set to 1.
            if (rng.generateBetween(1, 10) <= 3) {  // 30% of chance of being modified.
                ram[pagePos][2]++;  // Data is incremented.
                ram[pagePos][4] = 1;  // Modification bit is set to 1.
            }
        } else {  // Instruction isn't loaded on RAM, so it'll be needed to fetch it from disc.

        }
    }
    for (int i = 0; i < INSTRUCTIONS; i++) {  // Second page substitution algorithm.

    }

    return 0;
}

int getPagePos(int instructionNumber) {
    for (int i = 0; i < RLINES; i++) {
        if (ram[i][1] == instructionNumber) {
            return i;
        }
    }
    return -1;
}
