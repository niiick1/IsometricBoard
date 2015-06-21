#include "Model.h"
#include <gl/GL.h>
#include "Tileset.h"
#include "PTMReader.h"
#include <iostream>

Model::Model()
{
}

Model::~Model()
{
    //dtor
}

void Model::addSpriteForDirection(const Sprite& sprite, TileOrientation direction)
{
    sprites[direction] = sprite;
}

void Model::update()
{
    sprites[direction].setCurrentFrame(sprites[direction].getFrameCount() * time);
//    std::cout << time << " and " << sprites[direction].getCurrentFrame() << std::endl;

    walkX = time * walkXFactor;
    walkY = time * walkYFactor;

    if (time >= 1) {
        time = 0;
        walkX = 0;
        walkY = 0;
//        direction = IDLE;
    }
}

void Model::render(int x, int y)
{
    glBindTexture(GL_TEXTURE_2D, sprites[direction].getTextureId());

    glBegin(GL_QUADS);

    Sprite sprite = sprites[direction];

    int currentFrame = sprite.getCurrentFrame(),
        frames = sprite.getFrameCount(),
        width = sprite.getFrameWidth(),
        height = sprite.getFrameHeight();

    float initX = currentFrame * (1.0f / frames),
        endX = (currentFrame + 1) * (1.0f / frames);

//    std::cout << "init: " << initX << " end: " << endX << std::endl;;

    y += walkY;
    x += walkX;

    glTexCoord2f(0 + initX, 0);
    glVertex2f(x, y);

    glTexCoord2f(0 + initX, 1);
    glVertex2f(x, y + height);

    glTexCoord2f(endX, 1);
    glVertex2f(x + width, y + height);

    glTexCoord2f(endX, 0);
    glVertex2f(x + width, y);

    glEnd();
}

void Model::walk(TileOrientation direction)
{
    int TILE_HEIGHT = 32,
        TILE_WIDTH = 64;

    switch (direction) {
        case NORTH:
            walkXFactor = 0;
            walkYFactor = TILE_HEIGHT;
            break;
        case NORTHEAST:
            walkXFactor = TILE_WIDTH/2;
            walkYFactor = TILE_HEIGHT/2;
            break;
        case EAST:
            walkXFactor = TILE_WIDTH;
            walkYFactor = 0;
            break;
        case SOUTHEAST:
            walkXFactor = TILE_WIDTH/2;
            walkYFactor = TILE_HEIGHT/2 * -1;
            break;
        case SOUTH:
            walkXFactor = 0;
            walkYFactor = TILE_HEIGHT * -1;
            break;
        case SOUTHWEST:
            walkXFactor = TILE_WIDTH/2 * -1;
            walkYFactor = TILE_HEIGHT/2 * -1;
            break;
        case WEST:
            walkXFactor = TILE_WIDTH * -1;
            walkYFactor = 0;
            break;
        case NORTHWEST:
            walkXFactor = TILE_WIDTH/2 * -1;
            walkYFactor = TILE_HEIGHT/2;
            break;
        default:
            break;
    }

    this->direction = direction;
}

void Model::setCurrentPosition(const TilePosition& tp)
{
    oldPosition = currentPosition;
    currentPosition = tp;
}


