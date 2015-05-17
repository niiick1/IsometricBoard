#include "TileMapView.h"

TileMapView::TileMapView(TileMap tm, int w, int h) :
    width(w), height(h), x(0), y(0), tilemap(tm)
{
    //ctor
}

TileMapView::~TileMapView()
{
    //dtor
}
