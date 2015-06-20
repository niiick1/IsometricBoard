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

void Model::loadTextureFromFile(std::string file)
{
    PTMReader ptm;

    Image* img = ptm.readFile(file);
    unsigned textureID = 0;

    width = img->getWidth() / 9;
    height = img->getHeight();

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, img->getPixels());

    texId = textureID;

    delete img;
}

void Model::update()
{
    currentFrame = 9 * time;
//    std::cout << time << " and " << currentFrame << std::endl;
//    if (++currentFrame >= frames) {
//        currentFrame = 0;
//    }

    walkX = time * walkXFactor;
    walkY = time * walkYFactor;

    if (time >= 1) {
        time = 0;
        walkX = 0;
        walkY = 0;
    }
}

void Model::render(int x, int y)
{
    glBegin(GL_QUADS);

    float initX = currentFrame * (1.0f/9.0f),
        endX = (currentFrame + 1) * (1.0f/9.0f);

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
}

void Model::setCurrentPosition(const TilePosition& tp)
{
    oldPosition = currentPosition;
    currentPosition = tp;
}


