#include "Tile.h"
#include "TileCodes.h"

Tile::Tile()
{
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

std::string Tile::toString()
{
    std::string retval = colour + std::to_string(shape);
    return retval;
}
