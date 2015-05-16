#include "TileMap.h"
#include "DiamondView.h"

TileMap::TileMap(int rows, int cols)
    : rows(rows), cols(cols),
    map(rows, std::vector<unsigned short>(cols))
{}

TileMap::~TileMap()
{}

int TileMap::getTileId(int x, int y)
{
    return map.at(x).at(y);
}

void TileMap::loadTilemap()
{
    map = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
}

