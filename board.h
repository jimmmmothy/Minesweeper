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
    char** GetPublicField();
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
    char** publicField;
    char** losingField;
    char** InitField();
    void ResetField(char** field);
    void FinishPublicField();
};
