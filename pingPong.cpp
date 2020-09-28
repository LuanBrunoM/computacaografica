#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define janela_altura 420
#define janela_largura 640
#define PI 3.14159265359

float player1X;
float player1Y;
float player2X;
float player2Y;
float ballX;
float ballY;
float stepY;
float stepX;

void display(void);
void reshape(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void specialKeys(int tecla, int x, int y);
void update(int value);
void startGame();

int main(int argc, char** argv) {

	startGame();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(janela_largura, janela_altura);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Ping Pong");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(&specialKeys);
	glutKeyboardFunc(&keyboard);
	glutTimerFunc(100, update, 1);
	glutMainLoop();

	return 0;
}

void startGame() {
	player1X = -janela_largura / 2;
	player1Y = 150 / 2;

	player2X = janela_largura / 2 - 20;
	player2Y = 150 / 2;

	ballX = 0;
	ballY = 0;

	stepX = 10;
	stepY = 10;
}


void update(int value) {
	if (ballX > (janela_largura / 2) - 20 || ballX < -((janela_largura / 2) - 20)) { startGame(); }
	if (ballY > janela_altura - 20 || ballY < -((janela_altura / 2) - 20)) { stepY = -stepY; }
	if (ballY >= player2Y && ballY <= player2Y + 150 && ballX == player2X) { stepX = -stepX; }
	if (ballY >= player1Y && ballY <= player1Y + 150 && ballX == player1X + 20) { stepX = -stepX; }

	ballX += stepX;
	ballY += stepY;

	glutPostRedisplay();
	glutTimerFunc(100, update, 1);
}

void keyboard(unsigned char tecla, int x, int y) {
	if (tecla == 'w') {
		if (player1Y < (janela_altura / 2) + 90) {
			player1Y += 10;
		}
	}
	if (tecla == 's') {
		if (player1Y > -(janela_altura / 2)) {
			player1Y -= 10;
		}
	}

	glutPostRedisplay();
}

void specialKeys(int tecla, int x, int y) {
	if (tecla == GLUT_KEY_UP) {

		if (player2Y < (janela_altura / 2) + 90) {
			player2Y += 10;
		}
	}
	if (tecla == GLUT_KEY_DOWN) {

		if (player2Y > -(janela_altura / 2)) {
			player2Y -= 10;
		}

	}

	glutPostRedisplay();
}

void draw() {
	glPushMatrix();
	glTranslatef(player1X, player1Y, 0);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);
	glVertex2f(0, 130);
	glVertex2f(18, 130);
	glVertex2f(18, 0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(player2X, player2Y, 0);

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(0, 0);
	glVertex2f(0, 130);
	glVertex2f(18, 130);
	glVertex2f(18, 0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(ballX, ballY, 0);

	GLfloat circ_pnt = 100;
	GLfloat ang;

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * 10, sin(ang) * 15);
	}
	glEnd();

	glPopMatrix();
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);
	glViewport(0, 0, janela_largura, janela_altura);
	draw();

	glFlush();
}

void reshape(GLsizei, GLsizei) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, janela_largura, 0, janela_largura);
	glMatrixMode(GL_MODELVIEW);
}

