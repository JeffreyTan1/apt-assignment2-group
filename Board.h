#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H
#include <vector>
using std::vector;
#include "Tile.h"


//class Tile;

class Board
{
public:
    Board();
    vector<vector<Tile*>> getBoard();
    void setBoard();
    ~Board();
    void toString();
    void addTile(Tile* tile, std::string colour, int shape);
    void test();

private:
    vector<vector<Tile*>> board;
    Tile* apple= new Tile();


};

#endif // ASSIGN2_NODE_H
