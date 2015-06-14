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
        const Tile& getTileById(int id) const;
    protected:
    private:
        std::vector<Tile> tileset;
};

#endif // TILESET_H
