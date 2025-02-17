#ifndef BOARD_H
#define BOARD_H
#include <vector>

class Board
{
public:
    Board(int size, int mineCount);
    void PlaceMines();
    void RevealCell(int row, int col);
    void FlagCell(int row, int col);
    void Reset();
    int GetSize();
    std::vector<std::vector<char>> GetField();
    int CheckAdjacentMines(int row, int col);

private:;
    int size;
    int mineCount;
    std::vector<std::vector<char>> privField;
    std::vector<std::vector<char>> drawField;
};

#endif // BOARD_H
