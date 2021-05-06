#include "Tile.h"

Tile::Tile()
{
    colour = NULL;
    shape = NULL;
}
Tile::Tile(char colour, int shape)
{
    this->colour = colour;
    this->shape = shape;
}

Tile::Tile()
{
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

std::string Tile::toString(Tile *tile)
{
    std::string retval = tile->colour + std::to_string(tile->shape);
    return retval;
}

bool Tile::isValid()
{
    return true;
}
