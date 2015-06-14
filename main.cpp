#include <Windows.h>
#include <gl/GL.h>
#include <gl/glu.h>
#include <gl/glut.h>

#include "TileMap.h"
#include "DiamondView.h"
#include "RGBAColor.h"
#include <vector>
#include "PTMReader.h"
#include <iostream>

using namespace std;

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = TILE_WIDTH / 2;
const int TILE_ROWS = 57;
const int TILE_COLS = 56;

TileMap tm(TILE_ROWS, TILE_COLS);
DiamondView dv(tm, TILE_WIDTH, TILE_HEIGHT);
RGBAColor tileColorEven(255, 0, 0);
RGBAColor tileColorOdd(200, 0, 0);
RGBAColor tileColorSelected(76, 241, 31);
//RGBAColor tileColorSelected(255, 255, 255);
RGBAColor tileBorderColor(0, 0, 0);
vector<RGBAColor> colorSet = {tileColorEven, tileColorOdd};

GLuint textureID;

struct Cursor {
    int x = 5,
        y = 5;
};

Cursor cursor;
PTMReader ptm;
Tileset set;

void drawDiamond(GLfloat x, GLfloat y, GLfloat width) {
    GLfloat height = width / 2;

    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(x, height / 2 + y);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(height + x, height + y);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(width + x, height / 2 + y);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(height + x, y);
}

void drawCharacter(GLfloat x, GLfloat y) {
    int width = 45,
        height = 95;

    float tempX = (TILE_WIDTH - width)/2,
        tempY = (TILE_HEIGHT - height)/2;

    if (tempX > 0) x += tempX;

    y += tempX/2;

    cout << x << ", " << y << endl;

    glTexCoord2f(0, 0);
    glVertex2f(x, y);

    glTexCoord2f(0, 1);
    glVertex2f(x, y + height);

    glTexCoord2f(1, 1);
    glVertex2f(x + width, y + height);

    glTexCoord2f(1, 0);
    glVertex2f(x + width, y);
}

void drawPoring(GLfloat x, GLfloat y) {
    int width = 39,
        height = 33;


    float tempX = (TILE_WIDTH - width)/2,
        tempY = (TILE_HEIGHT - height)/2;

    if (tempX > 0) x += tempX;
    y += tempX/2;

    glTexCoord2f(0, 0);
    glVertex2f(x, y);

    glTexCoord2f(0, 1);
    glVertex2f(x, y + height);

    glTexCoord2f(1, 1);
    glVertex2f(x + width, y + height);

    glTexCoord2f(1, 0);
    glVertex2f(x + width, y);
}

void init() {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -300, 300);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-400, 0, 0);
//    glScalef(1, 1, 1);

    tm.loadTilemap();

    set.addTileFromFile("resources/tiles/grass.ptm");
    set.addTileFromFile("resources/tiles/ground.ptm");
    set.addTileFromFile("resources/tiles/poring11.ptm");
    set.addTileFromFile("resources/tiles/assassin1.ptm");
}

void render(void) {
    RGBAColor color;
    TilePosition tp;

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    for (int x = 0; x < TILE_ROWS; x++) {
        for (int y = 0; y < TILE_COLS; y++) {
            Tile tile = set.getTileById(tm.getTileId(x, y));

            glBindTexture(GL_TEXTURE_2D, tile.getTextureId());

            glBegin(GL_QUADS);
            tp = dv.calcTilePosition(x, y);
            drawDiamond(tp.x, tp.y, TILE_WIDTH);
            glEnd();
        }
    }

    glDisable(GL_TEXTURE_2D);

//    color = tileColorSelected;
//
//    glBegin(GL_POLYGON);
//    glColor3ub(color.getR(), color.getG(), color.getB());
    tp = dv.calcTilePosition(cursor.x, cursor.y);
//    drawDiamond(tp.x, tp.y, TILE_WIDTH);
//    glEnd();

    glEnable(GL_TEXTURE_2D);

    Tile tile1 = set.getTileById(2);
    glBindTexture(GL_TEXTURE_2D, tile1.getTextureId());

    glBegin(GL_QUADS);
    dv.calcTilePosition(cursor.x, cursor.y);
    dv.tileWalking(NORTHWEST);
    TilePosition tpPoring = dv.calcTilePosition(dv.getX(), dv.getY());
    drawPoring(tpPoring.x, tpPoring.y);
    glEnd();

    glBegin(GL_QUADS);
    dv.calcTilePosition(cursor.x, cursor.y);
    dv.tileWalking(NORTHEAST);
    tpPoring = dv.calcTilePosition(dv.getX(), dv.getY());
    drawPoring(tpPoring.x, tpPoring.y);
    glEnd();

    Tile tile = set.getTileById(3);
    glBindTexture(GL_TEXTURE_2D, tile.getTextureId());

    glBegin(GL_QUADS);
    drawCharacter(tp.x, tp.y);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, tile1.getTextureId());

    glBegin(GL_QUADS);
    dv.calcTilePosition(cursor.x, cursor.y);
    dv.tileWalking(SOUTHWEST);
    tpPoring = dv.calcTilePosition(dv.getX(), dv.getY());
    drawPoring(tpPoring.x, tpPoring.y);
    glEnd();

    glBegin(GL_QUADS);
    dv.calcTilePosition(cursor.x, cursor.y);
    dv.tileWalking(SOUTHEAST);
    tpPoring = dv.calcTilePosition(dv.getX(), dv.getY());
    drawPoring(tpPoring.x, tpPoring.y);
    glEnd();

    glFlush();
}

void handleKeyboard(unsigned char key, int x, int y) {
    dv.calcTilePosition(cursor.x, cursor.y);

    switch (key) {
        case 'w':
        case 'W':
            dv.tileWalking(NORTH);
            glTranslatef(0, -1* TILE_HEIGHT, 0);
            break;
        case 'a':
        case 'A':
            dv.tileWalking(WEST);
            glTranslatef(TILE_WIDTH, 0, 0);
            break;
        case 's':
        case 'S':
            dv.tileWalking(SOUTH);
            glTranslatef(0, TILE_HEIGHT, 0);
            break;
        case 'd':
        case 'D':
            dv.tileWalking(EAST);
            glTranslatef(-1 * TILE_WIDTH, 0, 0);
            break;
        case 'q':
        case 'Q':
            dv.tileWalking(NORTHWEST);
            break;
        case 'e':
        case 'E':
            dv.tileWalking(NORTHEAST);
            break;
        case 'z':
        case 'Z':
            dv.tileWalking(SOUTHWEST);
            break;
        case 'c':
        case 'C':
            dv.tileWalking(SOUTHEAST);
            break;
        default:
            break;
    }

    cursor.x = dv.getX();
    cursor.y = dv.getY();

    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);

    int windowX = (glutGet(GLUT_SCREEN_WIDTH) - 800)/2,
        windowY = (glutGet(GLUT_SCREEN_HEIGHT) - 600)/2;

    glutInitWindowPosition(windowX, windowY);
    glutCreateWindow("Teste");

    init();

    glutKeyboardFunc(handleKeyboard);
	glutDisplayFunc(render);

    glutMainLoop();

    return 0;
}
