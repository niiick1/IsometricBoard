#include "DiamondView.h"

DiamondView::DiamondView(TileMap tm, int w, int h) :
    TileMapView(tm, w, h)
{
    //ctor
}

DiamondView::~DiamondView()
{
    //dtor
}

void DiamondView::tileWalking()
{
    return;
}

void DiamondView::mouseMap()
{
    return;
}

void DiamondView::calcTilePosition(int x, int y)
{
//    this->x = x * width + y * (width/2);
//    this->y = y * (height/2);
    this->x = (x * width/2) + (y * width/2);
    this->y = (y * height/2) - (x * height/2);
}
