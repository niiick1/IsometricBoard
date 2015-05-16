#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include "Tileset.h"

class TileMap
{
    public:
        TileMap(int rows, int cols);
        virtual ~TileMap();

        int getTileId(int x, int y);

        void loadTilemap();
    protected:
    private:
        int rows,
            cols;

        std::vector< std::vector<unsigned short> > map;
};

#endif // TILEMAP_H
