#include "TileMap.h"
#include "DiamondView.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

TileMap::TileMap(int rows, int cols)
    : rows(rows), cols(cols),
    map(rows, std::vector<unsigned short>(cols))
{}

TileMap::~TileMap()
{}

int TileMap::getTileId(int x, int y)
{
    return map.at(x).at(y);
}

void TileMap::loadTilemap(std::string file)
{
    ifstream arq(file.c_str());

    if (arq.fail()) {
        cout << "Error opening file " << file << endl;
        return;
    }

    string buffer;

    arq >> buffer;

    string width,
        height;

    size_t strAt;

    while (!arq.eof()) {
        arq >> buffer;

        if (width.empty()) {
            strAt = buffer.find("width=");
            if (strAt != std::string::npos) {
                width = buffer.substr(strAt + 6, buffer.length());
            }
        }
        else {
            if (height.empty()) {
                strAt = buffer.find("height=");
                if (strAt != string::npos) {
                    height = buffer.substr(strAt + 7, buffer.length());
                }
            } else {
                // Ignoring max value
                break;
            }
        }
    }

    unsigned w = stoi(width),
            h = stoi(height);

    cout << w << " and " << h << endl;

    // Ignore next 10 lines
    for (int a = 0; a < 10; a++) {
        arq >> buffer;
    }

    for (int x = 0; x < h; x++) {
        arq >> buffer;

        for (int y = 0; y < w; y++) {
            string pos = buffer.substr(y * 2, 1);
            map[x][y] = stoi(pos) - 1;
            cout << pos;
        }

        cout << endl;
    }
}

