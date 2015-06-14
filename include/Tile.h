#ifndef TILE_H
#define TILE_H

#include <string>

class Tile
{
    public:
        Tile();
        Tile(int id, unsigned texId);
        virtual ~Tile();

        unsigned getTextureId() { return texId; }
    protected:
    private:
        int id;
        unsigned texId;
};

#endif // TILE_H
