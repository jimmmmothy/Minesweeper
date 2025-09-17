#pragma once

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
    char** GetDrawField();
    char** GetPrivField();
    char** GetLosingField();
    int CheckAdjacentMines(int row, int col);
    int CheckAdjacentFlags(int row, int col);

private:;
    int sizex;
    int sizey;
    int mineCountTotal;
    int mineCountRem;
    int freeCountRem;
    char** privField;
    char** drawField;
    char** losingField;
    char** InitField();
    void ResetField(char** field);
};
