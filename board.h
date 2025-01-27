#ifndef BOARD_H
#define BOARD_H
#include <vector>

class Board
{
public:
    Board(int size, int mineCount);
    void PlaceMines();
    char RevealCell(int row, int col);
    void FlagCell(int row, int col);
    void Reset();
    int GetSize();

private:;
    int size;
    int mineCount;
    std::vector<int> mineCoords;
};

#endif // BOARD_H
