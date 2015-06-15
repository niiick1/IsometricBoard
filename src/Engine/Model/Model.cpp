#include "Model.h"
#include <gl/GL.h>
#include "Tileset.h"
#include "PTMReader.h"

Model::Model()
{
    texCoord[0] = new float[8] {
            0.0f, 1.0f,
            0.0f, 0.0f,
            0.33f, 0.0f,
            0.33f, 1.0f
        };

    texCoord[1] = new float[8]
        {
            0.33f, 1.0f,
            0.33f, 0.0f,
            0.66f, 0.0f,
            0.66f, 1.0f
        };

    texCoord[2] = new float[8]
        {
            0.66f, 1.0f,
            0.66f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f
        };
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
    if (++currentFrame >= frames) {
        currentFrame = 0;
    }
}

void Model::render(int x, int y)
{
    glBegin(GL_QUADS);

    float initX = currentFrame * (1.0f/9.0f),
        endX = (currentFrame + 1) * (1.0f/9.0f);

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
