#include <Windows.h>
#include <gl/GL.h>
#include "Sprite.h"
#include "PTMReader.h"

Sprite::Sprite()
{
    //ctor
}

Sprite::~Sprite()
{
    //dtor
}

Sprite::Sprite(std::string file, int frames)
{
    loadTextureFromFile(file, frames);
}

void Sprite::loadTextureFromFile(std::string file, int frames)
{
    PTMReader ptm;

    Image* img = ptm.readFile(file);
    unsigned textureID = 0;

    this->frames = frames;
    frameWidth = img->getWidth() / frames;
    frameHeight = img->getHeight();

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, img->getPixels());

    texId = textureID;

    delete img;
}

