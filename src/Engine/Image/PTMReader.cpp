#include "PTMReader.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

PTMReader::PTMReader()
{
    //ctor
}

Image* PTMReader::readFile(string file)
{
    ifstream arq(file.c_str());

    if (arq.fail()) {
        cout << "Error opening file " << file << endl;
        return nullptr;
    }

    string buffer;

    arq >> buffer;

    string type = buffer.substr(0, 2),
        width,
        height;

    if (type == "P7") {
        cout << "P7 image detected.\n";
    } else {
        cout << "Image " << file << " is not on P7 format." << endl;
    }

    while (!arq.eof()) {
        arq >> buffer;

        if (buffer[0] == '#') continue;

        if (width.empty()) {
            width = buffer;
        }
        else {
            if (height.empty()) {
                height = buffer;
            } else {
                // Ignoring max value
                break;
            }
        }
    }

    unsigned w = stoi(width),
        h = stoi(height);

    Image* img = new Image(w, h);

    unsigned argb = 0,
        x = 0,
        y = h - 1; // OpenGL coord system have the y on bottom left. Need to adapt to the image

    while (!arq.eof()) {
        for (int c = 0; c < 4; c++) {
            arq >> buffer;
            argb |= (stoi(buffer) << (24 - 8*c));
        }

        img->setPixel(argb, x, y);

        if (++x >= w) {
            x = 0;

            if (y == 0) {
                // Last info was read. Read again so it falls on the EOF.
                arq >> buffer;
            } else {
                y--;
            }
        }

        argb = 0;
    }

    arq.close();

    return img;
}

PTMReader::~PTMReader()
{
    //dtor
}
