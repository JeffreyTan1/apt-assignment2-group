#include "Board.h"
#include "Tile.h"

Board::Board() 
{
    //TO DO
    
}

Board::~Board() 
{
    //TO DO
    
}

void Board::placeTile(Tile *tile, int row, int col) 
{
    //TO DO
}

Tile* Board::getTileAt(int row, int col) 
{
    //TO DO
    Tile *tile = new Tile('R', 1);
    return tile;
}

bool Board::rowIsEmpty(int row) {
    int i=0;
    bool tileFound = false;
    while(i<=26&&!tileFound) {
        Tile *currentTile = getTileAt(row, i);
        if (currentTile != nullptr) {
            tileFound = true;
        }
        i++;
    }
}
