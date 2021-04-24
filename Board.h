#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <vector>
using std::vector;

class Tile;

class Board
{
public:
    Board();

    ~Board();

private:
    vector<vector<Tile>> board;
};

#endif // ASSIGN2_NODE_H
