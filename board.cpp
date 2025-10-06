#include "board.h"
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <queue>
#include <set>

Board::Board(int sizex, int sizey, int mineCount) : m_size({sizex, sizey}), m_mineCountTotal(mineCount), m_mineCountRem(mineCount)
{
    m_privField = InitField();
    m_publicField = InitField();
    m_freeCountRem = sizex * sizey - mineCount;
}

Board::~Board()
{
    delete m_privField;
    delete m_publicField;
}

char** Board::InitField()
{
    char** field = new char*[m_size.x];
    for (int row = 0; row < m_size.x; ++row) 
    {
        field[row] = new char[m_size.y];
        for (int col = 0; col < m_size.y; ++col) 
        {
            field[row][col] = '.';
        }
    }

    return field;
}

void Board::ResetField(char** field)
{
    for (int row = 0; row < m_size.x; ++row) 
    {
        for (int col = 0; col < m_size.y; ++col) 
        {
            field[row][col] = '.';
        }
    }
}

void Board::FinishPublicField()
{
    for (int row = 0; row < m_size.x; ++row) 
    {
        for (int col = 0; col < m_size.y; ++col) 
        {
            if (m_privField[row][col] == 'M' && m_publicField[row][col] == '.')
                m_publicField[row][col] = 'F';
        }
    }

    m_mineCountRem = 0;
}

Size Board::GetSize()
{
    return m_size;
}

int Board::GetMineCount()
{
    return m_mineCountRem;
}

void Board::Reset()
{
    ResetField(m_privField);
    ResetField(m_publicField);
    m_mineCountRem = this->m_mineCountTotal;
    m_freeCountRem = m_size.x * m_size.y - m_mineCountTotal;
}

void Board::PlaceMines(int row, int col) // Don't place mines around clicked cell
{
    const std::size_t totalCells = m_size.x * m_size.y;
    std::vector<int> pool(totalCells);
    
    std::pair<int, int> directions[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {0, 0},  {1, -1}, {1, 0}, {1, 1}};
    int indexes[9];

    for (int i = 0; i < 9; i++) {
        int newRow = row + directions[i].first;
        int newCol = col + directions[i].second;
        int idOneDimension = newCol + newRow * m_size.y;

        if (newRow >= 0 && newRow < m_size.x && newCol >= 0 && newCol < m_size.y) 
        {
            indexes[i] = idOneDimension;
        }
        else 
        {
            indexes[i] = -1;
        }
    }

    std::iota(pool.begin(), pool.end(), 0);
    for (int i = 8; i >= 0; i--) 
    {
        if (indexes[i] != -1)
        {    
            pool.erase(pool.begin() + indexes[i]);
        }
    }

    std::srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < this->m_mineCountTotal; i++) 
    {
        int randI = std::rand() % (pool.size());
        int cell = pool[randI];
        int col = cell % m_size.y;
        int row = cell / m_size.y;
        m_privField[row][col] = 'M';
        pool.erase(pool.begin() + randI);
    }
}

char** Board::GetPublicField()
{
    return m_publicField;
}

char** Board::GetLosingField()
{
    for (int row = 0; row < m_size.x; ++row) 
    {
        for (int col = 0; col < m_size.y; ++col) 
        {
            if (m_publicField[row][col] == '.' && m_privField[row][col] == 'M')
            {
                m_publicField[row][col] = 'M';
            }
            else if (m_publicField[row][col] == 'F' && m_privField[row][col] != 'M')
            {
                m_publicField[row][col] = 'X';
            }
        }
    }

    return m_publicField;
}

char** Board::GetPrivField()
{
    return m_privField;
}

int Board::RevealCell(int row, int col, bool isFirstClick) 
{
    if (isFirstClick)
    {
        PlaceMines(row, col);
    }

    if (m_publicField[row][col] != '.') 
    {
        return this->ChordCell(row, col);
    }

    if (m_privField[row][col] == 'M') 
    {
        m_publicField[row][col] = 'B';
        return -1;
    }

    std::queue<std::pair<int, int>> toReveal;
    std::set<std::pair<int, int>> visited;
    toReveal.push({row, col});
    visited.insert({row, col});

    while (!toReveal.empty()) {
        auto [r, c] = toReveal.front();
        toReveal.pop();

        m_publicField[r][c] = '0';
        m_freeCountRem--;

        int adjacentMines = CheckAdjacentMines(r, c);
        if (adjacentMines > 0) 
        {
            m_publicField[r][c] = '0' + adjacentMines;
            continue;
        }

        std::pair<int, int> directions[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

        for (int i = 0; i < 8; i++) 
        {
            int newRow = r + directions[i].first;
            int newCol = c + directions[i].second;

            if (newRow >= 0 && newRow < m_size.x && newCol >= 0 && newCol < m_size.y) 
            {
                if (visited.count({newRow, newCol}) == 0 && m_privField[newRow][newCol] != 'M' && m_publicField[newRow][newCol] == '.') 
                {
                    toReveal.push({newRow, newCol});
                    visited.insert({newRow, newCol});
                }
            }
        }
    }

    if (m_freeCountRem == 0)
    {
        FinishPublicField();
        return 2;
    }

    return 1;
}

int Board::ChordCell(int row, int col)
{
    if (m_publicField[row][col] == ' ')
        return 0;

    // Check if is satisfied
    int revealedNum = m_publicField[row][col] - '0';
    if (CheckAdjacentFlags(row, col) != revealedNum)
        return 0;

    // If yes: chord (open all cells surrounding)
    std::pair<int, int> directions[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    bool foundMine = false;
    bool gameWon = false;

    for (int i = 0; i < 8; i++) 
    {
        int newRow = row + directions[i].first;
        int newCol = col + directions[i].second;

        if (newRow >= 0 && newRow < m_size.x && newCol >= 0 && newCol < m_size.y) 
        {
            if (m_publicField[newRow][newCol] == '.') 
            {
                int res = RevealCell(newRow, newCol, false);
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
    if (m_publicField[row][col] == '.') 
    {
        m_publicField[row][col] = 'F';
        m_mineCountRem--;
    }
    else if (m_publicField[row][col] == 'F') 
    {
        m_publicField[row][col] = '.';
        m_mineCountRem++;
    }
}

int Board::CheckAdjacentMines(int row, int col)
{
    int mines = 0;
    std::pair<int, int> directions[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < 8; i++) {
        int newRow = row + directions[i].first;
        int newCol = col + directions[i].second;

        if (newRow >= 0 && newRow < m_size.x && newCol >= 0 && newCol < m_size.y) {
            if (m_privField[newRow][newCol] == 'M') {
                mines++;
            }
        }
    }

    return mines;
}

int Board::CheckAdjacentFlags(int row, int col)
{
    int flags = 0;
    std::pair<int, int> directions[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int i = 0; i < 8; i++) {
        int newRow = row + directions[i].first;
        int newCol = col + directions[i].second;

        if (newRow >= 0 && newRow < m_size.x && newCol >= 0 && newCol < m_size.y) {
            if (m_publicField[newRow][newCol] == 'F') {
                flags++;
            }
        }
    }

    return flags;
}
