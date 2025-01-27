#include "board.h"
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <iostream>
#include <algorithm>

Board::Board(int size, int mineCount) : size(size), mineCount(mineCount), mineCoords(mineCount)
{
    this->PlaceMines();
}

int Board::GetSize()
{
    return size;
}

void Board::Reset()
{
    this->PlaceMines();
}

void Board::PlaceMines()
{
    int totalCells = this->size * this->size;
    std::vector<int> pool(totalCells);

    std::iota(pool.begin(), pool.end(), 0);

    std::srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < this->mineCount; i++) {
        int randI = std::rand() % (pool.size());
        int cell = pool[randI];
        mineCoords[i] = cell;

        pool.erase(pool.begin() + randI);
    }
}

char Board::RevealCell(int row, int col)
{
    int linearCoord = row * 9 + col;

    if(std::find(mineCoords.begin(), mineCoords.end(), linearCoord) != mineCoords.end()) {
        /* Player hit a mine */
        return 'M';
    } else {
        /* Player hit a safe cell */
        int cellNumber = 0;
        if (row - 1 >= 0) {
            if (col - 1 >= 0) {
                if (std::find(mineCoords.begin(), mineCoords.end(), (row - 1) * 9 + col - 1) != mineCoords.end()) {
                    cellNumber++;
                }
            }

            if (std::find(mineCoords.begin(), mineCoords.end(), (row - 1) * 9 + col) != mineCoords.end()) {
                cellNumber++;
            }

            if (col + 1 <= 8) {
                if (std::find(mineCoords.begin(), mineCoords.end(), (row - 1) * 9 + col + 1) != mineCoords.end()) {
                    cellNumber++;
                }
            }
        }

        if (col - 1 >= 0) {
            if (std::find(mineCoords.begin(), mineCoords.end(), row * 9 + col - 1) != mineCoords.end()) {
                cellNumber++;
            }
        }

        if (col + 1 <= 8) {
            if (std::find(mineCoords.begin(), mineCoords.end(), row * 9 + col + 1) != mineCoords.end()) {
                cellNumber++;
            }
        }

        if (row + 1 <= 8) {
            if (col - 1 >= 0) {
                if (std::find(mineCoords.begin(), mineCoords.end(), (row + 1) * 9 + col - 1) != mineCoords.end()) {
                    cellNumber++;
                }
            }

            if (std::find(mineCoords.begin(), mineCoords.end(), (row + 1) * 9 + col) != mineCoords.end()) {
                cellNumber++;
            }

            if (col + 1 <= 8) {
                if (std::find(mineCoords.begin(), mineCoords.end(), (row + 1) * 9 + col + 1) != mineCoords.end()) {
                    cellNumber++;
                }
            }
        }

        // Adding 48 to convert to char in reference to the ASCII table
        return cellNumber + 48;
    }
}
