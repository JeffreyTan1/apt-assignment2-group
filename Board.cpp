#include <iostream>
#include "Tile.h"
#include "Board.h"
#include <vector>

#define COLUMN_MAX 26
#define COLUMN_MIN 1
#define ROW_MAX 25
#define ROW_MIN 0

using std::string;
using std::cout;
using std::endl;


int n = 26;

int m = 27;

string init[26];

Board::Board()
{
    for (int ch = 'a'; ch <= 'z'; ch++)
    {
        init[ch - 'a'] = ::toupper(ch);
    }
    vector<vector<Tile *>> vec(n, vector<Tile *>(m));
    this->board = vec;
}

vector<vector<Tile *>> Board::getBoard()
{
    return this->board;
}

void Board::printBoard()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < m - 1; j++)
        {
            if (i == 0 && j == 0)
            {
                cout << "   " << j << "  ";
            }
            else if (i == 0 && j < 10)
            {
                cout << j << "  ";
            }
            else if (i == 0 && j > 9)
            {
                cout << j << " ";
            }
            else if (i == 1 && j == 0)
            {
                cout << "  -"
                     << "--";
            }
            else if (i == 1 && j == m - 2)
            {
                cout << "----";
            }
            else if (i == 1)
            {
                cout << "---";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++)
    {
        cout << init[i] << " ";
        for (int j = 0; j < m; ++j)
        {
            if (!(board[i][j] == nullptr))
            {
                string ptv = board[i][j]->toString();
                cout << ptv + "|";
            }
            else if (j == 0)
            {
                cout << "|";
            }
            else
            {
                cout << "  |";
            }
        }
        cout << endl;
    }
}

void Board::placeTile(Tile *tile, int row, int col)
{
    if (col > m)
    {
        board[row][col - 1] = tile;
    }
    else
    {
        board[row][col] = tile;
    }
}

Tile *Board::getTileAt(int row, int col)
{
    if (row >= ROW_MIN && col >= COLUMN_MIN && row <= ROW_MAX && col <= COLUMN_MAX)
    {
        return board[row][col];
    }
    else
    {
        return nullptr;
    }
}

std::string Board::getState()
{
    std::string stateString = "";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; ++j)
        {
            if (!(board[i][j] == nullptr))
            {

                stateString = stateString + board[i][j]->toString() + "@" + init[i] + std::to_string(j) + ", ";
            }
        }
    }

    //get rid of last space and comma
    if (stateString.length() > 5)
    {
        stateString.pop_back();
        stateString.pop_back();
    }

    return stateString;
}

bool Board::hasTileAt(int row, int col)
{
    bool hasTile = false;
    if (board[row][col] != nullptr)
    {
        hasTile = true;
    }

    return hasTile;
}
