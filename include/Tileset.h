#ifndef TILESET_H
#define TILESET_H

#include <vector>
#include <string>
#include "Tile.h"

class Tileset
{
    public:
        Tileset();
        virtual ~Tileset();

        void addTileFromFile(std::string file);
        Tile getTileById(int id);
    protected:
    private:
        std::vector<Tile> tileset;
};

#endif // TILESET_H
