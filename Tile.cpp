#include "Tile.h"

Tile::Tile() {
    colour = NULL;
    shape = NULL;
}
Tile::Tile(char colour, int shape)
{
    this->colour = colour;
    this->shape = shape;
}

bool Tile::equals(Tile *tile)
{
    bool equal = false;
    if (this->colour == tile->colour && this->shape == tile->shape)
    {
        equal = true;
    }
    return equal;
}
