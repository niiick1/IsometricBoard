#include <gl/GL.h>
#include "Tileset.h"
#include "PTMReader.h"
#include <iostream>

Tileset::Tileset()
{}

Tileset::~Tileset()
{}

void Tileset::addTileFromFile(std::string file)
{
    PTMReader ptm;

    Image* img = ptm.readFile(file);
    unsigned textureID = 0;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    std::cout << "Created texture " << textureID << std::endl;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, img->getPixels());

    Tile t(tileset.size(), textureID);

    tileset.push_back(t);

    delete img;
}

const Tile& Tileset::getTileById(int id) const
{
    return tileset.at(id);
}
