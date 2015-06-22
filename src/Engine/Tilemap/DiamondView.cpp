#include "DiamondView.h"

DiamondView::DiamondView(TileMap tm, int w, int h) :
    TileMapView(tm, w, h)
{}

DiamondView::~DiamondView()
{
    //dtor
}

void DiamondView::tileWalking(TileOrientation orientation)
{
    int savedX = x,
        savedY = y;

    switch (orientation) {
        case NORTH:
            x--;
            y--;
            break;
        case NORTHEAST:
            y--;
            break;
        case EAST:
            x++;
            y--;
            break;
        case SOUTHEAST:
            x++;
            break;
        case SOUTH:
            x++;
            y++;
            break;
        case SOUTHWEST:
            y++;
            break;
        case WEST:
            x--;
            y++;
            break;
        case NORTHWEST:
            x--;
            break;
        default:
            break;
    }

    if (x >= getTilemapRows() || x < 0 || y >= getTilemapCols() || y < 0) {
        y = savedY;
		x = savedX;
    }
}

void DiamondView::mouseMap()
{
    return;
}

TilePosition DiamondView::calcTilePosition(int x, int y)
{
    this->x = x;
    this->y = y;

    TilePosition tp;

    tp.x = (x * width/2) - (y * width/2);
    tp.y = ((y * height/2) * -1) - (x * height/2);

    return tp;
}

TilePosition DiamondView::screenToTilePosition(int x, int y, int offsetX, int offsetY) {

	int base = (offsetY - (getTilemapCols() * height)) / 2;
	int baseY = y - base;

	base = (offsetX - (getTilemapRows() * width)) / 2;
	int baseX = x - base + 48;

	int w = width / 2;
	int h = height / 2;

	int posX = ((baseX * h) + (baseY * w) - ((getTilemapCols() * w) + w) * h) / 1024;
	int posY = ((baseX * -h) + (baseY * w) + ((getTilemapCols() * w) + w) * h) / 1024;

	TilePosition tp;
	tp.x = posX;
	tp.y = posY;

	return tp;
}
