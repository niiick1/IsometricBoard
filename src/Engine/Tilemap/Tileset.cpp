#include "Tileset.h"

Tileset::Tileset()
{}

Tileset::~Tileset()
{}

void Tileset::addTileFromFile(std::string file)
{
    Tile t(tileset.size());
    t.loadPTMImageFromFile(file);

    tileset.push_back(t);
}

const Tile& Tileset::getTileById(int id) const
{
    return tileset.at(id);
}
