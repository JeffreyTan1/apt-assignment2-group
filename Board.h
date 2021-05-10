#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H
#include <vector>
using std::vector;
#include "Tile.h"
#include <string>
//class Tile;

class Board
{
public:
    Board();
    vector<vector<Tile *>> getBoard();
    void setBoard();
    ~Board();
    void printBoard();
    void addTile(Tile *tile, std::string colour, int shape);

    void placeTile(Tile *tile, int row, int col);
    Tile* getTileAt(int row, int col);
    bool lineIsEmpty(int line, bool isRow);
    bool lineContains(Tile *tile, int line, bool isRow);
    bool rowIsEmpty(int row);
    std::string getState();
    bool hasTileAt(int row, int col);

private:
    vector<vector<Tile *>>
        board;
    Tile *apple = new Tile();
};

#endif // ASSIGN2_BOARD_H
