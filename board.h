#pragma once

#include <vector>

class Board
{
public:
    Board(int sizex, int sizey, int mineCount);
    void PlaceMines();
    int RevealCell(int row, int col);
    int ChordCell(int row, int col);
    void FlagCell(int row, int col);
    void Reset();
    int GetSizex();
    int GetSizey();
    int GetMineCount();
    std::vector<std::vector<char>> GetField();
    std::vector<std::vector<char>> GetPrivField();
    int CheckAdjacentMines(int row, int col);
    int CheckAdjacentFlags(int row, int col);

private:;
    int sizex;
    int sizey;
    int mineCountTotal;
    int mineCountRem;
    int freeCountRem;
    std::vector<std::vector<char>> privField;
    std::vector<std::vector<char>> drawField;
};
