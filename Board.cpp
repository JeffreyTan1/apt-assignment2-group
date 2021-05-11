#include <iostream>
#include "Tile.h"
#include "Board.h"
#include <vector>

using namespace std;

//class Tile;
int n = 26;

int m = 27;

string init[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W",
                   "X", "Y", "Z"};
Tile *testy = new Tile('z', 5);
//vector<vector<Tile*>> vec(n, vector<Tile*>(m));

Board::Board()
{
    string init[6] = {"A", "B", "C", "D", "E", "F"};
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
            else if (i == 0)
            {
                cout << j << "  ";
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

// //place g5 at c4
// void Board::addTile(Tile *tile, string posX, int posY)
// {
//     int position = 0;
//     for (int i = 0; i < 6; ++i)
//     {
//         if (posX == init[i])
//         {
//             position = i;
//         }
//     }
//     board[position][posY] = tile;
// }

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
    if (row >= 0 && col >= 1 && row < 25 && col < 26)
    {
        return board[row][col];
    }
    else
    {
        return nullptr;
    }
}

bool Board::lineIsEmpty(int line, bool isRow)
{
    int i = 0;
    bool tileFound = false;
    Tile *currentTile = nullptr;
    while (i <= 26 && !tileFound)
    {
        if (isRow)
        {
            currentTile = getTileAt(line, i);
        }
        else
        {
            currentTile = getTileAt(i, line);
        }
        if (currentTile != nullptr)
        {
            tileFound = true;
        }
        i++;
    }
    return tileFound;
}

bool Board::lineContains(Tile *tile, int line, bool isRow)
{
    int i = 0;
    bool tileFound = false;
    Tile *currentTile = nullptr;
    while (i <= 26 && !tileFound)
    {
        if (isRow)
        {
            currentTile = getTileAt(line, i);
        }
        else
        {
            currentTile = getTileAt(i, line);
        }
        if (currentTile->equals(tile))
        {
            tileFound = true;
        }
        i++;
    }
    return tileFound;
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
                if (!(i == n - 1 && j == m - 1))
                {
                    stateString = stateString + board[i][j]->toString() + "@" + init[n] + std::to_string(m) + ", ";
                }
                else
                {
                    stateString = stateString + board[i][j]->toString() + "@" + init[n] + std::to_string(m);
                }
            }
        }
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
