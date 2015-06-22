#include <Windows.h>
#include <gl/GL.h>
#include <gl/glu.h>
#include <GL\freeglut.h>

#include "TileMap.h"
#include "DiamondView.h"
#include <vector>
#include "PTMReader.h"
#include "Model.h"
#include "Sprite.h"
#include <iostream>
#include <queue>

using namespace std;

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = TILE_WIDTH / 2;
const int TILE_ROWS = 13;
const int TILE_COLS = 12;
const int MAP_WIDTH = 800;
const int MAP_HEIGHT = 600;

TileMap tm(TILE_ROWS, TILE_COLS);
DiamondView dv(tm, TILE_WIDTH, TILE_HEIGHT);

PTMReader ptm;
Tileset set;
Model model;
Model female;
queue<TileOrientation> movementQueue;

void loadModel() {
    Sprite sprite("resources/tiles/southwest.ptm", 8);
    model.addSpriteForDirection(sprite, SOUTHWEST);

    sprite.loadTextureFromFile("resources/tiles/southeast.ptm", 8);
    model.addSpriteForDirection(sprite, SOUTHEAST);

    sprite.loadTextureFromFile("resources/tiles/south.ptm", 9);
    model.addSpriteForDirection(sprite, SOUTH);

    sprite.loadTextureFromFile("resources/tiles/west.ptm", 8);
    model.addSpriteForDirection(sprite, WEST);

    sprite.loadTextureFromFile("resources/tiles/east.ptm", 8);
    model.addSpriteForDirection(sprite, EAST);

    sprite.loadTextureFromFile("resources/tiles/northwest.ptm", 8);
    model.addSpriteForDirection(sprite, NORTHWEST);

    sprite.loadTextureFromFile("resources/tiles/northeast.ptm", 8);
    model.addSpriteForDirection(sprite, NORTHEAST);

    sprite.loadTextureFromFile("resources/tiles/north.ptm", 8);
    model.addSpriteForDirection(sprite, NORTH);

    sprite.loadTextureFromFile("resources/tiles/female.ptm", 1);
    female.addSpriteForDirection(sprite, SOUTH);
}

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

void drawBlock(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    glTexCoord2f(0, 0);
    glVertex2f(x, y);

    glTexCoord2f(0, 1);
    glVertex2f(x, y + height);

    glTexCoord2f(1, 1);
    glVertex2f(x + width, y + height);

    glTexCoord2f(1, 0);
    glVertex2f(x + width, y);
}

void resetModel() {

	//Initial model and objective positions
	TilePosition pos;
	pos.x = 12;
	pos.y = 3;
	model.setCurrentPosition(pos);

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
    glTranslatef(-48, 150, 0);
	glColor3f(0.0, 1.0, 0.5);

    tm.loadTilemap("resources/map/map.txt");

    set.addTileFromFile("resources/tiles/brickwall.ptm");		 // 1
    set.addTileFromFile("resources/tiles/stonebricksmooth.ptm"); // 2
//    set.addTileFromFile("resources/tiles/grass.ptm");			 // 3
//    set.addTileFromFile("resources/tiles/ground.ptm");			 // 4

	resetModel();

	TilePosition femalePos;
	femalePos.x = 11;
	femalePos.y = 1;
	female.setCurrentPosition(femalePos);

    loadModel();
}

void render(void) {
    TilePosition tp;

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    for (int x = 0; x < TILE_ROWS; x++) {
        for (int y = 0; y < TILE_COLS; y++) {
            tp = dv.calcTilePosition(x, y);

            Tile tile = set.getTileById(tm.getTileId(x, y));

            glBindTexture(GL_TEXTURE_2D, tile.getTextureId());

            glBegin(GL_QUADS);

            if (tile.getTextureId() != 1) {
                drawDiamond(tp.x, tp.y, TILE_WIDTH);
            }

            glEnd();
        }
    }

    for (int x = 0; x < TILE_ROWS; x++) {
        for (int y = 0; y < TILE_COLS; y++) {
			TilePosition pos = model.getCurrentPosition();

            if (x == pos.x && y == pos.y) {
                int cwidth = 44;
                float offX = (TILE_WIDTH - cwidth)/2;
                float currentTime = model.getTime();

                if (currentTime != 0) {
                    pos = model.getOldPosition();
                    model.setTime(currentTime +  0.125f);
                } else {
                    pos = model.getCurrentPosition();
                }

                pos = dv.calcTilePosition(pos.x, pos.y);
                model.render(pos.x + offX, pos.y + offX/2);
            }

			TilePosition femalePos = female.getCurrentPosition();

            if (x == femalePos.x && y == femalePos.y) {
                int cwidth = 51;
                float offX = (TILE_WIDTH - cwidth)/2;

                pos = dv.calcTilePosition(femalePos.x, femalePos.y);
                female.render(pos.x + offX, pos.y + offX/2);
            }

            tp = dv.calcTilePosition(x, y);
            Tile tile = set.getTileById(tm.getTileId(x, y));

            if (tile.getTextureId() == 1) {
                glBindTexture(GL_TEXTURE_2D, tile.getTextureId());
                glBegin(GL_QUADS);
                drawBlock(tp.x, tp.y, 64, 64);
                glEnd();
            }
        }
    }

    glDisable(GL_TEXTURE_2D);
    glFlush();
}

