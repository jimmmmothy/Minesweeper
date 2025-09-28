#pragma once

struct Size
{
    int x, y;
};

class Board
{
public:
    Board(int sizex, int sizey, int mineCount);
    ~Board();
    void PlaceMines();
    int RevealCell(int row, int col);
    int ChordCell(int row, int col);
    void FlagCell(int row, int col);
    void Reset();
    Size GetSize();
    int GetMineCount();
    char** GetPublicField();
    char** GetPrivField();
    char** GetLosingField();
    int CheckAdjacentMines(int row, int col);
    int CheckAdjacentFlags(int row, int col);

private:;
    Size m_size;
    int m_mineCountTotal;
    int m_mineCountRem;
    int m_freeCountRem;
    char** m_privField;
    char** m_publicField;
    char** InitField();
    void ResetField(char** field);
    void FinishPublicField();
};
