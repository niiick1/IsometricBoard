#include "Tile.h"

Tile::Tile() :
    id(0), texId(0)
{}

Tile::Tile(int id, unsigned texId) :
    id(id), texId(texId)
{}

Tile::~Tile()
{}
