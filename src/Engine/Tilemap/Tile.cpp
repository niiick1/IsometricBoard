#include "Tile.h"
#include "PTMReader.h"
#include "Image.h"

Tile::Tile() : id(0)
{}

Tile::Tile(int id) : id(id)
{}

Tile::Tile(const Tile& tile)
{
    id = tile.id;
    img = new Image(*tile.img);
}

Tile::~Tile()
{
    delete img;
}

void Tile::loadPTMImageFromFile(std::string file)
{
    PTMReader ptm;
    img = ptm.readFile(file);
}
