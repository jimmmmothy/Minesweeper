#include "board.h"
#include <random>

Board::Board(int size, int mineCount) : size(size), mineCount(mineCount) {
    field.resize(size, std::vector<char>(size, '.'));
}

std::vector<std::vector<char>> Board::GetField() {
    return this->field;
}