void victory() {
	glRasterPos2i(200, 110);
	glColor3f(0.0, 1.0, 0.5);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"You WIN!!!");
	glFlush();

	system("pause");
	resetModel();
}


bool detectCollision(TilePosition pos) {

	TilePosition currentPosition = model.getCurrentPosition();

	if (pos.x == currentPosition.x && pos.y == currentPosition.y) {
		//out of bounds
		return true;
	}

	Tile tile = set.getTileById(tm.getTileId(pos.x, pos.y));

	if (tile.getTextureId() == 1) {
		//block collision
		return true;
	}

	TilePosition femalePos = female.getCurrentPosition();
	if (pos.x == femalePos.x && pos.y == femalePos.y) {
		// Win
		victory();
		return true;
	}

	return false;
}

void tileWalking(TileOrientation orientation) {

	TilePosition cursor = model.getCurrentPosition();
	dv.calcTilePosition(cursor.x, cursor.y);

	dv.tileWalking(orientation);
	model.walk(orientation);

	TilePosition pos;
	pos.x = dv.getX();
	pos.y = dv.getY();

	if (detectCollision(pos)) {
		queue<TileOrientation> empty;
		swap(movementQueue, empty);
		return;
	}

	model.setCurrentPosition(pos);
	model.setTime(0.00001f);

}

void processQueue() {

	if (model.getTime() != 0 || movementQueue.empty()) {
		return;
	}

	TileOrientation orientation = movementQueue.front();
	movementQueue.pop();

	tileWalking(orientation);
}

void walkQueue(enum TileOrientation orientation, int size = 1) {

	for (int i = 0; i < size; i++) {
		movementQueue.push(orientation);
	}

	processQueue();

}

void handleKeyboard(unsigned char key, int x, int y) {

    switch (toupper(key)) {
        case 'W':
			walkQueue(NORTH);
            break;
        case 'A':
			walkQueue(WEST);
            break;
        case 'S':
            walkQueue(SOUTH);
            break;
        case 'D':
            walkQueue(EAST);
            break;
        case 'Q':
            walkQueue(NORTHWEST);
            break;
        case 'E':
            walkQueue(NORTHEAST);
            break;
        case 'Z':
            walkQueue(SOUTHWEST);
            break;
        case 'C':
            walkQueue(SOUTHEAST);
            break;
        default:
            return;
    }
}

void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

		TilePosition pos = dv.screenToTilePosition(x, y, MAP_WIDTH, MAP_HEIGHT);
		TilePosition cursor = model.getCurrentPosition();

        cout << "Cursor at " << pos.x << "x" << pos.y << "\n";

        int tileX = cursor.x - pos.x;
        int tileY = cursor.y - pos.y;

        if (tileY < 0) {
            if (tileX < 0) {
 				walkQueue(SOUTHWEST, tileY * tileX);
            }
            else if (tileX > 0) {
				walkQueue(NORTHWEST, -tileY * tileX);
            }
            else {
				walkQueue(WEST, -tileY);
            }
        }
        else if (tileY > 0) {
            if (tileX < 0) {
				walkQueue(NORTHEAST, tileY * -tileX);
            }
            else if (tileX > 0) {
				walkQueue(NORTHWEST, tileY * tileX);
            }
            else {
				walkQueue(NORTH, tileY);
            }
        }
        else {
            if (tileX < 0) {
				walkQueue(SOUTHEAST, -tileX);
            }
            else if (tileX > 0) {
				walkQueue(NORTHWEST, tileX);
            }
        }

    }
}

void animate(int t) {
    model.update(processQueue);
    glutTimerFunc(30, animate, 0);
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(MAP_WIDTH, MAP_HEIGHT);

    int windowX = (glutGet(GLUT_SCREEN_WIDTH) - MAP_WIDTH)/2,
        windowY = (glutGet(GLUT_SCREEN_HEIGHT) - MAP_HEIGHT)/2;

    glutInitWindowPosition(windowX, windowY);
    glutCreateWindow("Teste");

    init();

    glutKeyboardFunc(handleKeyboard);
    glutMouseFunc(handleMouse);
    glutDisplayFunc(render);

    glutTimerFunc(33, animate, 0);
    glutMainLoop();

    return 0;
}
