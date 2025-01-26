#ifndef BOARD_H
#define BOARD_H
#include <vector>

class Board
{
public:
    Board(int size, int mineCount);
    void PlaceMines();
    void RevealCell(int x, int y);
    void FlagCell(int x, int y);
    std::vector<std::vector<char>> GetField();

private:;
    int size;
    std::vector<std::vector<char>> field;
    int mineCount;
};

#endif // BOARD_H
