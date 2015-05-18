#include <Windows.h>
#include <gl\GL.h>
#include <gl\glu.h>
#include <gl\glut.h>

#include "TileMap.h"
#include "DiamondView.h"
#include "RGBAColor.h"
#include <vector>

using namespace std;

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = TILE_WIDTH / 2;
const int TILE_ROWS = 17;
const int TILE_COLS = 16;

TileMap tm(TILE_ROWS, TILE_COLS);
DiamondView dv(tm, TILE_WIDTH, TILE_HEIGHT);
RGBAColor tileColorEven(255, 0, 0);
RGBAColor tileColorOdd(200, 0, 0);
RGBAColor tileColorSelected(76, 241, 31);
RGBAColor tileBorderColor(127, 0, 0);
vector<RGBAColor> colorSet = {tileColorEven, tileColorOdd};

struct Cursor {
    int x = 0,
        y = 0;
};

Cursor cursor;

void drawDiamond(GLfloat x, GLfloat y, GLfloat width) {
    float height = width / 2;

    glVertex2f(x, height / 2 + y);
    glVertex2f(width / 2 + x, height + y);
    glVertex2f(width + x, height / 2 + y);
    glVertex2f(width / 2 + x, y);
}

void init() {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -300, 300);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-400, 0, 0);
    glScalef(0.75, 0.75, 1);

    tm.loadTilemap();
    Tileset set;
    set.addTileFromFile("resources/tiles/0.ptm");
    set.addTileFromFile("resources/tiles/1.ptm");
    set.addTileFromFile("resources/tiles/2.ptm");
    set.addTileFromFile("resources/tiles/3.ptm");

    dv.setTileset(set);
}

void render(void) {
    RGBAColor color;
    TilePosition tp;

    for (int x = 0; x < TILE_ROWS; x++) {
        for (int y = 0; y < TILE_COLS; y++) {
            color = colorSet.at(tm.getTileId(x, y));

            glBegin(GL_POLYGON);
            glColor3ub(color.getR(), color.getG(), color.getB());
            tp = dv.calcTilePosition(x, y);
            drawDiamond(tp.x, tp.y, TILE_WIDTH);
            glEnd();
        }
    }

    color = tileColorSelected;

    glBegin(GL_POLYGON);
    glColor3ub(color.getR(), color.getG(), color.getB());
    tp = dv.calcTilePosition(cursor.x, cursor.y);
    drawDiamond(tp.x, tp.y, TILE_WIDTH);
    glEnd();

    color = tileBorderColor;
    glColor3ub(color.getR(), color.getG(), color.getB());
    for (int x = 0; x < TILE_ROWS; x++) {
        for (int y = 0; y < TILE_COLS; y++) {
            glBegin(GL_LINE_LOOP);
            tp = dv.calcTilePosition(x, y);
            drawDiamond(tp.x, tp.y, TILE_WIDTH);
            glEnd();
        }
    }

    glFlush();
}

void handleKeyboard(unsigned char key, int x, int y) {
    dv.calcTilePosition(cursor.x, cursor.y);

    switch (key) {
        case 'w':
            dv.tileWalking(NORTH);
            break;
        case 'a':
            dv.tileWalking(WEST);
            break;
        case 's':
            dv.tileWalking(SOUTH);
            break;
        case 'd':
            dv.tileWalking(EAST);
            break;
        case 'q':
            dv.tileWalking(NORTHWEST);
            break;
        case 'e':
            dv.tileWalking(NORTHEAST);
            break;
        case 'z':
            dv.tileWalking(SOUTHWEST);
            break;
        case 'c':
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
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
