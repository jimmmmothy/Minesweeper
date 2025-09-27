#include "board.h"
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <queue>
#include <set>

Board::Board(int sizex, int sizey, int mineCount) : sizex(sizex), sizey(sizey), mineCountTotal(mineCount), mineCountRem(mineCount)
{
    privField = InitField();
    publicField = InitField();
    losingField = InitField();
    freeCountRem = sizex * sizey - mineCount;
    PlaceMines();
}

char** Board::InitField()
{
    char** field = new char*[this->sizex];
    for (int row = 0; row < sizex; ++row) {
        field[row] = new char[sizey];
        for (int col = 0; col < sizey; ++col) {
            field[row][col] = '.';
        }
    }

    return field;
}

void Board::ResetField(char** field)
{
    for (int row = 0; row < sizex; ++row) {
        for (int col = 0; col < sizey; ++col) {
            field[row][col] = '.';
        }
    }
}

void Board::FinishPublicField()
{
    for (int row = 0; row < sizex; ++row) {
        for (int col = 0; col < sizey; ++col) {
            if (privField[row][col] == 'M' && publicField[row][col] == '.')
                publicField[row][col] = 'F';
        }
    }
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
    ResetField(privField);
    ResetField(publicField);
    ResetField(losingField);
    mineCountRem = this->mineCountTotal;
    freeCountRem = sizex * sizey - mineCountTotal;
    PlaceMines();
}

void Board::PlaceMines()
{
    const std::size_t totalCells = sizex * sizey;
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

char** Board::GetPublicField()
{
    return publicField;
}

char** Board::GetLosingField()
{
    for (int row = 0; row < sizex; ++row) {
        for (int col = 0; col < sizey; ++col) {
            if (publicField[row][col] == '.' && privField[row][col] == 'M')
            {
                losingField[row][col] = 'M';
                continue;
            }
            if (publicField[row][col] == 'F' && privField[row][col] != 'M')
            {
                losingField[row][col] = 'X';
                continue;
            }

            losingField[row][col] = publicField[row][col];
        }
    }

    return losingField;
}

char** Board::GetPrivField()
{
    return privField;
}

int Board::RevealCell(int row, int col) {
    if (publicField[row][col] != '.') {
        return this->ChordCell(row, col);
    }

    if (privField[row][col] == 'M') {
        publicField[row][col] = 'B';
        return -1;
    }

    std::queue<std::pair<int, int>> toReveal;
    std::set<std::pair<int, int>> visited;
    toReveal.push({row, col});
    visited.insert({row, col});

    while (!toReveal.empty()) {
        auto [r, c] = toReveal.front();
        toReveal.pop();

        publicField[r][c] = '0';
        freeCountRem--;

        if (CheckAdjacentMines(r, c) > 0) {
            publicField[r][c] = '0' + CheckAdjacentMines(r, c);
            continue;
        }

        std::pair<int, int> directions[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

        for (int i = 0; i < 8; i++) {
            int newRow = r + directions[i].first;
            int newCol = c + directions[i].second;

            if (newRow >= 0 && newRow < sizex && newCol >= 0 && newCol < sizey) {
                if (visited.count({newRow, newCol}) == 0 && privField[newRow][newCol] != 'M' && publicField[newRow][newCol] == '.') {
                    toReveal.push({newRow, newCol});
                    visited.insert({newRow, newCol});
                }
            }
        }
    }

    if (freeCountRem == 0)
    {
        FinishPublicField();
        return 2;
    }
    return 1;
}

int Board::ChordCell(int row, int col)
{
    if (publicField[row][col] == ' ')
        return 0;

    // Check if is satisfied
    int revealedNum = publicField[row][col] - 48;
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
            if (publicField[newRow][newCol] == '.') {
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
    {
        FinishPublicField();
        return 2;
    }

    return 1;
}

void Board::FlagCell(int row, int col)
{
    if (publicField[row][col] == '.') {
        publicField[row][col] = 'F';
        mineCountRem--;
    }
    else if (publicField[row][col] == 'F') {
        publicField[row][col] = '.';
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
            if (publicField[newRow][newCol] == 'F') {
                flagCount++;
            }
        }
    }

    return flagCount;
}
