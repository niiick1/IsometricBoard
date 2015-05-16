#include <Windows.h>
#include <gl\GL.h>
#include <gl\glu.h>
#include <gl\glut.h>

#include "TileMap.h"
#include "DiamondView.h"
#include "RGBAColor.h"

using namespace std;

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = TILE_WIDTH / 2;
const int TILE_ROWS = 4;
const int TILE_COLS = 4;

TileMap tm(TILE_ROWS, TILE_COLS);
DiamondView dv(tm, TILE_WIDTH, TILE_HEIGHT);
RGBAColor tileColorEven(255, 0, 0);
RGBAColor tileColorOdd(200, 0, 0);

void drawDiamond(GLfloat x, GLfloat y, GLfloat width) {
    float height = width / 2;

    glVertex2f(x, height / 2 + y);
    glVertex2f(width / 2 + x, height + y);
    glVertex2f(width + x, height / 2 + y);
    glVertex2f(width / 2 + x, y);
}

void init() {
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

    for (int x = 0; x < TILE_ROWS; x++) {
        for (int y = 0; y < TILE_COLS; y++) {
            if (tm.getTileId(x, y) == 0) {
                color = tileColorEven;
            } else {
                color = tileColorOdd;
            }

            glBegin(GL_POLYGON);
            glColor3ub(color.getR(), color.getG(), color.getB());
            dv.calcTilePosition(x, y);
            drawDiamond(dv.getX(), dv.getY(), TILE_WIDTH);
            glEnd();
        }
    }


    glColor3f(0, 0, 0);
    for (int x = 0; x < TILE_ROWS; x++) {
        for (int y = 0; y < TILE_COLS; y++) {
            glBegin(GL_LINE_LOOP);
            dv.calcTilePosition(x, y);
            drawDiamond(dv.getX(), dv.getY(), TILE_WIDTH);
            glEnd();
        }
    }

    glFlush();
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

    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(400, 300, 400, 300);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -300, 300);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-400, 0, 0);
    glScalef(0.75, 0.75, 1);

    init();

	glutDisplayFunc(render);

    glutMainLoop();

    return 0;
}
