#include <iostream>

#define DLINES 100
#define RLINES 100
#define COLUMNS 5
#define ROW_SIZE 120
#define SPACE_SIZE 20
#define INSTRUCTIONS 500

void row() {
    std::string row = "";
    for (int i = 0; i < ROW_SIZE; i++) {
        row += "-";
    }
    std::cout << row << std::endl;
}
