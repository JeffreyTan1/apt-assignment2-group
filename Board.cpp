#include <iostream>
#include "Tile.h"
#include "Board.h"

using std::cout;
using std::endl;
using std::string;

//class Tile;

//contains uppercase letters A to Z
string init[COLS - 1];

Board::Board()
{
    for (int ch = 'a'; ch <= 'z'; ch++)
    {
        init[ch - 'a'] = toupper(ch);
    }
    vector<vector<Tile *>> vec(ROWS, vector<Tile *>(COLS));
    this->board = vec;
}

Board::~Board()
{
    //delete board;
}

vector<vector<Tile *>> Board::getBoard()
{
    return this->board;
}

void Board::printBoard()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < COLS - 1; j++)
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
            else if (i == 1 && j == COLS - 2)
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

    for (int i = 0; i < ROWS; i++)
    {
        cout << init[i] << " ";
        for (int j = 0; j < COLS; ++j)
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
    if (col > COLS)
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

    if (row >= 0 && col >= 1 && row <= ROWS - 1 && col <= COLS - 1)
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

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (!(board[i][j] == nullptr))
            {

                stateString = stateString + board[i][j]->toString() + "@" + init[i] + std::to_string(j) + ", ";
            }
        }
    }

    //get rid of last space and comma
    if (stateString.length() > STATE_TOKEN_LEN)
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
