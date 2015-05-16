#ifndef TILEMAPVIEW_H
#define TILEMAPVIEW_H

#include "TileMap.h"
#include "Tileset.h"

class TileMapView
{
    public:
        TileMapView(TileMap tm, int w, int h);
        virtual ~TileMapView();

        virtual void tileWalking() = 0;
        virtual void mouseMap() = 0;
        virtual void calcTilePosition(int x, int y) = 0;

        void setTileset(Tileset ts) { tileset = ts; }

        const int& getX() { return x; }
        const int& getY() { return y; }

    protected:
        int width,
            height,
            x,
            y;

    private:
        TileMap tilemap;
        Tileset tileset;
};

#endif // TILEMAPVIEW_H
