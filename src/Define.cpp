#include "../include/Define.hpp"

void row (){
    std::string row = "";
    for (int i = 0; i < ROW_SIZE; i++) {
        row += "-";
    }
    std::cout << row << std::endl;
}
