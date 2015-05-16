#include "Image.h"
#include <iostream>

Image::Image(int w, int h) :
    width(w), height(h), pixels(new unsigned[w*h])
{}

Image::Image(const Image& img) {
    this->height = img.height;
    this->width = img.width;
    this->pixels = new unsigned[this->width*this->height];

    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            unsigned pos = x+y*this->width;
            this->pixels[pos] = img.pixels[pos];
        }
    }
}

void Image::setPixel(unsigned argb, int x, int y)
{
    pixels[x+y*this->width] = argb;
}

Image::~Image()
{
    delete this->pixels;
}
