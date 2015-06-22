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
		TilePosition screenToTilePosition(int x, int y, int offsetX, int offsetY);

    protected:
    private:
};

#endif // DIAMONDVIEW_H
