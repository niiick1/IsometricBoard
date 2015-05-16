#ifndef DIAMONDVIEW_H
#define DIAMONDVIEW_H

#include "TileMapView.h"

class DiamondView : public TileMapView
{
    public:
        DiamondView(TileMap tm, int w, int h);
        virtual ~DiamondView();

        void tileWalking();
        void mouseMap();
        void calcTilePosition(int x, int y);

    protected:
    private:
};

#endif // DIAMONDVIEW_H
