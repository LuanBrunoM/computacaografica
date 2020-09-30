#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <windows.h>

#define PI 3.1415926535898

void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int tecla, int x, int y);
void resize(GLsizei w, GLsizei h);
void display(void);
void animate(int value);

float translateX = 0;
float translateY = 0;
float xStep = 4;
float yStep = 4;

int TIMER = 70;
int X = 0;
int Y = 1;
int WIDTH = 2;
int HEIGHT = 3;
int VISIBLE = 4;
int TYPE = 5;

int FUEL_TYPE = 1;
int HELICOPTER_TYPE = 2;
int TREE_TYPE = 3;
int HOUSE_TYPE = 4;
int SHIP_TYPE = 5;
int ROAD_TYPE = 6;
int TERRAIN_TYPE = 7;

int DEFAULT_FORCE = 10;
int SPEED = 1;
int HORIZONTAL_SPEED = 3;
int BULLET_SPEED = 3;
int BULLETS_POSITION[100][5];
int bulletsCounter = 0;
int MAX_FUEL = 100;
int ACTUAL_FUEL = 100;

bool firstFrame = true;
int colisors[5][6];
int colisorsCounter = 0;
int AIRPLANE_POSITION[4];
int playerPositionX = 1;
int playerPositionY = 1;
int rotatePropeller;

bool firstTimeBullet = true;

void resetArrays() {
    for (int bullet = 0; bullet < 100; bullet++) {
        BULLETS_POSITION[bullet][X] = 0;
        BULLETS_POSITION[bullet][Y] = -200;
        BULLETS_POSITION[bullet][WIDTH] = 0;
        BULLETS_POSITION[bullet][HEIGHT] = -200;
        BULLETS_POSITION[bullet][VISIBLE] = 0;
    }
    for (int colisor = 0; colisor < 100; colisor++) {
        colisors[colisor][X] = 0;
        colisors[colisor][Y] = -200;
        colisors[colisor][WIDTH] = 0;
        colisors[colisor][HEIGHT] = -200;
        colisors[colisor][VISIBLE] = 0;
        colisors[colisor][TYPE] = 0;
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores � RGB ou RGBA

    glutInitWindowSize(400, 400);  // tamanho da janela

    //glutFullScreen();  // full screen

    glutInitWindowPosition(900, -800); // posicao inicial da janela

    glutCreateWindow("River Raid - Marcos e Luan");   /// cria a janela

    glutKeyboardFunc(&keyboard);
    glutSpecialFunc(&specialKeyboard);

    glutReshapeFunc(&resize); // 
    glutTimerFunc(150, animate, 1);
    glutDisplayFunc(display);

    if (firstFrame) {
        resetArrays();
    }

    glutMainLoop();

    return EXIT_SUCCESS;
}
void resize(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;  // Evita a divisao por zero

    glViewport(0, 0, w, h);  // Especifica as dimens�es da Viewport

   // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de sele��o (left, right, bottom, top)
    if (w <= h)
    {
        gluOrtho2D(0.0f, 400.0f, 0.0f, 400.0f * h / w);
    }
    else
    {
        gluOrtho2D(0.0f, 400.0f * w / h, 0.0f, 400.0f);
    }
    glMatrixMode(GL_MODELVIEW);
}
void animate(int value) {
    if (translateX > 200 || translateX < -200) {
        xStep = -xStep;
    }
    if (translateY > 200 || translateY < -200) {
        yStep = -yStep;
    }

    if (translateY <= playerPositionX + 50 && translateY >= playerPositionX - 50) {
        xStep = -xStep;
        if (TIMER > 15) {
            TIMER -= 5;
        }
    }

    translateX -= xStep;
    translateY -= yStep;

    glutPostRedisplay();
    glutTimerFunc(TIMER, animate, 1);
}
void specialKeyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT) {
        playerPositionX = playerPositionX + DEFAULT_FORCE;
    }
    if (key == GLUT_KEY_LEFT) {
        playerPositionX = playerPositionX - DEFAULT_FORCE;
    }
    if (key == GLUT_KEY_DOWN) {
        playerPositionY = playerPositionY - DEFAULT_FORCE;
    }
    if (key == GLUT_KEY_UP) {
        playerPositionY = playerPositionY + DEFAULT_FORCE;
    }

    glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
    if (key == 'w') {
        bulletsCounter++;
        BULLETS_POSITION[bulletsCounter][VISIBLE] = 1;
        firstTimeBullet = true;
    }
}

