#ifndef TILEMAPVIEW_H
#define TILEMAPVIEW_H

#include "TileMap.h"
#include "Tileset.h"
#include "TilePosition.h"

enum TileOrientation {
    NORTH, NORTHEAST, EAST, SOUTHEAST,
    SOUTH, SOUTHWEST, WEST, NORTHWEST
};

class TileMapView
{
    public:
        TileMapView(TileMap tm, int w, int h);
        virtual ~TileMapView();

        virtual void tileWalking(TileOrientation) = 0;
        virtual void mouseMap() = 0;
        virtual TilePosition calcTilePosition(int x, int y) = 0;

        void setTileset(Tileset ts) { tileset = ts; }

        int getX() const { return x; }
        int getY() const { return y; }
        int getTilemapRows() { return tilemap.getRows(); }
        int getTilemapCols() { return tilemap.getCols(); }

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
