#ifndef TILE_H
#define TILE_H

#include <string>
#include "Image.h"

class Tile
{
    public:
        Tile();
        Tile(int id);
        Tile(const Tile& tile);
        virtual ~Tile();

        void loadPTMImageFromFile(std::string file);
    protected:
    private:
        int id;
        Image* img;
};

#endif // TILE_H
