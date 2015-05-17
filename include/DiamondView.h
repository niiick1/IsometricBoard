#ifndef DIAMONDVIEW_H
#define DIAMONDVIEW_H

#include "TileMapView.h"

class DiamondView : public TileMapView
{
    public:
        DiamondView(TileMap tm, int w, int h);
        virtual ~DiamondView();

        void tileWalking(TileOrientation);
        void mouseMap();
        TilePosition calcTilePosition(int x, int y);

    protected:
    private:
};

#endif // DIAMONDVIEW_H
