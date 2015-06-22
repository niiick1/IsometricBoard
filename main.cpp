#include <Windows.h>
#include <gl/GL.h>
#include <gl/glu.h>
#include <GL\freeglut.h>

#include "TileMap.h"
#include "DiamondView.h"
#include "RGBAColor.h"
#include <vector>
#include "PTMReader.h"
#include "Model.h"
#include "Sprite.h"
#include <iostream>

using namespace std;

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = TILE_WIDTH / 2;
const int TILE_ROWS = 13;
const int TILE_COLS = 12;
const int MAP_WIDTH = 800;
const int MAP_HEIGHT = 600;

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
    int x = 12,
        y = 3;
};

struct FemalePosition {
    int x = 11,
        y = 1;
};

Cursor cursor;
FemalePosition femalePos;
PTMReader ptm;
Tileset set;
Model m;
Model female;

void loadModel() {
    Sprite sprite("resources/tiles/southwest.ptm", 8);
    m.addSpriteForDirection(sprite, SOUTHWEST);

    sprite.loadTextureFromFile("resources/tiles/southeast.ptm", 8);
    m.addSpriteForDirection(sprite, SOUTHEAST);

    sprite.loadTextureFromFile("resources/tiles/char1.ptm", 9);
    m.addSpriteForDirection(sprite, SOUTH);

    sprite.loadTextureFromFile("resources/tiles/west.ptm", 8);
    m.addSpriteForDirection(sprite, WEST);

    sprite.loadTextureFromFile("resources/tiles/east.ptm", 8);
    m.addSpriteForDirection(sprite, EAST);

    sprite.loadTextureFromFile("resources/tiles/northwest.ptm", 8);
    m.addSpriteForDirection(sprite, NORTHWEST);

    sprite.loadTextureFromFile("resources/tiles/northeast.ptm", 8);
    m.addSpriteForDirection(sprite, NORTHEAST);

    sprite.loadTextureFromFile("resources/tiles/north.ptm", 8);
    m.addSpriteForDirection(sprite, NORTH);

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

void drawTile(GLfloat x, GLfloat y, GLfloat width, GLint volume) {
    float height = width / 2;

    glBegin(GL_QUADS);
    drawDiamond(x, y, width);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(x, height / 2 - y);
        glVertex2f(width / 2 + x, height - y);
        glVertex2f(width / 2 + x, height - y - volume);
        glVertex2f(x, height / 2 - y - volume);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(width / 2 + x, height - y);
        glVertex2f(width + x, height / 2 - y);
        glVertex2f(width + x, height / 2 - y - volume);
        glVertex2f(width / 2 + x, height - y - volume);
    glEnd();
}

void drawCharacter(GLfloat x, GLfloat y) {
    int width = 45,
        height = 95;

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
    glTranslatef(0, 150, 0);
	glColor3f(0.0, 1.0, 0.5);

    tm.loadTilemap("resources/map/map.txt");

//    set.addTileFromFile("resources/tiles/bricks.ptm");
//    set.addTileFromFile("resources/tiles/stonebrick.ptm");
    set.addTileFromFile("resources/tiles/brickwall.ptm");
    set.addTileFromFile("resources/tiles/stonebricksmooth.ptm");
//    set.addTileFromFile("resources/tiles/grass.ptm");

//    set.addTileFromFile("resources/tiles/ground.ptm");
    set.addTileFromFile("resources/tiles/poring.ptm");
    set.addTileFromFile("resources/tiles/assassin.ptm");

    TilePosition pos;
    pos.x = cursor.x;
    pos.y = cursor.y;
    m.setCurrentPosition(pos);

    pos = m.getCurrentPosition();

    loadModel();
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
            TilePosition pos;

            if (x == cursor.x && y == cursor.y) {
                int cwidth = 44;
                float offX = (TILE_WIDTH - cwidth)/2;
                float currentTime = m.getTime();

                if (currentTime != 0) {
                    pos = m.getOldPosition();
                    m.setTime(currentTime +  0.125f);
                } else {
                    pos = m.getCurrentPosition();
                }

                pos = dv.calcTilePosition(pos.x, pos.y);
                m.render(pos.x + offX, pos.y + offX/2);
            }

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
	glRasterPos2i(100, 100);
	glColor3f(0.0, 1.0, 0.5);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"WONNED!!!");
	glFlush();

	system("pause");
}


bool detectCollision(TilePosition pos) {

	if (pos.x == cursor.x && pos.y == cursor.y) {
		//out of bounds
		return true;
	}

	Tile tile = set.getTileById(tm.getTileId(pos.x, pos.y));

	if (tile.getTextureId() == 1) {
		//block collision
		return true;
	}

	if (pos.x == femalePos.x && pos.y == femalePos.y) {
		// Wonned
		victory();
		return true;
	}
	
	return false;
}


void walk(enum TileOrientation orientation) {

	if (m.getTime() != 0) {
		return;
	}

	dv.calcTilePosition(cursor.x, cursor.y);

	dv.tileWalking(orientation);
	m.walk(orientation);

	TilePosition pos;
	pos.x = dv.getX();
	pos.y = dv.getY();

	if (detectCollision(pos)) {
		return;
	}

	m.setCurrentPosition(pos);
	m.setTime(0.00001f);

	cursor.x = dv.getX();
	cursor.y = dv.getY();

}

void handleKeyboard(unsigned char key, int x, int y) {

    switch (toupper(key)) {        
        case 'W':	
			walk(NORTH);
            break;        
        case 'A':
			walk(WEST);
            break;        
        case 'S':
            walk(SOUTH);            
            break;        
        case 'D':
            walk(EAST);            
            break;
        case 'Q':
            walk(NORTHWEST);            
            break;        
        case 'E':
            walk(NORTHEAST);            
            break;
        case 'Z':
            walk(SOUTHWEST);
            break;
        case 'C':
            walk(SOUTHEAST);
            break;
        default:
            return;
    }
}

void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

		TilePosition pos = dv.screenToTilePosition(x, y, MAP_WIDTH, MAP_HEIGHT);

        cout << "Cursor at " << pos.x << "x" << pos.y << "\n";

        int tileX = cursor.x - pos.x;
        int tileY = cursor.y - pos.y;

        if (tileY < 0) {
            if (tileX < 0) {
                cout << "1 - Move to SouthWest" << "\n";                
 				walk(SOUTHWEST);
            }
            else if (tileX > 0) {
                cout << "2- Move to NorthWest" << "\n";                
				walk(NORTHWEST);
            }
            else {                
                cout << "3 - Move to West" << "\n";
				walk(WEST);
            }
        }
        else if (tileY > 0) {
            if (tileX < 0) {                                
                cout << "4 - Move to NorthEast" << "\n";
				walk(NORTHEAST);
            }
            else if (tileX > 0) {
                cout << "5 - Move to NorthWest" << "\n";
				walk(NORTHWEST);
            }
            else {
                cout << "6 - Move to North" << "\n";
				walk(NORTH);
            }
        }
        else {
            if (tileX < 0) {
                cout << "7 - Move to SouthEast" << "\n";
				walk(SOUTHEAST);
            }
            else if (tileX > 0) {
                cout << "8 - Move to NorthWest" << "\n";
				walk(NORTHWEST);
            }
        }

    }
}

void animate(int t) {
    m.update();
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
