#include "board.h"
#include "qdebug.h"
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

Board::Board(int size, int mineCount) : size(size), mineCount(mineCount)
{
    privField.resize(size, std::vector<char>(size, '.'));
    drawField.resize(size, std::vector<char>(size, '.'));
    this->PlaceMines();
}

int Board::GetSize()
{
    return size;
}

void Board::Reset()
{
    this->drawField.clear();
    this->privField.clear();
    this->drawField.resize(size, std::vector<char>(size, '.'));
    this->privField.resize(size, std::vector<char>(size, '.'));
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
        int col = cell % size;
        int row = cell / size;
        privField[row][col] = 'M';
        pool.erase(pool.begin() + randI);
    }
}

std::vector<std::vector<char>> Board::GetField()
{
    return this->drawField;
}

void Board::RevealCell(int row, int col) {
    if (drawField[row][col] != '.') {
        return;
    }

    if (privField[row][col] == 'M') {
        drawField[row][col] = 'M';
        return;
    }

    std::queue<std::pair<int, int>> toReveal;
    std::set<std::pair<int, int>> visited;
    toReveal.push({row, col});
    visited.insert({row, col});

    while (!toReveal.empty()) {
        auto [r, c] = toReveal.front();
        toReveal.pop();

        drawField[r][c] = ' ';

        if (CheckAdjacentMines(r, c) > 0) {
            drawField[r][c] = '0' + CheckAdjacentMines(r, c);
            continue;
        }

        std::pair<int, int> directions[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

        for (int i = 0; i < 8; i++) {
            int newRow = r + directions[i].first;
            int newCol = c + directions[i].second;

            if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size) {
                if (visited.count({newRow, newCol}) == 0 && privField[newRow][newCol] != 'M') {
                    toReveal.push({newRow, newCol});
                    visited.insert({newRow, newCol});
                }
            }
        }
    }
}

void Board::FlagCell(int row, int col)
{
    if (drawField[row][col] == '.')
        drawField[row][col] = 'F';
    else if (drawField[row][col] == 'F')
        drawField[row][col] = '.';
}

int Board::CheckAdjacentMines(int row, int col)
{
    int mineCount = 0;
    std::pair<int, int> directions[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < 8; i++) {
        int newRow = row + directions[i].first;
        int newCol = col + directions[i].second;

        if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size) {
            if (privField[newRow][newCol] == 'M') {
                mineCount++;
            }
        }
    }

    return mineCount;
}
