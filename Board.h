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


    void placeTile(Tile *tile, int row, int col);
    Tile* getTileAt(int row, int col);
    std::string getState();
    bool hasTileAt(int row, int col);

private:
    vector<vector<Tile *>>
        board;
    Tile *apple = new Tile();
};

#endif // ASSIGN2_BOARD_H