void ocean() {
    glBegin(GL_QUADS);
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(-150, -200);
    glVertex2f(150, -200);
    glVertex2f(150, 225);
    glVertex2f(-150, 225);
    glEnd();
}
void treeColisor(int x, int y) {
    glPushMatrix();

    glTranslatef(175, 125, 0);

    glBegin(GL_QUADS); // green
    glColor3ub(19, 113, 52);
    glVertex2f(x + -153, y + -98 - SPEED);
    glVertex2f(x + -153, y + -123 - SPEED);
    glVertex2f(x + -197, y + -123 - SPEED);
    glVertex2f(x + -197, y + -98 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // brown
    glColor3ub(101, 101, 28);
    glVertex2f(x + -170, y + -115 - SPEED);
    glVertex2f(x + -170, y + -123 - SPEED);
    glVertex2f(x + -180, y + -123 - SPEED);
    glVertex2f(x + -180, y + -115 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // green
    glColor3ub(104, 203, 156);
    glVertex2f(x + -162, y + -115 - SPEED);
    glVertex2f(x + -162, y + -105 - SPEED);
    glVertex2f(x + -188, y + -105 - SPEED);
    glVertex2f(x + -188, y + -115 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // green
    glColor3ub(104, 203, 156);
    glVertex2f(x + -153, y + -112 - SPEED);
    glVertex2f(x + -153, y + -108 - SPEED);
    glVertex2f(x + -197, y + -108 - SPEED);
    glVertex2f(x + -197, y + -112 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // green
    glColor3ub(104, 203, 156);
    glVertex2f(x + -170, y + -98 - SPEED);
    glVertex2f(x + -170, y + -105 - SPEED);
    glVertex2f(x + -180, y + -105 - SPEED);
    glVertex2f(x + -180, y + -98 - SPEED);
    glEnd();

    glPopMatrix();
}
void tree(int x, int y) {
    glPushMatrix();

    glTranslatef(193, 99, 0);

    glBegin(GL_QUADS); // brown
    glColor3ub(101, 101, 28);
    glVertex2f(x + -170, y + -115 - SPEED);
    glVertex2f(x + -170, y + -123 - SPEED);
    glVertex2f(x + -180, y + -123 - SPEED);
    glVertex2f(x + -180, y + -115 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // green
    glColor3ub(104, 203, 156);
    glVertex2f(x + -162, y + -115 - SPEED);
    glVertex2f(x + -162, y + -105 - SPEED);
    glVertex2f(x + -188, y + -105 - SPEED);
    glVertex2f(x + -188, y + -115 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // green
    glColor3ub(104, 203, 156);
    glVertex2f(x + -153, y + -112 - SPEED);
    glVertex2f(x + -153, y + -108 - SPEED);
    glVertex2f(x + -197, y + -108 - SPEED);
    glVertex2f(x + -197, y + -112 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // green
    glColor3ub(104, 203, 156);
    glVertex2f(x + -170, y + -98 - SPEED);
    glVertex2f(x + -170, y + -105 - SPEED);
    glVertex2f(x + -180, y + -105 - SPEED);
    glVertex2f(x + -180, y + -98 - SPEED);
    glEnd();

    glPopMatrix();
}
void generateTree(int x, int y) {
    //treeColisor(x, y);
    tree(x, y);
}
void houseColisor(int x, int y) {
    glPushMatrix();

    glTranslatef(0, 15, 0);

    glTranslatef(x, y, 0);

    glBegin(GL_QUADS); // house base
    glColor3ub(46, 139, 87);
    glVertex2f(-30, 20 - SPEED);
    glVertex2f(-30, -10 - SPEED);
    glVertex2f(30, -10 - SPEED);
    glVertex2f(30, 20 + -SPEED);
    glEnd();

    glPopMatrix();
}
void house(int x, int y) {
    glPushMatrix();

    glTranslatef(27, -18, 0);

    glTranslatef(x, y, 0);
    glBegin(GL_TRIANGLES); // roof
    glColor3ub(4, 0, 4);
    glVertex2f(-30, 10 - SPEED);
    glVertex2f(30, 10 - SPEED);
    glVertex2f(0, 20 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // house base
    glColor3ub(211, 209, 208);
    glVertex2f(-30, 10 - SPEED);
    glVertex2f(-30, -10 - SPEED);
    glVertex2f(30, -10 - SPEED);
    glVertex2f(30, 10 + -SPEED);
    glEnd();

    glBegin(GL_QUADS); // house first window
    glColor3ub(46, 139, 87);
    glVertex2f(-20, 4 - SPEED);
    glVertex2f(-20, -4 - SPEED);
    glVertex2f(-10, -4 - SPEED);
    glVertex2f(-10, 4 + -SPEED);
    glEnd();

    glBegin(GL_QUADS); // house second window
    glColor3ub(46, 139, 87);
    glVertex2f(-5, 4 - SPEED);
    glVertex2f(-5, -4 - SPEED);
    glVertex2f(5, -4 - SPEED);
    glVertex2f(5, 4 + -SPEED);
    glEnd();

    glBegin(GL_QUADS); // house third window
    glColor3ub(46, 139, 87);
    glVertex2f(20, 4 - SPEED);
    glVertex2f(20, -4 - SPEED);
    glVertex2f(10, -4 - SPEED);
    glVertex2f(10, 4 - SPEED);
    glEnd();

    glPopMatrix();
}
void generateHouse(int x, int y) {
    // houseColisor(x, y);
    house(x, y);
}
void fuelColisor(int x, int y) {
    glPushMatrix();

    glTranslatef(0, -85, 0);

    glTranslatef(GLfloat(x), GLfloat(y), 0);

    glBegin(GL_QUADS);
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(15, 130 - SPEED);
    glVertex2f(15, 70 - SPEED);
    glVertex2f(-15, 70 - SPEED);
    glVertex2f(-15, 130 - SPEED);
    glEnd();

    glPopMatrix();
}

void generateColisorTest(int x, int y, int width, int height) {
    glPushMatrix();
    glTranslatef(x, y, 0);

    glTranslatef(0, -85, 0);

    glBegin(GL_QUADS);
    glColor3ub(107, 206, 234);
    glVertex2f(x, y);
    glVertex2f(x, height);
    glVertex2f(width, height);
    glVertex2f(width, y);
    glEnd();

    glPopMatrix();
}

void fuel(int x, int y) {
    glPushMatrix();

    glTranslatef(11, -129, 0);

    glTranslatef(x, y, 0);

    glBegin(GL_QUADS); //  pink fuel F
    glColor3ub(207, 106, 134);
    glVertex2f(15, 128 - SPEED);
    glVertex2f(15, 115 - SPEED);
    glVertex2f(-15, 115 - SPEED);
    glVertex2f(-15, 128 - SPEED);
    glEnd();

    glBegin(GL_QUADS); //  pink fuel F block
    glColor3ub(207, 106, 134);
    glVertex2f(11, 130 - SPEED);
    glVertex2f(11, 115 - SPEED);
    glVertex2f(-11, 115 - SPEED);
    glVertex2f(-11, 130 - SPEED);
    glEnd();

    glBegin(GL_QUADS); //  F base
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(-5, 125 - SPEED);
    glVertex2f(-5, 117 - SPEED);
    glVertex2f(-3, 117 - SPEED);
    glVertex2f(-3, 125 - SPEED);
    glEnd();

    glBegin(GL_QUADS); //  F top
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(5, 125 - SPEED);
    glVertex2f(5, 123 - SPEED);
    glVertex2f(-3, 123 - SPEED);
    glVertex2f(-3, 125 - SPEED);
    glEnd();

    glBegin(GL_QUADS); //  F bot
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(3, 121 - SPEED);
    glVertex2f(3, 120 - SPEED);
    glVertex2f(-3, 120 - SPEED);
    glVertex2f(-3, 121 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // white fuel U
    glColor3ub(211, 209, 208);
    glVertex2f(15, 100 - SPEED);
    glVertex2f(15, 115 - SPEED);
    glVertex2f(-15, 115 - SPEED);
    glVertex2f(-15, 100 - SPEED);
    glEnd();

    glBegin(GL_QUADS); //  U right
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(-5, 102 - SPEED);
    glVertex2f(-5, 113 - SPEED);
    glVertex2f(-2, 113 - SPEED);
    glVertex2f(-2, 102 - SPEED);
    glEnd();

    glBegin(GL_QUADS); //  U left
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(5, 102 - SPEED);
    glVertex2f(5, 113 - SPEED);
    glVertex2f(2, 113 - SPEED);
    glVertex2f(2, 102 - SPEED);
    glEnd();

    glBegin(GL_QUADS); //  U bot
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(-5, 102 - SPEED);
    glVertex2f(-5, 104 - SPEED);
    glVertex2f(5, 104 - SPEED);
    glVertex2f(5, 102 - SPEED);
    glEnd();

    glBegin(GL_QUADS); //  pink fuel E
    glColor3ub(207, 106, 134);
    glVertex2f(15, 100 - SPEED);
    glVertex2f(15, 85 - SPEED);
    glVertex2f(-15, 85 - SPEED);
    glVertex2f(-15, 100 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // E base
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(-5, 87 - SPEED);
    glVertex2f(-5, 97 - SPEED);
    glVertex2f(-3, 97 - SPEED);
    glVertex2f(-3, 87 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // E top
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(-3, 95 - SPEED);
    glVertex2f(-3, 97 - SPEED);
    glVertex2f(5, 97 - SPEED);
    glVertex2f(5, 95 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // E middle
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(-3, 93 - SPEED);
    glVertex2f(-3, 91 - SPEED);
    glVertex2f(3, 91 - SPEED);
    glVertex2f(3, 93 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // E bot
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(-3, 89 - SPEED);
    glVertex2f(-3, 87 - SPEED);
    glVertex2f(5, 87 - SPEED);
    glVertex2f(5, 89 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // white fuel L
    glColor3ub(211, 209, 208);
    glVertex2f(15, 85 - SPEED);
    glVertex2f(15, 70 - SPEED);
    glVertex2f(-15, 70 - SPEED);
    glVertex2f(-15, 85 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // L base
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(-5, 73 - SPEED);
    glVertex2f(-5, 83 - SPEED);
    glVertex2f(-3, 83 - SPEED);
    glVertex2f(-3, 73 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // L bot
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(5, 73 - SPEED);
    glVertex2f(5, 75 - SPEED);
    glVertex2f(-3, 75 - SPEED);
    glVertex2f(-3, 73 - SPEED);
    glEnd();

    glPopMatrix();
}
void addFuelToColisors(int x, int y, int colisorCounter) {
    if (colisors[colisorCounter][Y] == -200) {
        colisors[colisorCounter][X] = x;
        colisors[colisorCounter][Y] = y;
        colisors[colisorCounter][WIDTH] = x + 30;
        colisors[colisorCounter][HEIGHT] = y + 60;
    }
    else {
        colisors[colisorCounter][Y] = y - SPEED;
        colisors[colisorCounter][HEIGHT] = y + 60 - SPEED;
    }
}
int timerFuel = 0;
void generateFuel(int x, int y) {
    if (ACTUAL_FUEL > -70 && timerFuel == 4) {
        ACTUAL_FUEL -= 1;
        timerFuel = 0;
    }

    timerFuel++;

    if (firstFrame) {
        colisors[colisorsCounter][VISIBLE] = 1;
        colisors[colisorsCounter][TYPE] = FUEL_TYPE;
        colisorsCounter++;
    }

    for (int colisorCounter = 0; colisorCounter < colisorsCounter; colisorCounter++) {
        if (colisors[colisorCounter][VISIBLE] == 1 && colisors[colisorCounter][TYPE] == FUEL_TYPE) {
            fuel(x, y);
            addFuelToColisors(x, y, colisorCounter);
        }
    }
}
int helicopterHorizontalSpeed = 1;
bool helicopterShouldGoRight = false;
void helicopterColisor(int x, int y) {
    glPushMatrix();

    glTranslatef(35, -137, 0);

    /*if (helicopterHorizontalSpeed > -75 && !helicopterShouldGoRight) {
        helicopterHorizontalSpeed -= 2;
        helicopterShouldGoRight = helicopterHorizontalSpeed < -70 && helicopterHorizontalSpeed > -75;
    }
    else {
        helicopterHorizontalSpeed += 2;
        helicopterShouldGoRight = !(helicopterHorizontalSpeed > 70 && helicopterHorizontalSpeed < 75);
    }*/

    glTranslatef(x + helicopterHorizontalSpeed, 1, 0);

    glBegin(GL_QUADS); // blue
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(x + -20, y + 167 - SPEED);
    glVertex2f(x + -20, y + 141 - SPEED);
    glVertex2f(x + -60, y + 141 - SPEED);
    glVertex2f(x + -60, y + 167 - SPEED);
    glEnd();

    glPopMatrix();
}
void helicopter(int x, int y) {
    glPushMatrix();

    glTranslatef(54, -167, 0);

    /*if (helicopterHorizontalSpeed >= -150 - 35 && !helicopterShouldGoRight) {
        helicopterHorizontalSpeed -= 2;
        helicopterShouldGoRight = helicopterHorizontalSpeed <= -150 - 35;
    }
    else {
        helicopterHorizontalSpeed += 2;
        helicopterShouldGoRight = helicopterHorizontalSpeed < 150 - 35;
    }*/

    glTranslatef(x + helicopterHorizontalSpeed, 1, 0);

    glBegin(GL_QUADS); // green
    glColor3ub(4, 76, 108);
    glVertex2f(x + -55, y + 158 - SPEED);
    glVertex2f(x + -55, y + 147 - SPEED);
    glVertex2f(x + -60, y + 147 - SPEED);
    glVertex2f(x + -60, y + 158 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // blue
    glColor3ub(0, 34, 114);
    glVertex2f(x + -20, y + 155 - SPEED);
    glVertex2f(x + -20, y + 150 - SPEED);
    glVertex2f(x + -60, y + 150 - SPEED);
    glVertex2f(x + -60, y + 155 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // green
    glColor3ub(4, 76, 108);
    glVertex2f(x + -45, y + 147 - SPEED);
    glVertex2f(x + -45, y + 150 - SPEED);
    glVertex2f(x + -25, y + 150 - SPEED);
    glVertex2f(x + -25, y + 147 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // green
    glColor3ub(4, 76, 108);
    glVertex2f(x + -37, y + 147 - SPEED);
    glVertex2f(x + -37, y + 144 - SPEED);
    glVertex2f(x + -33, y + 144 - SPEED);
    glVertex2f(x + -33, y + 147 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // green
    glColor3ub(4, 76, 108);
    glVertex2f(x + -45, y + 144 - SPEED);
    glVertex2f(x + -45, y + 141 - SPEED);
    glVertex2f(x + -25, y + 141 - SPEED);
    glVertex2f(x + -25, y + 144 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // green
    glColor3ub(4, 76, 108);
    glVertex2f(x + -47, y + 155 - SPEED);
    glVertex2f(x + -47, y + 158 - SPEED);
    glVertex2f(x + -20, y + 158 - SPEED);
    glVertex2f(x + -20, y + 155 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // green
    glColor3ub(4, 76, 108);
    glVertex2f(x + -43, y + 160 - SPEED);
    glVertex2f(x + -43, y + 158 - SPEED);
    glVertex2f(x + -24, y + 158 - SPEED);
    glVertex2f(x + -24, y + 160 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // yellow
    glColor3ub(222, 191, 113);
    glVertex2f(x + -35, y + 160 - SPEED);
    glVertex2f(x + -35, y + 167 - SPEED);
    glVertex2f(x + -30, y + 167 - SPEED);
    glVertex2f(x + -30, y + 160 - SPEED);
    glEnd();

    int rotatePropellerRight = rotatePropeller > 4 ? 167 : 163;
    int rotatePropellerLeft = rotatePropeller > 4 ? 163 : 167;

    glBegin(GL_QUADS); // yellow
    glColor3ub(222, 191, 113);
    glVertex2f(x + -35, y + 165 - SPEED);
    glVertex2f(x + -35, y + rotatePropellerRight - SPEED);
    glVertex2f(x + -20, y + rotatePropellerRight - SPEED);
    glVertex2f(x + -20, y + 165 - SPEED);
    glEnd();

    glBegin(GL_QUADS); // yellow 
    glColor3ub(222, 191, 113);
    glVertex2f(x + -35, y + 165 - SPEED);
    glVertex2f(x + -35, y + rotatePropellerLeft - SPEED);
    glVertex2f(x + -45, y + rotatePropellerLeft - SPEED);
    glVertex2f(x + -45, y + 165 - SPEED);
    glEnd();

    glPopMatrix();
}
void addHelicopterToColisors(int x, int y, int colisorCounter) {
    /* colisors[colisorCounter][X] = -20;
     colisors[colisorCounter][Y] = 167 - SPEED;
     colisors[colisorCounter][WIDTH] = -60;
     colisors[colisorCounter][HEIGHT] = 141 - SPEED;*/


    if (colisors[colisorCounter][X] >= -150 && !helicopterShouldGoRight) {
        helicopterHorizontalSpeed = -3;
        helicopterShouldGoRight = colisors[colisorCounter][X] <= -145;
    }

    if (helicopterShouldGoRight) {
        helicopterHorizontalSpeed = 3;
        helicopterShouldGoRight = colisors[colisorCounter][X] < 145;
    }

    if (colisors[colisorCounter][Y] == -200) {
        colisors[colisorCounter][X] = x;
        colisors[colisorCounter][Y] = y;
        colisors[colisorCounter][WIDTH] = x + 90;
        colisors[colisorCounter][HEIGHT] = y + 22;
    }
    else {
        //colisors[colisorCounter][X] += helicopterHorizontalSpeed;
        colisors[colisorCounter][Y] = y + 10 - SPEED;
        //colisors[colisorCounter][WIDTH] += helicopterHorizontalSpeed;
        colisors[colisorCounter][HEIGHT] = y - SPEED;
    }
}
void generateHelicopter(int x, int y) {
    if (firstFrame) {
        colisors[colisorsCounter][VISIBLE] = 1;
        colisors[colisorsCounter][TYPE] = HELICOPTER_TYPE;
        colisorsCounter++;
    }

    for (int colisorCounter = 0; colisorCounter < colisorsCounter; colisorCounter++) {
        if (colisors[colisorCounter][VISIBLE] == 1 && colisors[colisorCounter][TYPE] == HELICOPTER_TYPE) {
            helicopter(x, y);
            addHelicopterToColisors(x, y, colisorCounter);
        }
    }
}
int shipHorizontalSpeed = 1;
bool shipShouldGoRight = false;
void shipColisor(int x, int y, int colisorCounter) {
    glPushMatrix();

    glTranslatef(-40, -130, 0);

    glTranslatef(colisors[colisorCounter][X], colisors[colisorCounter][Y], 0);

    glBegin(GL_QUADS); // blue
    glColor3f(0.16862f, 0.352941f, 0.64313725f);
    glVertex2f(80, 130);
    glVertex2f(80, 154);
    glVertex2f(-10, 154);
    glVertex2f(-10, 130);
    glEnd();

    glPopMatrix();
}
void ship(int colisorCounter) {
    glPushMatrix();
    glTranslatef(5, -160, 0);

    glTranslatef(colisors[colisorCounter][X], colisors[colisorCounter][Y], 0);

    glColor3ub(222, 222, 222);

    glBegin(GL_QUADS); // blue
    glColor3ub(80, 159, 203);
    glVertex2f(70, 132);
    glVertex2f(70, 137);
    glVertex2f(20, 137);
    glVertex2f(20, 132);
    glEnd();

    glBegin(GL_QUADS); // blue
    glColor3ub(80, 159, 203);
    glVertex2f(70, 135);
    glVertex2f(70, 137);
    glVertex2f(80, 137);
    glVertex2f(80, 135);
    glEnd();

    glBegin(GL_QUADS); // brown
    glColor3ub(133, 85, 35);
    glVertex2f(80, 140);
    glVertex2f(80, 137);
    glVertex2f(5, 137);
    glVertex2f(5, 140);
    glEnd();

    glBegin(GL_QUADS); // brown
    glColor3ub(133, 85, 35);
    glVertex2f(80, 140);
    glVertex2f(80, 142);
    glVertex2f(-10, 142);
    glVertex2f(-10, 140);
    glEnd();

    glBegin(GL_QUADS); // black
    glColor3ub(2, 0, 6);
    glVertex2f(70, 145);
    glVertex2f(70, 142);
    glVertex2f(20, 142);
    glVertex2f(20, 145);
    glEnd();

    glBegin(GL_QUADS); // black
    glColor3ub(2, 0, 6);
    glVertex2f(60, 145);
    glVertex2f(60, 149);
    glVertex2f(30, 149);
    glVertex2f(30, 145);
    glEnd();

    glBegin(GL_QUADS); // black
    glColor3ub(2, 0, 6);
    glVertex2f(43, 154);
    glVertex2f(43, 149);
    glVertex2f(30, 149);
    glVertex2f(30, 154);
    glEnd();

    glPopMatrix();

}
void addShipToColisors(int x, int y, int colisorCounter) {
    if (colisors[colisorCounter][X] >= -150 && !shipShouldGoRight) {
        shipHorizontalSpeed = -3;
        shipShouldGoRight = colisors[colisorCounter][X] <= -145;
    }

    if (shipShouldGoRight) {
        shipHorizontalSpeed = 3;
        shipShouldGoRight = colisors[colisorCounter][X] < 145;
    }

    if (colisors[colisorCounter][Y] == -200) {
        colisors[colisorCounter][X] = x;
        colisors[colisorCounter][Y] = y;
        colisors[colisorCounter][WIDTH] = x + 90;
        colisors[colisorCounter][HEIGHT] = y + 22;
    }
    else {
        //colisors[colisorCounter][X] += shipHorizontalSpeed;
        colisors[colisorCounter][Y] = y + 10 - SPEED;
        //colisors[colisorCounter][WIDTH] += shipHorizontalSpeed;
        colisors[colisorCounter][HEIGHT] = y - SPEED;
    }
}
void generateShip(int x, int y) {
    if (firstFrame) {
        colisors[colisorsCounter][VISIBLE] = 1;
        colisors[colisorsCounter][TYPE] = SHIP_TYPE;
        colisorsCounter++;
    }

    for (int colisorCounter = 0; colisorCounter < colisorsCounter; colisorCounter++) {
        if (colisors[colisorCounter][VISIBLE] == 1 && colisors[colisorCounter][TYPE] == SHIP_TYPE) {
            addShipToColisors(x, y, colisorCounter);
            ship(colisorCounter);
        }
    }
}
void generateShips() {
    int positions[100][2];
    positions[0][X] = 100;
    positions[0][Y] = 110;
    positions[1][X] = 200;
    positions[1][Y] = 210;
    for (int i = 0; i < 3; i++) {
        generateShip(positions[i][X], positions[i][Y]);
    }
}

void bullet(int x, int y, int bulletCounter) {
    glPushMatrix();
    if (BULLETS_POSITION[bulletCounter][X] == 0) {
        glTranslatef(-55, 125, 0);
        glTranslatef(AIRPLANE_POSITION[X], AIRPLANE_POSITION[Y], 0);

        firstTimeBullet = false;
        BULLETS_POSITION[bulletCounter][X] = AIRPLANE_POSITION[X];
        BULLETS_POSITION[bulletCounter][Y] = AIRPLANE_POSITION[Y] + BULLET_SPEED;
        BULLETS_POSITION[bulletCounter][WIDTH] = AIRPLANE_POSITION[X] + 4;
        BULLETS_POSITION[bulletCounter][HEIGHT] = AIRPLANE_POSITION[Y] + 10 + BULLET_SPEED;
    }
    else {
        glTranslatef(-55, 125, 0);
        glTranslatef(BULLETS_POSITION[bulletCounter][X], BULLETS_POSITION[bulletCounter][Y], 0);

        BULLETS_POSITION[bulletCounter][Y] += BULLET_SPEED;
        BULLETS_POSITION[bulletCounter][HEIGHT] += BULLET_SPEED;
    }

    glBegin(GL_QUADS); // bullet
    glColor3ub(233, 201, 122);
    glVertex2f(x + 41, y + 100 + BULLET_SPEED);
    glVertex2f(x + 45, y + 100 + BULLET_SPEED);
    glVertex2f(x + 45, y + 110 + BULLET_SPEED);
    glVertex2f(x + 41, y + 110 + BULLET_SPEED);
    glEnd();

    glPopMatrix();
}
void bulletColided(int bulletCounter) {
    for (int colisor = 0; colisor < colisorsCounter; colisor++) {
        if (
            colisors[colisor][VISIBLE] &&
            BULLETS_POSITION[bulletCounter][X] <  colisors[colisor][X] + colisors[colisor][WIDTH] &&
            BULLETS_POSITION[bulletCounter][X] + BULLETS_POSITION[bulletCounter][WIDTH] > colisors[colisor][X] &&
            BULLETS_POSITION[bulletCounter][Y] < colisors[colisor][Y] + colisors[colisor][HEIGHT] &&
            BULLETS_POSITION[bulletCounter][Y] + BULLETS_POSITION[bulletCounter][HEIGHT] > colisors[colisor][Y]
            ) {
            printf("\n------ aqui drento --------\n");
            BULLETS_POSITION[bulletCounter][VISIBLE] = 0;
            colisors[colisor][VISIBLE] = 0;
        }
    }
}
void generateBullet(int x, int y) { // fazer um especial que a bullet SPEED é mais devagar
    for (int bulletCounter = 0; bulletCounter < bulletsCounter; bulletCounter++) {
        if (BULLETS_POSITION[bulletCounter][Y] < 230 && BULLETS_POSITION[bulletCounter][VISIBLE] == 1) {
            bullet(x, y, bulletCounter);
            bulletColided(bulletCounter);
        }
        else {
            BULLETS_POSITION[bulletCounter][VISIBLE] = 0;
        }
    }
}

void airplaneColided() {
    printf("\nAir: [X]: %d  [Y]: %d  [WIDTH]: %d  [HEIGHT]: %d\n", AIRPLANE_POSITION[X], AIRPLANE_POSITION[Y], AIRPLANE_POSITION[WIDTH], AIRPLANE_POSITION[HEIGHT]);

    for (int counter = 0; counter < colisorsCounter; counter++) {
        printf("Col: [X]: %d  [Y]: %d  [WIDTH]: %d  [HEIGHT]: %d\n\n\n", colisors[counter][X], colisors[counter][Y], colisors[counter][WIDTH], colisors[counter][HEIGHT]);
        printf("\n1: %d\n", AIRPLANE_POSITION[X] < colisors[counter][X] + colisors[counter][WIDTH]);
        printf("\n2: %d\n", AIRPLANE_POSITION[X] + AIRPLANE_POSITION[WIDTH] > colisors[counter][X]);
        printf("\n3: %d\n", AIRPLANE_POSITION[Y] < colisors[counter][Y] + colisors[counter][HEIGHT]);
        printf("\n4: %d\n", AIRPLANE_POSITION[Y] + AIRPLANE_POSITION[HEIGHT] > colisors[counter][Y]);

        if (
            colisors[counter][TYPE] != FUEL_TYPE &&
            AIRPLANE_POSITION[X] <= colisors[counter][X] + colisors[counter][WIDTH] &&
            AIRPLANE_POSITION[X] + AIRPLANE_POSITION[WIDTH] >= colisors[counter][X] &&
            AIRPLANE_POSITION[Y] <= colisors[counter][Y] + colisors[counter][HEIGHT] &&
            AIRPLANE_POSITION[Y] + AIRPLANE_POSITION[HEIGHT] >= colisors[counter][Y]
            ) {
            //printf("\n-------------------------aqui-------------------------");
            colisors[counter][VISIBLE] = false;
        }
        if (
            colisors[counter][TYPE] == FUEL_TYPE &&
            ACTUAL_FUEL < 100 &&
            AIRPLANE_POSITION[X] <= colisors[counter][X] + colisors[counter][WIDTH] &&
            AIRPLANE_POSITION[X] + AIRPLANE_POSITION[WIDTH] >= colisors[counter][X] &&
            AIRPLANE_POSITION[Y] <= colisors[counter][Y] + colisors[counter][HEIGHT] &&
            AIRPLANE_POSITION[Y] + AIRPLANE_POSITION[HEIGHT] >= colisors[counter][Y]
            ) {
            ACTUAL_FUEL += 2;
        }
    }
}
void airplaneColisor() {
    AIRPLANE_POSITION[X] = playerPositionX + 10;
    AIRPLANE_POSITION[Y] = playerPositionY - 155;
    AIRPLANE_POSITION[WIDTH] = playerPositionX - 25;
    AIRPLANE_POSITION[HEIGHT] = playerPositionY - 110;
}
void airplane(int x, int y) {
    glPushMatrix();

    glTranslatef(AIRPLANE_POSITION[X] - 10, AIRPLANE_POSITION[Y] + 45, 0);

    glColor3ub(233, 199, 119);

    glBegin(GL_QUADS); // core
    glVertex2f(x + 45, y + 100);
    glVertex2f(x + 45, y + 132);
    glVertex2f(x + 40, y + 132);
    glVertex2f(x + 40, y + 100);
    glEnd();

    glBegin(GL_QUADS); // top right
    glVertex2f(x + 45, y + 125);
    glVertex2f(x + 57, y + 120);
    glVertex2f(x + 57, y + 110);
    glVertex2f(x + 45, y + 115);
    glEnd();

    glBegin(GL_QUADS); // bot right
    glVertex2f(x + 45, y + 105);
    glVertex2f(x + 55, y + 99);
    glVertex2f(x + 55, y + 95);
    glVertex2f(x + 45, y + 99);
    glEnd();

    glBegin(GL_QUADS); // top left
    glVertex2f(x + 40, y + 125);
    glVertex2f(x + 28, y + 120);
    glVertex2f(x + 28, y + 110);
    glVertex2f(x + 40, y + 115);
    glEnd();

    glBegin(GL_QUADS); // bot left
    glVertex2f(x + 40, y + 105);
    glVertex2f(x + 30, y + 99);
    glVertex2f(x + 30, y + 95);
    glVertex2f(x + 40, y + 99);
    glEnd();

    glPopMatrix();
}
void generateAirplane(int x, int y) {
    airplaneColisor();
    airplane(x, y);
    airplaneColided();
}

void score() {
    glPushMatrix();

    glTranslatef(0, 100, 0);

    glBegin(GL_QUADS); // pointer
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(90.0, -253);
    glVertex2f(80, -253);
    glVertex2f(80.0, -285);
    glVertex2f(90, -285);
    glEnd();

    glBegin(GL_QUADS); //SCORE GRAY
    glColor3f(0.5803f, 0.5803f, 0.5803f);
    glVertex2f(-200, -230);
    glVertex2f(-200, -300);
    glVertex2f(200, -300);
    glVertex2f(200, -230);
    glEnd();

    glBegin(GL_QUADS); //SCORE BLACK LINE
    glColor3f(0.0f, 0.0f, 0.0);
    glVertex2f(-200, -230);
    glVertex2f(-200, -235);
    glVertex2f(200, -235);
    glVertex2f(200, -230);
    glEnd();

    glBegin(GL_QUADS); //V1
    glColor3f(0, 0, 0);
    glVertex2f(-100.0, -242);
    glVertex2f(-106, -242);
    glVertex2f(-106.0, -288);
    glVertex2f(-100, -288);
    glEnd();

    glBegin(GL_QUADS); //H1
    glColor3f(0, 0, 0);
    glVertex2f(100, -242);
    glVertex2f(-100, -242);
    glVertex2f(-100.0, -245);
    glVertex2f(100, -245);
    glEnd();

    glBegin(GL_QUADS); //H2
    glColor3f(0, 0, 0);
    glVertex2f(100, -285);
    glVertex2f(-100, -285);
    glVertex2f(-100.0, -288);
    glVertex2f(100, -288);
    glEnd();

    glBegin(GL_QUADS); //V2
    glColor3f(0, 0, 0);
    glVertex2f(106.0, -242);
    glVertex2f(100, -242);
    glVertex2f(100.0, -288);
    glVertex2f(106, -288);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(90.0, -245);
    glVertex2f(80, -245);
    glVertex2f(80.0, -253);
    glVertex2f(90, -253);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(-80.0, -245);
    glVertex2f(-90, -245);
    glVertex2f(-90.0, -253);
    glVertex2f(-80, -253);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f(3, -245);
    glVertex2f(-3, -245);
    glVertex2f(-3, -253);
    glVertex2f(3, -253);
    glEnd();

    glBegin(GL_QUADS);// /M+4
    glColor3f(0, 0, 0);
    glVertex2f(27, -253);
    glVertex2f(21, -253);
    glVertex2f(21, -256);
    glVertex2f(27, -256);
    glEnd();

    glBegin(GL_QUADS);// /M+3
    glColor3f(0, 0, 0);
    glVertex2f(21, -253);
    glVertex2f(15, -253);
    glVertex2f(15, -259);
    glVertex2f(21, -259);
    glEnd();

    glBegin(GL_QUADS);// /M+2
    glColor3f(0, 0, 0);
    glVertex2f(15, -256);
    glVertex2f(9, -256);
    glVertex2f(9, -262);
    glVertex2f(15, -262);
    glEnd();

    glBegin(GL_QUADS);// /M+1
    glColor3f(0, 0, 0);
    glVertex2f(9, -259);
    glVertex2f(3, -259);
    glVertex2f(3, -265);
    glVertex2f(9, -265);
    glEnd();

    glBegin(GL_QUADS);// /M
    glColor3f(0, 0, 0);
    glVertex2f(3, -262);
    glVertex2f(-3, -262);
    glVertex2f(-3, -268);
    glVertex2f(3, -268);
    glEnd();

    glBegin(GL_QUADS);// /M-1
    glColor3f(0, 0, 0);
    glVertex2f(-3, -265);
    glVertex2f(-9, -265);
    glVertex2f(-9, -271);
    glVertex2f(-3, -271);
    glEnd();

    glBegin(GL_QUADS);// /M-2
    glColor3f(0, 0, 0);
    glVertex2f(-9, -268);
    glVertex2f(-15, -268);
    glVertex2f(-15, -274);
    glVertex2f(-9, -274);
    glEnd();

    glBegin(GL_QUADS);// /M-3
    glColor3f(0, 0, 0);
    glVertex2f(-15, -271);
    glVertex2f(-21, -271);
    glVertex2f(-21, -277);
    glVertex2f(-15, -277);
    glEnd();

    glBegin(GL_QUADS);// /M-4
    glColor3f(0, 0, 0);
    glVertex2f(-21, -274);
    glVertex2f(-27, -274);
    glVertex2f(-27, -277);
    glVertex2f(-21, -277);
    glEnd();

    glBegin(GL_QUADS);// 1 p1
    glColor3f(0, 0, 0);
    glVertex2f(-9, -262);
    glVertex2f(-27, -262);
    glVertex2f(-27, -265);
    glVertex2f(-9, -265);
    glEnd();

    glBegin(GL_QUADS);// 1 p2
    glColor3f(0, 0, 0);
    glVertex2f(-15, -250);
    glVertex2f(-21, -250);
    glVertex2f(-21, -262);
    glVertex2f(-15, -262);
    glEnd();

    glBegin(GL_QUADS);// 1 p3
    glColor3f(0, 0, 0);
    glVertex2f(-21, -253);
    glVertex2f(-27, -253);
    glVertex2f(-27, -256);
    glVertex2f(-21, -256);
    glEnd();

    glBegin(GL_QUADS);// 2 p1
    glColor3f(0, 0, 0);
    glVertex2f(27, -265);
    glVertex2f(9, -265);
    glVertex2f(9, -268);
    glVertex2f(27, -268);
    glEnd();

    glBegin(GL_QUADS);// 2 p2
    glColor3f(0, 0, 0);
    glVertex2f(27, -268);
    glVertex2f(21, -268);
    glVertex2f(21, -271);
    glVertex2f(27, -271);
    glEnd();

    glBegin(GL_QUADS);// 2 p3
    glColor3f(0, 0, 0);
    glVertex2f(27, -271);
    glVertex2f(9, -271);
    glVertex2f(9, -274);
    glVertex2f(27, -274);
    glEnd();

    glBegin(GL_QUADS);// 2 p4
    glColor3f(0, 0, 0);
    glVertex2f(15, -274);
    glVertex2f(9, -274);
    glVertex2f(9, -277);
    glVertex2f(15, -277);
    glEnd();

    glBegin(GL_QUADS);// 2 p5
    glColor3f(0, 0, 0);
    glVertex2f(27, -277);
    glVertex2f(9, -277);
    glVertex2f(9, -280);
    glVertex2f(27, -280);
    glEnd();

    glBegin(GL_QUADS); // E1
    glColor3f(0, 0, 0);
    glVertex2f(-85.0, -259);
    glVertex2f(-90, -259);
    glVertex2f(-90.0, -282);
    glVertex2f(-85, -282);
    glEnd();

    glBegin(GL_QUADS); // E2
    glColor3f(0, 0, 0);
    glVertex2f(-65.0, -259);
    glVertex2f(-85, -259);
    glVertex2f(-85.0, -262);
    glVertex2f(-65, -262);
    glEnd();

    glBegin(GL_QUADS); // E3
    glColor3f(0, 0, 0);
    glVertex2f(-70.0, -269);
    glVertex2f(-85, -269);
    glVertex2f(-85.0, -272);
    glVertex2f(-70, -272);
    glEnd();

    glBegin(GL_QUADS); // E4
    glColor3f(0, 0, 0);
    glVertex2f(-65.0, -279);
    glVertex2f(-85, -279);
    glVertex2f(-85.0, -282);
    glVertex2f(-65, -282);
    glEnd();

    glBegin(GL_QUADS); // F1
    glColor3f(0, 0, 0);
    glVertex2f(60.0, -259);
    glVertex2f(65, -259);
    glVertex2f(65.0, -282);
    glVertex2f(60, -282);
    glEnd();

    glBegin(GL_QUADS); // F2
    glColor3f(0, 0, 0);
    glVertex2f(85.0, -259);
    glVertex2f(65, -259);
    glVertex2f(65.0, -262);
    glVertex2f(85, -262);
    glEnd();

    glBegin(GL_QUADS); // F3
    glColor3f(0, 0, 0);
    glVertex2f(80.0, -269);
    glVertex2f(65, -269);
    glVertex2f(65.0, -272);
    glVertex2f(80, -272);
    glEnd();

    glPopMatrix();
}

void nomes() {
    glPushMatrix();

    char nome_str[80];
    strcpy_s(nome_str, "marcos e luan");
    GLint nome_length = (GLint)strlen(nome_str);
    GLint nome_cont = 0;

    glScalef(0.1, 0.1, 1);
    glTranslatef(-1200, -1985, 0);

    glPushMatrix();

    glLineWidth(3);
    for (nome_cont = 0; nome_cont < nome_length; nome_cont++) {
        glPushMatrix();
        glColor3ub(1, 1, 1);
        glTranslatef((200 * nome_cont), 0, 0);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, nome_str[nome_cont]);
        glPopMatrix();
    }
    glPopMatrix();


}

void greenRectangle(int x, int y, int width, int height) {

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.255f, 0.0f);
    glVertex2f(x, y);
    glVertex2f(x, height);
    glVertex2f(width, height);
    glVertex2f(width, y);
    glEnd();
}

void generateGreenRectangles() {

    glPushMatrix();
    glTranslatef(0, -SPEED, 0);

    //inicio
      //esquerda
    greenRectangle(-200, -200, -150, 2200);
    greenRectangle(-150, -200, -100, 0);
    greenRectangle(-100, -200, -50, -50);


    //direita
    greenRectangle(150, -200, 200, 2200);
    greenRectangle(100, -200, 150, 0);
    greenRectangle(50, -200, 100, -50);



    //meio 1
    greenRectangle(-150, 200, -100, 600);//esquerda
    greenRectangle(100, 200, 150, 600);//direita

    //meio2
    greenRectangle(-25, 700, 25, 950);


    /*//fim
      //esquerda
    greenRectangle(-200, 200, -150, 600);
    greenRectangle(-150, 400, -100, 600);
    greenRectangle(-100, 450, -50, 600);


      //direita
    greenRectangle(150, 200, 200, 600);
    greenRectangle(100, 400, 150, 600);
    greenRectangle(50, 450, 100, 600);*/
    glPopMatrix();
}



void generateGreenRectangle(int x, int y) {
    /*if (firstFrame) {
        colisors[colisorsCounter][VISIBLE] = 1;
        colisors[colisorsCounter][TYPE] = TERRAIN_TYPE;
        colisorsCounter++;
    }

    for (int colisorCounter = 0; colisorCounter < colisorsCounter; colisorCounter++) {
        if (colisors[colisorCounter][VISIBLE] == 1 && colisors[colisorCounter][TYPE] == TERRAIN_TYPE) {
            addShipToColisors(x, y, colisorCounter);
            ship(colisorCounter);
        }
    }*/
}







void display() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0745f, 0.4431f, 0.203f, 1.0f);  // cor do fundo
    glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo
    glTranslatef(400 / 2, 400 / 2, 0.0f); // largura e altura da janela por 2 

    ocean();
    generateGreenRectangles();

    HORIZONTAL_SPEED = HORIZONTAL_SPEED + 1;
    rotatePropeller++;
    if (rotatePropeller == 8) {
        rotatePropeller = 0;
    }
    //SPEED++;


    generateHouse(100, -80);
    generateFuel(60, 180);
    generateTree(-100, -60);
    generateShip(50, 60);
    generateHelicopter(-50, 125);



    /* glBegin(GL_QUADS);
     glVertex2f(AIRPLANE_POSITION[X], AIRPLANE_POSITION[Y]);
     glVertex2f(AIRPLANE_POSITION[X], AIRPLANE_POSITION[HEIGHT]);
     glVertex2f(AIRPLANE_POSITION[WIDTH], AIRPLANE_POSITION[HEIGHT]);
     glVertex2f(AIRPLANE_POSITION[WIDTH], AIRPLANE_POSITION[Y]);
     glEnd();*/

    generateBullet(-6, -180);
    generateAirplane(-50, -100);

    score();
    nomes();
    glPushMatrix();

    glTranslatef(-10, 100, 0);

    glBegin(GL_QUADS); // pointer
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(ACTUAL_FUEL, -253);
    glVertex2f(ACTUAL_FUEL - 10, -253);
    glVertex2f(ACTUAL_FUEL - 10, -285);
    glVertex2f(ACTUAL_FUEL, -285);
    glEnd();
    glPopMatrix();

    firstFrame = false;

    glFlush(); // executa o desenho 
}


