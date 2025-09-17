#include "board.h"
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <queue>
#include <set>

Board::Board(int sizex, int sizey, int mineCount) : sizex(sizex), sizey(sizey), mineCountTotal(mineCount), mineCountRem(mineCount)
{
    privField.resize(sizex, std::vector<char>(sizey, '.'));
    drawField.resize(sizex, std::vector<char>(sizey, '.'));
    losingField.resize(sizex, std::vector<char>(sizey, '.'));
    freeCountRem = sizex * sizey - mineCount;
    PlaceMines();
}

int Board::GetSizex()
{
    return sizex;
}

int Board::GetSizey()
{
    return sizey;
}

int Board::GetMineCount()
{
    return mineCountRem;
}

void Board::Reset()
{
    drawField.clear();
    privField.clear();
    drawField.resize(sizex, std::vector<char>(sizey, '.'));
    privField.resize(sizex, std::vector<char>(sizey, '.'));
    mineCountRem = this->mineCountTotal;
    freeCountRem = sizex * sizey - mineCountTotal;
    PlaceMines();
}

void Board::PlaceMines()
{
    int totalCells = sizex * sizey;
    std::vector<int> pool(totalCells);

    std::iota(pool.begin(), pool.end(), 0);

    std::srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < this->mineCountTotal; i++) {
        int randI = std::rand() % (pool.size());
        int cell = pool[randI];
        int col = cell % sizey;
        int row = cell / sizey;
        privField[row][col] = 'M';
        pool.erase(pool.begin() + randI);
    }
}

std::vector<std::vector<char>>* Board::GetField()
{
    return &drawField;
}

std::vector<std::vector<char>>* Board::GetLosingField()
{
    for (int row = 0; row < sizex; ++row) {
        for (int col = 0; col < sizey; ++col) {
            if (drawField[row][col] == '.' && privField[row][col] == 'M')
            {
                losingField[row][col] = 'M';
                continue;
            }
            if (drawField[row][col] == 'F' && privField[row][col] != 'M')
            {
                losingField[row][col] = 'X';
                continue;
            }

            losingField[row][col] = drawField[row][col];
        }
    }

    return &losingField;
}

std::vector<std::vector<char>>* Board::GetPrivField()
{
    return &privField;
}

int Board::RevealCell(int row, int col) {
    if (drawField[row][col] != '.') {
        return this->ChordCell(row, col);
    }

    if (privField[row][col] == 'M') {
        drawField[row][col] = 'B';
        return -1;
    }

    std::queue<std::pair<int, int>> toReveal;
    std::set<std::pair<int, int>> visited;
    toReveal.push({row, col});
    visited.insert({row, col});

    while (!toReveal.empty()) {
        auto [r, c] = toReveal.front();
        toReveal.pop();

        drawField[r][c] = '0';
        freeCountRem--;

        if (CheckAdjacentMines(r, c) > 0) {
            drawField[r][c] = '0' + CheckAdjacentMines(r, c);
            continue;
        }

        std::pair<int, int> directions[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

        for (int i = 0; i < 8; i++) {
            int newRow = r + directions[i].first;
            int newCol = c + directions[i].second;

            if (newRow >= 0 && newRow < sizex && newCol >= 0 && newCol < sizey) {
                if (visited.count({newRow, newCol}) == 0 && privField[newRow][newCol] != 'M' && drawField[newRow][newCol] == '.') {
                    toReveal.push({newRow, newCol});
                    visited.insert({newRow, newCol});
                }
            }
        }
    }

    if (freeCountRem == 0)
        return 2;
    return 1;
}

int Board::ChordCell(int row, int col)
{
    if (drawField[row][col] == ' ')
        return 0;

    // Check if is satisfied
    int revealedNum = drawField[row][col] - 48;
    if (CheckAdjacentFlags(row, col) != revealedNum)
        return 0;

    // If yes: chord
    std::pair<int, int> directions[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    bool foundMine = false;
    bool gameWon = false;
    for (int i = 0; i < 8; i++) {
        int newRow = row + directions[i].first;
        int newCol = col + directions[i].second;

        if (newRow >= 0 && newRow < sizex && newCol >= 0 && newCol < sizey) {
            if (drawField[newRow][newCol] == '.') {
                int res = RevealCell(newRow, newCol);
                if (res == -1)
                    foundMine = true;
                else if (res == 2)
                    gameWon = true;
            }
        }
    }

    if (foundMine)
        return -1;
    if (gameWon)
        return 2;
    return 1;
}

void Board::FlagCell(int row, int col)
{
    if (drawField[row][col] == '.') {
        drawField[row][col] = 'F';
        mineCountRem--;
    }
    else if (drawField[row][col] == 'F') {
        drawField[row][col] = '.';
        mineCountRem++;
    }
}

int Board::CheckAdjacentMines(int row, int col)
{
    int mines = 0;
    std::pair<int, int> directions[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < 8; i++) {
        int newRow = row + directions[i].first;
        int newCol = col + directions[i].second;

        if (newRow >= 0 && newRow < sizex && newCol >= 0 && newCol < sizey) {
            if (privField[newRow][newCol] == 'M') {
                mines++;
            }
        }
    }

    return mines;
}

int Board::CheckAdjacentFlags(int row, int col)
{
    int flagCount = 0;
    std::pair<int, int> directions[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < 8; i++) {
        int newRow = row + directions[i].first;
        int newCol = col + directions[i].second;

        if (newRow >= 0 && newRow < sizex && newCol >= 0 && newCol < sizey) {
            if (drawField[newRow][newCol] == 'F') {
                flagCount++;
            }
        }
    }

    return flagCount;
}
