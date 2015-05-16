#include "RGBAColor.h"

RGBAColor::RGBAColor() : r(0), g(0), b(0), a(255), argb(toARGB())
{}

RGBAColor::RGBAColor(unsigned r, unsigned g, unsigned b, unsigned a)
    : r(r), g(g), b(b), a(a), argb(toARGB())
{}

RGBAColor::RGBAColor(unsigned argb) :
    r(argb >> 16 & 0xff),
    g(argb >> 8 & 0xff),
    b(argb & 0xff),
    a(argb >> 24 & 0xff),
    argb(argb)
{}

RGBAColor::~RGBAColor()
{
    //dtor
}

unsigned RGBAColor::toARGB() {
    return ((this->a << 24) | (this->r << 16) | (this->g << 8) | this->b);
}
