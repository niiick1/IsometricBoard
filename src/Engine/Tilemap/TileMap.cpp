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
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            map[x][y] = (x+y) % 2;
        }
    }
}

