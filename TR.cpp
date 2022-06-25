#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok 3
// Sindy Cristine Baun					(672020052)
// Albertus Bima Krisnawan				(672020095)
// Mikha Kurnia Anggi Purbaningtyas		(672020109)
// David Alvin Nugroho					(672020121)
// Tessalonica Putry Avrylya			(672020167)

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0, terbang = 25.0;

void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

struct Motion {
	bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void init() {
	glClearColor(0.529, 0.807, 0.921, 0.0);
	glutSetCursor(GLUT_CURSOR_NONE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glutWarpPointer(width / 2, height / 2);
}

void ground() {
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(-1000.0, 0, -1000.0);

	glColor3f(0.6f, 0.6f, 0.6f);
	glVertex3f(1000.0, 0, -1000.0);

	glColor3f(0.6f, 0.6f, 0.6f);
	glVertex3f(1000.0, 0, 1000.0);

	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(-1000.0, 0, 1000.0);
	glEnd();
}

void dasar() {
	glPushMatrix();
	glTranslatef(0.0, 40, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(-100.0, 250.0, 100);
	glVertex3f(100.0, 250.0, 100);
	glVertex3f(250.0, 100.0, 100);
	glVertex3f(250.0, -100.0, 100);
	glVertex3f(100.0, -250.0, 100);
	glVertex3f(-100.0, -250.0, 100);
	glVertex3f(-250.0, -100.0, 100);
	glVertex3f(-250.0, 100.0, 100);
	glEnd();
	glPopMatrix();

	//TEPI
	glPushMatrix();
	glTranslatef(0, 40, 150);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-102.0, -100.0, 100);
	glVertex3f(-102.0, 100.0, 100);
	glVertex3f(102.0, 100.0, 100);
	glVertex3f(102.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 40, -350);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-102.0, -100.0, 100);
	glVertex3f(-102.0, 100.0, 100);
	glVertex3f(102.0, 100.0, 100);
	glVertex3f(102.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(104, 40, 105);
	glRotatef(45, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-105.0, -100.0, 100);
	glVertex3f(-105.0, 100.0, 100);
	glVertex3f(105.0, 100.0, 100);
	glVertex3f(105.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-243, 40, -247);
	glRotatef(45, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-105.0, -100.0, 100);
	glVertex3f(-105.0, 100.0, 100);
	glVertex3f(105.0, 100.0, 100);
	glVertex3f(105.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-104, 40, 105);
	glRotatef(-45, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-105.0, -100.0, 100);
	glVertex3f(-105.0, 100.0, 100);
	glVertex3f(105.0, 100.0, 100);
	glVertex3f(105.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(243, 40, -247);
	glRotatef(-45, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-105.0, -100.0, 100);
	glVertex3f(-105.0, 100.0, 100);
	glVertex3f(105.0, 100.0, 100);
	glVertex3f(105.0, -100.0, 100);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-350, 40, z_geser);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-102.0, -100.0, 100);
	glVertex3f(-102.0, 100.0, 100);
	glVertex3f(102.0, 100.0, 100);
	glVertex3f(102.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(150, 40, 0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-102.0, -100.0, 100);
	glVertex3f(-102.0, 100.0, 100);
	glVertex3f(102.0, 100.0, 100);
	glVertex3f(102.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	//KANAN KIRI
	glPushMatrix();
	glTranslatef(250.0, 0.0, -10.0);
	glRotatef(45, 0.0, .0, 1.0);
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(-100.0, -100.0, 100);
	glVertex3f(-100.0, 100.0, 100);
	glVertex3f(100.0, 100.0, 100);
	glVertex3f(100.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(250.0, 0.0, -0.0);
	glRotatef(45, 0.0, .0, 1.0);
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(-100.0, -100.0, 100);
	glVertex3f(-100.0, 100.0, 100);
	glVertex3f(100.0, 100.0, 100);
	glVertex3f(100.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(250.0, 0.0, -190.0);
	glRotatef(45, 0.0, .0, 1.0);
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(-100.0, -100.0, 100);
	glVertex3f(-100.0, 100.0, 100);
	glVertex3f(100.0, 100.0, 100);
	glVertex3f(100.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(250.0, 0.0, -200.0);
	glRotatef(45, 0.0, .0, 1.0);
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(-100.0, -100.0, 100);
	glVertex3f(-100.0, 100.0, 100);
	glVertex3f(100.0, 100.0, 100);
	glVertex3f(100.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(250.0, 0.0, 95.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(45.0, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(-100.0, -5.0, 100);
	glVertex3f(-100.0, 5.0, 100);
	glVertex3f(100.0, 5.0, 100);
	glVertex3f(100.0, -5.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(250.0, 0.0, -95);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(45.0, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(-100.0, -5.0, 100);
	glVertex3f(-100.0, 5.0, 100);
	glVertex3f(100.0, 5.0, 100);
	glVertex3f(100.0, -5.0, 100);
	glEnd();
	glPopMatrix();


	//TIDUR
	glPushMatrix();
	glTranslatef(360, -80, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-10.0, -100.0, 100);
	glVertex3f(-10.0, 100.0, 100);
	glVertex3f(10.0, 100.0, 100);
	glVertex3f(10.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(340, -60, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-10.0, -100.0, 100);
	glVertex3f(-10.0, 100.0, 100);
	glVertex3f(10.0, 100.0, 100);
	glVertex3f(10.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(320, -40, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-10.0, -100.0, 100);
	glVertex3f(-10.0, 100.0, 100);
	glVertex3f(10.0, 100.0, 100);
	glVertex3f(10.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(300, -20, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-10.0, -100.0, 100);
	glVertex3f(-10.0, 100.0, 100);
	glVertex3f(10.0, 100.0, 100);
	glVertex3f(10.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(280, 0, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-10.0, -100.0, 100);
	glVertex3f(-10.0, 100.0, 100);
	glVertex3f(10.0, 100.0, 100);
	glVertex3f(10.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(260, 20, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-10.0, -100.0, 100);
	glVertex3f(-10.0, 100.0, 100);
	glVertex3f(10.0, 100.0, 100);
	glVertex3f(10.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	//TEGAK
	glPushMatrix();
	glTranslatef(270, 10, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-10.0, -100.0, 100);
	glVertex3f(-10.0, 100.0, 100);
	glVertex3f(10.0, 100.0, 100);
	glVertex3f(10.0, -100.0, 100);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(250, 30, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-10.0, -100.0, 100);
	glVertex3f(-10.0, 100.0, 100);
	glVertex3f(10.0, 100.0, 100);
	glVertex3f(10.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(230, 50, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-10.0, -100.0, 100);
	glVertex3f(-10.0, 100.0, 100);
	glVertex3f(10.0, 100.0, 100);
	glVertex3f(10.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(210, 70, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-10.0, -100.0, 100);
	glVertex3f(-10.0, 100.0, 100);
	glVertex3f(10.0, 100.0, 100);
	glVertex3f(10.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(190, 90, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-10.0, -100.0, 100);
	glVertex3f(-10.0, 100.0, 100);
	glVertex3f(10.0, 100.0, 100);
	glVertex3f(10.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(170, 110, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-10.0, -100.0, 100);
	glVertex3f(-10.0, 100.0, 100);
	glVertex3f(10.0, 100.0, 100);
	glVertex3f(10.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(150, 130, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-10.0, -100.0, 100);
	glVertex3f(-10.0, 100.0, 100);
	glVertex3f(10.0, 100.0, 100);
	glVertex3f(10.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	//taneman
	glPushMatrix();
	glColor3f(0.16, 0.66, 0.11);
	glTranslatef(-270, 10, 0);
	glutSolidSphere(90, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.87, 0.24);
	glTranslatef(100, 10, 270);
	glutSolidSphere(90, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.16, 0.66, 0.11);
	glTranslatef(-100, 10, 270);
	glutSolidSphere(90, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.87, 0.24);
	glTranslatef(100, 10, -270);
	glutSolidSphere(90, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.16, 0.66, 0.11);
	glTranslatef(-100, 10, -270);
	glutSolidSphere(90, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.87, 0.24);
	glTranslatef(0, 10, 270);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.87, 0.24);
	glTranslatef(0, 40, -270);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.16, 0.66, 0.11);
	glTranslatef(0, 10, -300);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.14, 0.55, 0.09);
	glTranslatef(0, 40, 300);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.87, 0.24);
	glTranslatef(250, 10, 130);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.16, 0.66, 0.11);
	glTranslatef(180, 40, -200);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.87, 0.24);
	glTranslatef(250, 10, -130);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.14, 0.55, 0.09);
	glTranslatef(180, 40, 200);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.14, 0.55, 0.09);
	glTranslatef(-200, 10, 250);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.16, 0.66, 0.11);
	glTranslatef(-150, 40, -270);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.87, 0.24);
	glTranslatef(250, 10, -250);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.16, 0.66, 0.11);
	glTranslatef(-150, 40, 280);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.87, 0.24);
	glTranslatef(-250, 10, 130);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.16, 0.66, 0.11);
	glTranslatef(-180, 40, -200);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.87, 0.24);
	glTranslatef(-250, 10, -130);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.16, 0.66, 0.11);
	glTranslatef(-180, 40, 200);
	glutSolidSphere(80, 5, 5);
	glEnd();
	glPopMatrix();

}

void pagar_tegak_lantai1() {

	glColor3f(0.941, 0.262, 0);
	glPushMatrix();
	glTranslatef(354.5, 210, 152);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 40.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(144, 210, 362);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 40.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-144, 210, 362);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 40.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-354.5, 210, 152);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 40.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-354.5, 210, -145);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 40.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(144, 210, -362);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 40.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-144, 210, -362);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 40.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(354.5, 210, -145);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 40.0f, 32, 32);
	glEnd();
	glPopMatrix();
}

void pagar_lantai1() {
	pagar_tegak_lantai1();

	glColor3f(0.941, 0.262, 0);

	//pagar kiri
	glPushMatrix();
	glTranslatef(140, 220, 362);
	glRotatef(-90, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 280, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(140, 230, 362);
	glRotatef(-90, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 280.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(140, 240, 362);
	glRotatef(-90, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 280.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//pagar kanan
	glPushMatrix();
	glTranslatef(140, 220, -362);
	glRotatef(-90, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 280.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(140, 230, -362);
	glRotatef(-90, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 280.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(140, 240, -362);
	glRotatef(-90, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 280.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//pagar_belakang
	glPushMatrix();
	glTranslatef(-352, 220, -141.5);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 300.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-352, 230, -141.5);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 300.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-352, 240, -141.5);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 300.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//pojok kiri depan
	glPushMatrix();
	glTranslatef(355.5, 220, 155.5);
	glRotatef(-45, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 295.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(355.5, 230, 155.5);
	glRotatef(-45, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 295.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(355.5, 240, 155.5);
	glRotatef(-45, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 295.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//pojok kanan balakang
	glPushMatrix();
	glTranslatef(-142.5, 220, -360);
	glRotatef(-45, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 300.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-142, 230, -360);
	glRotatef(-45, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 300.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-142, 240, -360);
	glRotatef(-45, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 300.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//pojok kanan depan
	glPushMatrix();
	glTranslatef(140, 220, -362);
	glRotatef(45, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 300.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(140, 230, -362);
	glRotatef(45, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 300.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(140, 240, -362);
	glRotatef(45, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 300.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//pojok kiri belakang
	glPushMatrix();
	glTranslatef(-357, 220, 152);
	glRotatef(45, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 295.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-357, 230, 152);
	glRotatef(45, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 295.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-357, 240, 152);
	glRotatef(45, 0.0, 1.0, 0.0);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 295.0f, 32, 32);
	glEnd();
	glPopMatrix();
}


void luar() {
	//kiri
	glPushMatrix();
	glTranslatef(0, 469.5, 22.5);
	glRotatef(0, 0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.815, 0.458);
	glVertex3f(-100.0, -100.0, 100);
	glVertex3f(-100.0, 60.0, 100);
	glVertex3f(100.0, 60.0, 100);
	glVertex3f(100.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	//belakang
	glPushMatrix();
	glTranslatef(0, 469.5, 22.5);
	glRotatef(-90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.815, 0.458);
	glVertex3f(-155.0, -100.0, 100);
	glVertex3f(-155.0, 60.0, 100);
	glVertex3f(100.0, 60.0, 100);
	glVertex3f(100.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	//depan
	glPushMatrix();
	glTranslatef(0, 469.5, 22.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.815, 0.458);
	glVertex3f(-100.0, -100.0, 100);
	glVertex3f(-100.0, 60.0, 100);
	glVertex3f(155.0, 60.0, 100);
	glVertex3f(155.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	//kanan
	glPushMatrix();
	glTranslatef(0, 469.5, -232.5);
	glRotatef(0, 0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.815, 0.458);
	glVertex3f(-100.0, -100.0, 100);
	glVertex3f(-100.0, 60.0, 100);
	glVertex3f(100.0, 60.0, 100);
	glVertex3f(100.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	//PILAR POJOK
	//pilar depan kiri
	glPushMatrix();
	glTranslatef(100.5, 369.5, 120.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//pilar belakakang kiri
	glPushMatrix();
	glTranslatef(-99, 369.5, 120.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//pilar depan kanan
	glPushMatrix();
	glTranslatef(100.5, 369.5, -131.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//pilar belakang kanan
	glPushMatrix();
	glTranslatef(-96, 369.5, -131.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//PILAR 2nd

	// kanan depan
	glPushMatrix();
	glTranslatef(36, 369.5, -131.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	// kanan belakang
	glPushMatrix();
	glTranslatef(-36, 369.5, -131.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//kiri depan
	glPushMatrix();
	glTranslatef(36, 369.5, 120.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//kanan belakang
	glPushMatrix();
	glTranslatef(-36, 369.5, 120.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//depan kiri
	glPushMatrix();
	glTranslatef(100.5, 369.5, 48);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//depan kanan
	glPushMatrix();
	glTranslatef(100.5, 369.5, -48);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//belakakang kiri
	glPushMatrix();
	glTranslatef(-99, 369.5, 48);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//belakakang kanan
	glPushMatrix();
	glTranslatef(-99, 369.5, -48);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//PINTU
	//pintu depan
	glPushMatrix();
	glTranslatef(100.5, 169.5, 393);
	glRotatef(90.0, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(350, 200);
	glVertex2f(350, 300);
	glVertex2f(395, 300);
	glVertex2f(395, 200);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(396, 200);
	glVertex2f(396, 300);
	glVertex2f(436, 300);
	glVertex2f(436, 200);
	glEnd();
	glPopMatrix();

	//pintu belakang
	glPushMatrix();
	glTranslatef(-101, 169.5, 393);
	glRotatef(90.0, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(350, 200);
	glVertex2f(350, 300);
	glVertex2f(395, 300);
	glVertex2f(395, 200);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(396, 200);
	glVertex2f(396, 300);
	glVertex2f(436, 300);
	glVertex2f(436, 200);
	glEnd();
	glPopMatrix();

	//pintu kiri
	glPushMatrix();
	glTranslatef(-393, 169.5, 123);
	glRotatef(0.0, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(355, 200);
	glVertex2f(355, 300);
	glVertex2f(395, 300);
	glVertex2f(395, 200);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(395, 200);
	glVertex2f(395, 300);
	glVertex2f(430, 300);
	glVertex2f(430, 200);
	glEnd();
	glPopMatrix();

	//pintu kanan
	glPushMatrix();
	glTranslatef(-393, 169.5, -133);
	glRotatef(0.0, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(355, 200);
	glVertex2f(355, 300);
	glVertex2f(395, 300);
	glVertex2f(395, 200);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(395, 200);
	glVertex2f(395, 300);
	glVertex2f(430, 300);
	glVertex2f(430, 200);
	glEnd();
	glPopMatrix();

	//PEMBATAS

	//belakang
	//1
	glPushMatrix();
	glTranslatef(-105, 473.5, -138.5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 265.0f, 4, 4);
	glEnd();
	glPopMatrix();
	//2
	glPushMatrix();
	glTranslatef(-105, 484, -138.5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 265.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//depan
	glPushMatrix();
	glTranslatef(106.5, 473.5, -138.5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 265.0f, 4, 4);
	glEnd();
	glPopMatrix();
	//2
	glPushMatrix();
	glTranslatef(106.5, 484, -138.5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 265.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//kiri
	glPushMatrix();
	glTranslatef(-109.5, 473.5, -134.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 220.0f, 4, 4);
	glEnd();
	glPopMatrix();
	//2
	glPushMatrix();
	glTranslatef(-109.5, 484, -134.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 220.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//kanan
	glPushMatrix();
	glTranslatef(-109.5, 473.5, 123.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 220.0f, 4, 4);
	glEnd();
	glPopMatrix();
	//2
	glPushMatrix();
	glTranslatef(-109.5, 484, 123.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 220.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//jendela

	//kiri
	glPushMatrix();
	glTranslatef(-44.5, 420, 23.5);
	glRotatef(90, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 100);
	glVertex3f(0.0, 45.0, 100);
	glVertex3f(45.0, 45.0, 100);
	glVertex3f(45.0, 0.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(90.5, 420, 23.5);
	glRotatef(90, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 100);
	glVertex3f(0.0, 45.0, 100);
	glVertex3f(45.0, 45.0, 100);
	glVertex3f(45.0, 0.0, 100);
	glEnd();
	glPopMatrix();

	//kanan
	glPushMatrix();
	glTranslatef(-44.5, 420, -233);
	glRotatef(90, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 100);
	glVertex3f(0.0, 45.0, 100);
	glVertex3f(45.0, 45.0, 100);
	glVertex3f(45.0, 0.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(90.5, 420, -233);
	glRotatef(90, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 100);
	glVertex3f(0.0, 45.0, 100);
	glVertex3f(45.0, 45.0, 100);
	glVertex3f(45.0, 0.0, 100);
	glEnd();
	glPopMatrix();

	//depan
	glPushMatrix();
	glTranslatef(1, 414.5, -65);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 100);
	glVertex3f(0.0, 50.0, 100);
	glVertex3f(50.0, 50.0, 100);
	glVertex3f(50.0, 0.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, 414.5, 109);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 100);
	glVertex3f(0.0, 50.0, 100);
	glVertex3f(50.0, 50.0, 100);
	glVertex3f(50.0, 0.0, 100);
	glEnd();
	glPopMatrix();

	//belakang
	glPushMatrix();
	glTranslatef(-200.5, 414.5, -65);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 100);
	glVertex3f(0.0, 50.0, 100);
	glVertex3f(50.0, 50.0, 100);
	glVertex3f(50.0, 0.0, 100);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200.5, 414.5, 109);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 100);
	glVertex3f(0.0, 50.0, 100);
	glVertex3f(50.0, 50.0, 100);
	glVertex3f(50.0, 0.0, 100);
	glEnd();
	glPopMatrix();

	//BAWAH JENDELA
	//depan
	glPushMatrix();
	glTranslatef(106.5, 408.5, 42.5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 90.0f, 4, 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(106.5, 408.5, -143);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 100.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//belakang
	glPushMatrix();
	glTranslatef(-102.5, 408.5, 42.5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 90.0f, 4, 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-102.5, 408.5, -143);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 100.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//kanan
	glPushMatrix();
	glTranslatef(29.5, 473.5 - 65, -139);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 80.0f, 4, 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-106.5, 473.5 - 65, -139);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 75.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//kiri
	glPushMatrix();
	glTranslatef(29.5, 473.5 - 65, 128.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 80.0f, 4, 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-106.5, 473.5 - 65, 128.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 75.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//DETAIL
	//DEPAN


	//BELAKANG
	//bola hitam

	//atas(dari kiri)
	//1
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, -132.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//2
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, -49);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//3
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, 48);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//4
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, 120.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//bawah belakang
	glPushMatrix();
	glTranslatef(2.5, -64.5, 0);

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, -132.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//2
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, -49);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//3
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, 48);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//4
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, 120.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();
	glPopMatrix();



	//Depan

	glPushMatrix();
	glTranslatef(220.5, 0, 0);
	//atas(dari kiri)
	//1
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, -132.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//2
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, -49);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//3
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, 48);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//4
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, 120.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//bawah(dari kiri)
	//1
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5 - 64.5, 109.5, -132.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//2
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5 - 64.5, 109.5, -49);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//3
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5 - 64.5, 109.5, 48);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//4
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5 - 64.5, 109.5, 120.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPopMatrix();


	//kanan

	//1
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-99.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-35.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(36.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(105.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//2
	glPushMatrix();
	glTranslatef(0, -65, 5);
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-99.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-35.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(36.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(105.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPopMatrix();

	//kiri

	glPushMatrix();
	glTranslatef(0, 0, -267);

	//1
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-99.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-35.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(36.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(105.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//2
	glPushMatrix();
	glTranslatef(0, -65, 5);
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-99.5, 128 - 9.5, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-35.5, 128 - 9.5, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(36.5, 128 - 9.5, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(105.5, 128 - 9.5, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//ORNAMEN PINTU
	//PEMBATAS DEPAN
	glPushMatrix();
	glTranslatef(102, 369.5, -2.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//PEMBATAS BELAKANG
	glPushMatrix();
	glTranslatef(-101, 369.5, -2.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//PEMBATAS KIRI
	glPushMatrix();
	glTranslatef(0, 369.5, 123);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//PEMBATAS KANAN
	glPushMatrix();
	glTranslatef(0, 369.5, -133);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
	glEnd();
	glPopMatrix();
}




void lantai1() {
	luar();

	//kanan
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-99.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//atap lantai 1
	glPushMatrix();
	glColor3f(1, 0.882, 0.658);
	glTranslatef(0, 534.5, 0);
	glScalef(1.8, 0.05, 1.8);
	glutSolidCube(200);
	glPopMatrix();

}


void lantai1_fix() {
	glPushMatrix();
	glScalef(1.6, 1.35, 1.6);
	glTranslatef(0, -219, 0);
	lantai1();
	glPopMatrix();
}

void pagar_lantai2() {
	//kiri
	glColor3f(0.941, 0.262, 0);
	glPushMatrix();
	glTranslatef(228.5, 442, 234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-228.5, 442, 234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(200, 442, 234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(160, 442, 234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(120, 442, 234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 442, 234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 442, 234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 442, 234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40, 442, 234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-80, 442, 234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-120, 442, 234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-160, 442, 234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200, 442, 234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 455, 234);
	glScalef(457, 5, 5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 445, 234);
	glScalef(457, 5, 5);
	glutSolidCube(1);
	glPopMatrix();

	//kanan
	glColor3f(0.941, 0.262, 0);
	glPushMatrix();
	glTranslatef(228.5, 442, -234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-228.5, 442, -234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(200, 442, -234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(160, 442, -234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(120, 442, -234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 442, -234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 442, -234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 442, -234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40, 442, -234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-80, 442, -234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-120, 442, -234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();;
	glTranslatef(-160, 442, -234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200, 442, -234);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 455, -234);
	glScalef(457, 5, 5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 445, -234);
	glScalef(457, 5, 5);
	glutSolidCube(1);
	glPopMatrix();

	//depan
	glPushMatrix();
	glTranslatef(228.5, 442, 200);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(228.5, 442, 160);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(228.5, 442, 120);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(228.5, 442, 80);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(228.5, 442, 40);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(228.5, 442, 0);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(228.5, 442, -40);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(228.5, 442, -80);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(228.5, 442, -120);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(228.5, 442, -160);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(228.5, 442, -200);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(228.5, 455, 0);
	glScalef(5, 5, 468);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(228.5, 445, 0);
	glScalef(5, 5, 468);
	glutSolidCube(1);
	glPopMatrix();

	//belakang
	glPushMatrix();
	glTranslatef(-228.5, 442, 200);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-228.5, 442, 160);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-228.5, 442, 120);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-228.5, 442, 80);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-228.5, 442, 40);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-228.5, 442, 0);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-228.5, 442, -40);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-228.5, 442, -80);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-228.5, 442, -120);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-228.5, 442, -160);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-228.5, 442, -200);
	glScalef(0.2, 1, 0.2);
	glutSolidCube(30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-228.5, 455, 0);
	glScalef(5, 5, 468);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-228.5, 445, 0);
	glScalef(5, 5, 468);
	glutSolidCube(1);
	glPopMatrix();
}


void lantai2() {

	luar();

	//CAGAK

	//depan
	glPushMatrix();
	glTranslatef(222, 369.5, -92.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.852, 0.323, 0.119);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 135.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(222, 369.5, 92.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.852, 0.323, 0.119);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 135.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//belakang
	glPushMatrix();
	glTranslatef(-223, 369.5, -92.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.852, 0.323, 0.119);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 132.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-223, 369.5, 92.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.852, 0.323, 0.119);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 132.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//kiri
	glPushMatrix();
	glTranslatef(0, 369.5, 220);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.852, 0.323, 0.119);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 135.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//kanan
	glPushMatrix();
	glTranslatef(0, 369.5, -224);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 132.0f, 32, 32);
	glEnd();
	glPopMatrix();



	//DALEMAN

	//STACK
	glPushMatrix();
	glColor3f(0.852, 0.323, 0.119);
	glTranslatef(0, 372.5, 0);
	glScalef(1.8, 0.1, 1.8);
	glutSolidCube(70);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.873, 0.344, 0.139);
	glTranslatef(0, 377.5, 0);
	glScalef(1.8, 0.1, 1.8);
	glutSolidCube(65);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.894, 0.365, 0.159);
	glTranslatef(0, 382.5, 0);
	glScalef(1.8, 0.1, 1.8);
	glutSolidCube(60);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.915, 0.386, 0.179);
	glTranslatef(0, 387.5, 0);
	glScalef(1.8, 0.1, 1.8);
	glutSolidCube(55);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.936, 0.407, 0.199);
	glTranslatef(0, 392.5, 0);
	glScalef(1.8, 0.1, 1.8);
	glutSolidCube(50);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.957, 0.428, 0.219);
	glTranslatef(0, 397.5, 0);
	glScalef(1.8, 0.1, 1.8);
	glutSolidCube(45);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.978, 0.449, 0.239);
	glTranslatef(0, 400.5, 0);
	glScalef(1.8, 0.1, 1.8);
	glutSolidCube(40);
	glPopMatrix();

	//bayangan
	glPushMatrix();
	glColor4f(0.3, 0.3, 0.3, 0.1);
	glTranslatef(0, 403.5, 0);
	glScalef(1.8, 0.1, 1.8);
	glutSolidSphere(3.0, 2, 20);
	glPopMatrix();


	//ORNAMEN
	glPushMatrix();
	glColor3f(0.9, 0.9, 0.11);
	glTranslatef(0, 402.5 + 22.5, 0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	glutSolidTorus(5.0, 10.0, 20, 20);
	glPopMatrix();

	//LAMPU
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 492.5, 0);
	glutSolidSphere(10.0, 30, 30);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 500.5, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 1.0f, 1.0f, 30.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//cahaya
	glPushMatrix();
	glColor4f(1, 1, 1.0, 0.1);
	glTranslatef(0, 490, 0);
	int r = 1;
	for (int i = 0; i < 30; i++) {
		glutSolidSphere(10 + r, 30, 30);
		r = r + 1;
	}
	glEnd();
	glPopMatrix();

	//atap lantai 2
	glPushMatrix();
	glColor3f(1, 0.882, 0.658);
	glTranslatef(0, 534.5, 0);
	glScalef(1.8, 0.05, 1.8);
	glutSolidCube(170);
	glPopMatrix();


}


void atap_lt2() {

	//kiri
	glPushMatrix();
	glTranslatef(0, 580 - 31, -10);
	glRotatef(-45, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.29f, 0.70f, 0.76f);
	glVertex3f(-230.0, -200.0, 135);
	glVertex3f(-150.0, -125.0, 100);
	glVertex3f(150.0, -125.0, 100);
	glVertex3f(230.0, -200.0, 135);
	glEnd();
	glPopMatrix();

	//kanan
	glPushMatrix();
	glTranslatef(0, 720 - 31, -130);
	glRotatef(45, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.29f, 0.70f, 0.76f);
	glVertex3f(-230.0, -200.0, 65);
	glVertex3f(-150.0, -125.0, 100);
	glVertex3f(150.0, -125.0, 100);
	glVertex3f(230.0, -200.0, 65);
	glEnd();
	glPopMatrix();

	//depan
	glPushMatrix();
	glTranslatef(-8, 580 - 31, 0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.29f, 0.70f, 0.76f);
	glVertex3f(-230.0, -200.0, 135);
	glVertex3f(-150.0, -125.0, 100);
	glVertex3f(150.0, -125.0, 100);
	glVertex3f(225.0, -200.0, 135);
	glEnd();
	glPopMatrix();

	//belakang
	glPushMatrix();
	glTranslatef(-130, 720 - 31, 0);
	glRotatef(-45, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.29f, 0.70f, 0.76f);
	glVertex3f(-230.0, -200.0, 65);
	glVertex3f(-150.0, -125.0, 100);
	glVertex3f(150.0, -125.0, 100);
	glVertex3f(225.0, -200.0, 65);
	glEnd();
	glPopMatrix();

}


void lantai3() {

	//BAWAH JENDELA
//depan
	glPushMatrix();
	glTranslatef(106.5, 408.5, 42.5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 90.0f, 4, 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(106.5, 408.5, -143);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 100.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//belakang
	glPushMatrix();
	glTranslatef(-102.5, 408.5, 42.5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 90.0f, 4, 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-102.5, 408.5, -143);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 100.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//kanan
	glPushMatrix();
	glTranslatef(29.5, 473.5 - 65, -139);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 80.0f, 4, 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-106.5, 473.5 - 65, -139);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 75.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//kiri
	glPushMatrix();
	glTranslatef(29.5, 473.5 - 65, 128.5);
	glRotatef(90, 0.0, 1.0, 0.0);

	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 80.0f, 4, 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-106.5, 473.5 - 65, 128.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 75.0f, 4, 4);
	glEnd();
	glPopMatrix();


	//DINDING
	//dinding bagian kiri
	glPushMatrix();
	glTranslatef(0, 469.5, 22.5);
	glRotatef(0, 0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.815, 0.458);
	glVertex3f(-100.0, -100.0, 100);
	glVertex3f(-100.0, 60.0, 100);
	glVertex3f(100.0, 60.0, 100);
	glVertex3f(100.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	//dinding bagian belakang
	glPushMatrix();
	glTranslatef(0, 469.5, 22.5);
	glRotatef(-90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.815, 0.458);
	glVertex3f(-155.0, -100.0, 100);
	glVertex3f(-155.0, 60.0, 100);
	glVertex3f(100.0, 60.0, 100);
	glVertex3f(100.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	//dinding bagian depan kanan
	glPushMatrix();
	glTranslatef(0, 469.5, 22.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.815, 0.458);
	glVertex3f(-100.0, -100.0, 100);
	glVertex3f(-100.0, -15.0, 100);
	glVertex3f(-20.0, -15.0, 100);
	glVertex3f(-20.0, -100, 100);
	glEnd();
	glPopMatrix();

	//dinding bagian depan kiri
	glPushMatrix();
	glTranslatef(0, 469.5, 22.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.815, 0.458);
	glVertex3f(65.0, -100.0, 100);
	glVertex3f(65.0, -15.0, 100);
	glVertex3f(155.0, -15.0, 100);
	glVertex3f(155.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	//dinding bagian depan atas
	glPushMatrix();
	glTranslatef(0, 469.5, 22.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.815, 0.458);
	glVertex3f(-100.0, -15.0, 100);
	glVertex3f(-100.0, 60.0, 100);
	glVertex3f(155.0, 60.0, 100);
	glVertex3f(155.0, -15.0, 100);
	glEnd();
	glPopMatrix();

	//dinding bagian kanan
	glPushMatrix();
	glTranslatef(0, 469.5, -232.5);
	glRotatef(0, 0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.815, 0.458);
	glVertex3f(-100.0, -100.0, 100);
	glVertex3f(-100.0, 60.0, 100);
	glVertex3f(100.0, 60.0, 100);
	glVertex3f(100.0, -100.0, 100);
	glEnd();
	glPopMatrix();

	//-=-=-=-=-=-=--=-=-==-=
	//PILAR X
	//bagian ti tidur kiri 1
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(0, 457, 122.5);
	glScalef(2, 0.05, 0.05);
	glutSolidCube(100);
	glPopMatrix();

	//bagian ti tidur kiri 2
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(0, 472, 122.5);
	glScalef(2, 0.05, 0.05);
	glutSolidCube(100);
	glPopMatrix();

	//bagian ti tidur kiri 3
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(0, 495, 122.5);
	glScalef(2, 0.05, 0.05);
	glutSolidCube(100);
	glPopMatrix();


	//bagian ti tidur kanan 1
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(0, 457, -134.5);
	glScalef(2, 0.05, 0.05);
	glutSolidCube(100);
	glPopMatrix();

	//bagian ti tidur kanan 2
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(0, 472, -134.5);
	glScalef(2, 0.05, 0.05);
	glutSolidCube(100);
	glPopMatrix();

	//bagian ti tidur kanan 3
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(0, 495, -134.5);
	glScalef(2, 0.05, 0.05);
	glutSolidCube(100);
	glPopMatrix();


	//tiang ti depan atas 1
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(100, 457, -7);
	glScalef(0.05, 0.05, 2);
	glutSolidCube(130);
	glPopMatrix();

	//tiang ti depan atas 2
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(100, 472, -7);
	glScalef(0.05, 0.05, 2);
	glutSolidCube(130);
	glPopMatrix();

	//tiang ti depan atas 3
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(100, 495, -5);
	glScalef(0.05, 0.05, 2);
	glutSolidCube(130);
	glPopMatrix();

	// tiang ti depan kanan bawah jendela
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(102, 405, -90);
	glScalef(0.05, 0.05, 0.725);
	glutSolidCube(100);
	glPopMatrix();

	// tiang ti depan kiri bawah jendela
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(102, 405, 84);
	glScalef(0.05, 0.05, 0.725);
	glutSolidCube(100);
	glPopMatrix();

	//tiang ti belakang atas 1
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(-100, 457, -7);
	glScalef(0.05, 0.05, 2);
	glutSolidCube(130);
	glPopMatrix();

	//tiang ti belakang atas 2
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(-100, 472, -7);
	glScalef(0.05, 0.05, 2);
	glutSolidCube(130);
	glPopMatrix();

	//tiang ti belakang atas 3
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(-100, 495, -7);
	glScalef(0.05, 0.05, 2);
	glutSolidCube(130);
	glPopMatrix();

	// tiang ti belakang kanan bawah jendela
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(-102, 405, -90);
	glScalef(0.05, 0.05, 0.725);
	glutSolidCube(100);
	glPopMatrix();

	// tiang ti belakang kiri bawah jendela
	glPushMatrix();
	glColor3f(0.952, 0.423, 0.219);
	glTranslatef(-102, 405, 84);
	glScalef(0.05, 0.05, 0.725);
	glutSolidCube(100);
	glPopMatrix();


	///////// tiang ti belakang kiri bawah jendela
   /* glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(0, 406, -197);
	glScalef(2, 0.05, 0.05);
	glutSolidCube(100);
	glPopMatrix();*/



	//(x_geser, y_geser, z_geser);

	// karpet
	glPushMatrix();
	glTranslatef(-3.5, 368.5, 4.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.905, 0.886, 0.854);
	gluCylinder(gluNewQuadric(), 0.0f, 150.0f, 0.0f, 32, 32);
	glEnd();
	glPopMatrix();


	//-=-=-=-=-=-=-=-=-=-=-=-
	 //PILAR Y

	 //pilar kiri depan
	glPushMatrix();
	glTranslatef(100.5, 369.5, 120.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//pilar belakang kiri
	glPushMatrix();
	glTranslatef(-99, 369.5, 120.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//pilar depan kanan
	glPushMatrix();
	glTranslatef(100.5, 369.5, -131.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//pilar belakang kanan
	glPushMatrix();
	glTranslatef(-96, 369.5, -131.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	// kanan depan
	glPushMatrix();
	glTranslatef(36, 369.5, -131.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	// kanan belakang
	glPushMatrix();
	glTranslatef(-36, 369.5, -131.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//kiri depan
	glPushMatrix();
	glTranslatef(36, 369.5, 120.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//kanan belakang
	glPushMatrix();
	glTranslatef(-36, 369.5, 120.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//depan kiri
	glPushMatrix();
	glTranslatef(100.5, 369.5, 48);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//depan kanan
	glPushMatrix();
	glTranslatef(100.5, 369.5, -48);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//belakang kiri
	glPushMatrix();
	glTranslatef(-99, 369.5, 48);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//belakang kanan
	glPushMatrix();
	glTranslatef(-99, 369.5, -48);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();


	//--=--==-=--==-=-==--
	// Jendela

	// JENDELA belakang kanan
	glPushMatrix();
	glTranslatef(-100.5, 291, 279.5);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(450, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(-100.5, 291, 279.5);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.5, 0.5, 0.5);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();

	// JENDELA belakang KIRI
	glPushMatrix();
	glTranslatef(-101.5, 291, 103.5);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(450, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(-101.5, 291, 103.5);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.5, 0.5, 0.5);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();


	// JENDELA depan KIRI
	glPushMatrix();
	glTranslatef(100.5, 288, 279.5);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(450, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(100.5, 288, 279.5);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.5, 0.5, 0.5);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();
	// JENDELA depan KANAN
	glPushMatrix();
	glTranslatef(101.5, 290.5, 105);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(450, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(101.5, 290.5, 105);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.5, 0.5, 0.5);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();
	// JENDELA KIRI KANAN
	glPushMatrix();
	glTranslatef(90, 541.5, -135.5);
	glRotatef(180.0, 0, 0, 1.0);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(450, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(90, 541.5, -135.5);
	glRotatef(180.0, 0, 0, 1.0);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.4, 0.4, 0.4);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();
	// JENDELA KIRI kiri
	glPushMatrix();
	glTranslatef(224, 541.5, -134.5);
	glRotatef(180.0, 0, 0, 1.0);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(450, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(224, 541.5, -134.5);
	glRotatef(180.0, 0, 0, 1.0);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.4, 0.4, 0.4);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();

	// JENDELA KANAN KANAN
	glPushMatrix();
	glTranslatef(-87.5, 321.5, 123);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(450, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(-87.5, 321.5, 123);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.4, 0.4, 0.4);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();
	// JENDELA KANAN kiri
	glPushMatrix();
	glTranslatef(-223, 321.5, 123);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(450, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(-223, 321.5, 123);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.4, 0.4, 0.4);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();


	//-=-=-=-=-=-=-=-==-=-
	// pintu

	//pintu depan
	glPushMatrix();
	glTranslatef(100.5, 169.5, 393);
	glRotatef(90.0, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(350, 200);
	glVertex2f(350, 300);
	glVertex2f(395, 300);
	glVertex2f(395, 200);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(396, 200);
	glVertex2f(396, 300);
	glVertex2f(436, 300);
	glVertex2f(436, 200);
	glEnd();
	glPopMatrix();

	//pintu belakang
	glPushMatrix();
	glTranslatef(-101, 169.5, 393);
	glRotatef(90.0, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(350, 200);
	glVertex2f(350, 280);
	glVertex2f(395, 280);
	glVertex2f(395, 200);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(396, 200);
	glVertex2f(396, 280);
	glVertex2f(436, 280);
	glVertex2f(436, 200);
	glEnd();
	glPopMatrix();

	//pintu kiri
	glPushMatrix();
	glTranslatef(-393, 169.5, 123);
	glRotatef(0.0, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(355, 200);
	glVertex2f(355, 280);
	glVertex2f(395, 280);
	glVertex2f(395, 200);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(395, 200);
	glVertex2f(395, 280);
	glVertex2f(430, 280);
	glVertex2f(430, 200);
	glEnd();
	glPopMatrix();

	//pintu kanan
	glPushMatrix();
	glTranslatef(-393, 169.5, -133);
	glRotatef(0.0, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(355, 200);
	glVertex2f(355, 280);
	glVertex2f(395, 280);
	glVertex2f(395, 200);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(395, 200);
	glVertex2f(395, 280);
	glVertex2f(430, 280);
	glVertex2f(430, 200);
	glEnd();
	glPopMatrix();





	//ORNAMEN PINTU
	//PEMBATAS DEPAN
	glPushMatrix();
	glTranslatef(102, 369.5, -2.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//PEMBATAS BELAKANG
	glPushMatrix();
	glTranslatef(-101, 369.5, -2.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//PEMBATAS KIRI
	glPushMatrix();
	glTranslatef(0, 369.5, 123);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//PEMBATAS KANAN
	glPushMatrix();
	glTranslatef(0, 369.5, -133);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.921, 0.345, 0);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 100.0f, 32, 32);
	glEnd();
	glPopMatrix();


	//DETAIL
		//atap lantai 3
	glPushMatrix();
	glColor3f(1, 0.882, 0.658);
	glTranslatef(0, 534.5, 0);
	glScalef(1.8, 0.05, 1.8);
	glutSolidCube(200);
	glPopMatrix();


}

// lantai 4
void lantai4() {
	//dinding bagian kiri
	glPushMatrix();
	glTranslatef(0, 469.5, 22.5);
	glRotatef(0, 0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.815, 0.458);
	glVertex3f(-100.0, -100.0, 100);
	glVertex3f(-100.0, 60.0, 100);
	glVertex3f(100.0, 60.0, 100);
	glVertex3f(100.0, -100.0, 100);
	glEnd();
	glPopMatrix();
	//dinding bagian belakang
	glPushMatrix();
	glTranslatef(0, 469.5, 22.5);
	glRotatef(-90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.815, 0.458);
	glVertex3f(-155.0, -100.0, 100);
	glVertex3f(-155.0, 60.0, 100);
	glVertex3f(100.0, 60.0, 100);
	glVertex3f(100.0, -100.0, 100);
	glEnd();
	glPopMatrix();
	//dinding bagian depan
	glPushMatrix();
	glTranslatef(0, 469.5, 22.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.815, 0.458);
	glVertex3f(-100.0, -100.0, 100);
	glVertex3f(-100.0, 60.0, 100);
	glVertex3f(155.0, 60.0, 100);
	glVertex3f(155.0, -100.0, 100);
	glEnd();
	glPopMatrix();
	//dinding bagian kanan
	glPushMatrix();
	glTranslatef(0, 469.5, -232.5);
	glRotatef(0, 0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.815, 0.458);
	glVertex3f(-100.0, -100.0, 100);
	glVertex3f(-100.0, 60.0, 100);
	glVertex3f(100.0, 60.0, 100);
	glVertex3f(100.0, -100.0, 100);
	glEnd();
	glPopMatrix();


	//pilar kiri depan
	glPushMatrix();
	glTranslatef(100.5, 369.5, 120.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//pilar belakakang kiri
	glPushMatrix();
	glTranslatef(-99, 369.5, 120.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//pilar depan kanan
	glPushMatrix();
	glTranslatef(100.5, 369.5, -131.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//pilar belakang kanan
	glPushMatrix();
	glTranslatef(-96, 369.5, -131.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	// kanan depan
	glPushMatrix();
	glTranslatef(36, 369.5, -131.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	// kanan belakang
	glPushMatrix();
	glTranslatef(-36, 369.5, -131.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//kiri depan
	glPushMatrix();
	glTranslatef(36, 369.5, 120.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//kanan belakang
	glPushMatrix();
	glTranslatef(-36, 369.5, 120.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//depan kiri
	glPushMatrix();
	glTranslatef(100.5, 369.5, 48);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//depan kanan
	glPushMatrix();
	glTranslatef(100.5, 369.5, -48);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//belakakang kiri
	glPushMatrix();
	glTranslatef(-99, 369.5, 48);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();
	//belakakang kanan
	glPushMatrix();
	glTranslatef(-99, 369.5, -48);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//pintu depan
	glPushMatrix();
	glTranslatef(100.5, 169.5, 393);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(350, 200);
	glVertex2f(350, 280);
	glVertex2f(395, 280);
	glVertex2f(395, 200);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(396, 200);
	glVertex2f(396, 280);
	glVertex2f(436, 280);
	glVertex2f(436, 200);
	glEnd();
	glPopMatrix();
	//pintu belakang
	glPushMatrix();
	glTranslatef(-101, 169.5, 393);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(350, 200);
	glVertex2f(350, 280);
	glVertex2f(395, 280);
	glVertex2f(395, 200);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(396, 200);
	glVertex2f(396, 280);
	glVertex2f(436, 280);
	glVertex2f(436, 200);
	glEnd();
	glPopMatrix();
	//pintu kiri
	glPushMatrix();
	glTranslatef(-393, 169.5, 123);
	glRotatef(0.0, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(355, 200);
	glVertex2f(355, 280);
	glVertex2f(395, 280);
	glVertex2f(395, 200);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(395, 200);
	glVertex2f(395, 280);
	glVertex2f(430, 280);
	glVertex2f(430, 200);
	glEnd();
	glPopMatrix();
	//pintu kanan
	glPushMatrix();
	glTranslatef(-393, 169.5, -133);
	glRotatef(0.0, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(355, 200);
	glVertex2f(355, 280);
	glVertex2f(395, 280);
	glVertex2f(395, 200);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.541, 0.203, 0);
	glVertex2f(395, 200);
	glVertex2f(395, 280);
	glVertex2f(430, 280);
	glVertex2f(430, 200);
	glEnd();
	glPopMatrix();

	// JENDELA belakang kanan
	glPushMatrix();
	glTranslatef(-100.5, 291, 279.5);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(452, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(-100.5, 291, 279.5);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.5, 0.5, 0.5);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();

	// JENDELA belakang KIRI
	glPushMatrix();
	glTranslatef(-101.5, 291, 103.5);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(452, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(-101.5, 291, 103.5);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.5, 0.5, 0.5);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();

	// JENDELA depan KIRI
	glPushMatrix();
	glTranslatef(100.5, 288, 279.5);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(452, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(100.5, 288, 279.5);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.5, 0.5, 0.5);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();

	// JENDELA depan KANAN
	glPushMatrix();
	glTranslatef(101.5, 290.5, 105);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(452, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(101.5, 290.5, 105);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.5, 0.5, 0.5);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();

	// JENDELA KIRI KANAN
	glPushMatrix();
	glTranslatef(90, 541.5, -135.5);
	glRotatef(180.0, 0, 0, 1.0);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(452, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(90, 541.5, -135.5);
	glRotatef(180.0, 0, 0, 1.0);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.4, 0.4, 0.4);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();
	// JENDELA KIRI kiri
	glPushMatrix();
	glTranslatef(224, 541.5, -134.5);
	glRotatef(180.0, 0, 0, 1.0);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(452, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(224, 541.5, -134.5);
	glRotatef(180.0, 0, 0, 1.0);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.4, 0.4, 0.4);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();

	// JENDELA KANAN KANAN
	glPushMatrix();
	glTranslatef(-87.5, 321.5, 123);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(452, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(-87.5, 321.5, 123);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.4, 0.4, 0.4);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();
	// JENDELA KANAN kiri
	glPushMatrix();
	glTranslatef(-223, 321.5, 123);
	glColor3f(0.5, 0.0, 0.0);
	glScalef(0.4, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2i(330, 320);
	glVertex2i(450, 320);
	glVertex2i(452, 230);
	glVertex2i(330, 230);
	glEnd();
	glPopMatrix();
	//garis jendela
	glPushMatrix();
	glTranslatef(-223, 321.5, 123);
	glColor3f(0.1, 0.7, 0.5);
	glScalef(0.4, 0.4, 0.4);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(390, 320);
	glVertex2i(390, 230);
	glVertex2i(330, 273);
	glVertex2i(450, 273);
	glEnd();
	glPopMatrix();

	//BAWAH JENDELA
//depan
	glPushMatrix();
	glTranslatef(106.5, 408.5, 42.5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 90.0f, 4, 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(106.5, 408.5, -143);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 100.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//belakang
	glPushMatrix();
	glTranslatef(-102.5, 408.5, 42.5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 90.0f, 4, 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-102.5, 408.5, -143);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 100.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//kanan
	glPushMatrix();
	glTranslatef(29.5, 473.5 - 65, -139);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 80.0f, 4, 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-106.5, 473.5 - 65, -139);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 75.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//kiri
	glPushMatrix();
	glTranslatef(29.5, 473.5 - 65, 128.5);
	glRotatef(90, 0.0, 1.0, 0.0);

	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 80.0f, 4, 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-106.5, 473.5 - 65, 128.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 75.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//CAGAK

//depan
	glPushMatrix();
	glTranslatef(222, 369.5, -92.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(222, 369.5, 92.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//belakang
	glPushMatrix();
	glTranslatef(-223, 369.5, -92.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-223, 369.5, 92.5);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//kiri
	glPushMatrix();
	glTranslatef(0, 369.5, 220);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//kanan
	glPushMatrix();
	glTranslatef(0, 369.5, -224);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 160.0f, 32, 32);
	glEnd();
	glPopMatrix();

	//PEMBATAS

//belakang
//1
	glPushMatrix();
	glTranslatef(-105, 473.5, -138.5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 265.0f, 4, 4);
	glEnd();
	glPopMatrix();
	//2
	glPushMatrix();
	glTranslatef(-105, 484, -138.5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 265.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//depan
	glPushMatrix();
	glTranslatef(106.5, 473.5, -138.5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 265.0f, 4, 4);
	glEnd();
	glPopMatrix();
	//2
	glPushMatrix();
	glTranslatef(106.5, 484, -138.5);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 265.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//kiri
	glPushMatrix();
	glTranslatef(-109.5, 473.5, -134.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 220.0f, 4, 4);
	glEnd();
	glPopMatrix();
	//2
	glPushMatrix();
	glTranslatef(-109.5, 484, -134.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 220.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//kanan
	glPushMatrix();
	glTranslatef(-109.5, 473.5, 123.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 220.0f, 4, 4);
	glEnd();
	glPopMatrix();
	//2
	glPushMatrix();
	glTranslatef(-109.5, 484, 123.5);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glColor3f(0.952, 0.423, 0.219);
	gluCylinder(gluNewQuadric(), 6.0f, 6.0f, 220.0f, 4, 4);
	glEnd();
	glPopMatrix();

	//interior

	//meja
	glColor3f(0.871, 0.722, 0.529);
	glPushMatrix();
	glRotatef(90, 0.0, 1.0, 0.0);
	glTranslatef(29 + -31.5, 370.5 + 7.5, -45 + -14);
	glScalef(1.0, 0.05, 0.8);
	glutSolidCube(100);
	glPopMatrix();
	//kaki meja
	glColor3f(0.627, 0.322, 0.176);
	glPushMatrix();
	glTranslatef(29 + -53.5, 370.5 + 0, -45 + 3);
	glScalef(1.0, 1.0, 1.0);
	glutSolidCube(10);
	glPopMatrix();
	//kaki meja
	glColor3f(0.627, 0.322, 0.176);
	glPushMatrix();
	glTranslatef(29 + 0.5 + -53.5, 370.5 + 0, -45 + 92.5);
	glScalef(1.0, 1.0, 1.0);
	glutSolidCube(10);
	glPopMatrix();
	//teko
	glColor3f(0.13, 0.1, 0.1);
	glPushMatrix();
	glTranslatef(29 + -31.5 + -50, 370.5 + 7.5 + 5.5, -45 + -14 + 71);
	glutSolidTeapot(5);
	glPopMatrix();

	//bola hitam

//atas(dari kiri)
//1
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, -132.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//2
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, -49);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//3
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, 48);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//4
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, 120.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//bawah(dari kiri)
	//1
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5 - 64.5, 109.5 - 2.5, -132.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//2
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5 - 64.5, 109.5 - 2.5, -49);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//3
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5 - 64.5, 109.5 - 2.5, 48);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//4
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5 - 64.5, 109.5 - 2.5, 120.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//atas(dari kiri)
	//1
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, -132.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//2
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, -49);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//3
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, 48);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//4
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, 120.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();



	//Depan

	glPushMatrix();
	glTranslatef(220.5, 0, 0);
	//atas(dari kiri)
	//1
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, -132.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//2
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, -49);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//3
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, 48);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//4
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5, 109.5, 120.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//bawah(dari kiri)
	//1
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5 - 64.5, 109.5, -132.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//2
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5 - 64.5, 109.5, -49);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//3
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5 - 64.5, 109.5, 48);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//4
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(473.5 - 64.5, 109.5, 120.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPopMatrix();


	//kanan

	//1
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-99.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-35.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(36.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(105.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//2
	glPushMatrix();
	glTranslatef(0, -65, 5);
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-99.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-35.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(36.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(105.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPopMatrix();

	//kiri

	glPushMatrix();
	glTranslatef(0, 0, -267);

	//1
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-99.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-35.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(36.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(105.5, 128, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	//2
	glPushMatrix();
	glTranslatef(0, -65, 5);
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-99.5, 128 - 9.5, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-35.5, 128 - 9.5, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(36.5, 128 - 9.5, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(105.5, 128 - 9.5, -473.5);
	glutSolidSphere(3.0, 2, 30);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


}





void gelas_object() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(5, 162, 273);
	gluCylinder(gluNewQuadric(), 6.0, 8.0, 15.0, 60.0, 100);
	glPopMatrix();
}

void gelas() {
	gelas_object();

	glPushMatrix();
	glTranslatef(5, 0, -163);
	gelas_object();
	glTranslatef(100, 0, 103);
	gelas_object();

	glPopMatrix();
}

void atap_atas() {
	glPushMatrix();
	glColor3f(0.29f, 0.70f, 0.76f);
	glTranslatef(0, 534.5, 0);
	glScalef(1.8, 0.05, 1.8);
	glutSolidCube(200);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 545, -8);
	glRotatef(-45, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.29f, 0.70f, 0.76f);
	glVertex3f(-230.0, -200.0, 135);
	glVertex3f(-40.0, 30.0, 100);
	glVertex3f(40.0, 30.0, 100);
	glVertex3f(230.0, -200.0, 135);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 710, -113.5);
	glRotatef(62, 1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.29f, 0.70f, 0.76f);
	glVertex3f(-230.0, -200.0, 135);
	glVertex3f(-40.0, 30.0, 100);
	glVertex3f(40.0, 30.0, 100);
	glVertex3f(225.0, -200.0, 135);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8, 545, 0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.29f, 0.70f, 0.76f);
	glVertex3f(-230.0, -200.0, 135);
	glVertex3f(-40.0, 30.0, 100);
	glVertex3f(40.0, 30.0, 100);
	glVertex3f(230.0, -200.0, 135);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-113.5, 710, 0);
	glRotatef(-62, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.29f, 0.70f, 0.76f);
	glVertex3f(-230.0, -200.0, 135);
	glVertex3f(-40.0, 30.0, 100);
	glVertex3f(40.0, 30.0, 100);
	glVertex3f(230.0, -200.0, 135);
	glEnd();
	glPopMatrix();

	//sini
	glPushMatrix();
	glTranslatef(0, 910, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.988, 0.866, 0.329);
	gluCylinder(gluNewQuadric(), 1.0f, 3.0f, 300, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 610, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(0.713, 0.6, 0.105);
	glutSolidCube(80);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 910, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.15, 0, 0.84);
	gluCylinder(gluNewQuadric(), 0.0f, 10.0f, 50, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 850, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.15, 0, 0.84);
	gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 10, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 830, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.15, 0, 0.84);
	gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 10, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 810, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.15, 0, 0.84);
	gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 10, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 790, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.15, 0, 0.84);
	gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 10, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 770, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.15, 0, 0.84);
	gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 10, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 750, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.15, 0, 0.84);
	gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 10, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 730, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.15, 0, 0.84);
	gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 10, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 710, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.15, 0, 0.84);
	gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 10, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 690, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.15, 0, 0.84);
	gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 10, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 670, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.15, 0, 0.84);
	gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 10, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 650, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.15, 0, 0.84);
	gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 10, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 630, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.15, 0, 0.84);
	gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 10, 32, 32);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 610, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.15, 0, 0.84);
	gluCylinder(gluNewQuadric(), 10.0f, 10.0f, 10, 32, 32);
	glEnd();
	glPopMatrix();



}


void draw() {
	// Mulai tuliskan isi pikiranmu disini

	//lantai dasar
	glPushMatrix();
	glScalef(1.5, 1.5, 1.5);
	dasar();
	glPopMatrix();

	pagar_lantai1();

	//pagar lantai 2
	glPushMatrix();
	glScalef(1.2, 1, 1.2);
	pagar_lantai2();
	glPopMatrix();

	//pagar lantai 3
	glPushMatrix();
	glScalef(0.8, 0.8, 0.8);
	glTranslatef(0, 665.5 - 61, 0);
	pagar_lantai2();
	glPopMatrix();

	//pagar lantai 4
	glPushMatrix();
	glScalef(0.7, 0.7, 0.7);
	glTranslatef(0, 482, 0);
	pagar_lantai2();
	glPopMatrix();

	//lantai1
	lantai1_fix();

	//lantai2
	glPushMatrix();
	glScalef(1.2, 1.2, 1.2);
	glTranslatef(0, -9, 2);
	lantai2();
	atap_lt2();
	glPopMatrix();

	//lantai3
	glPushMatrix();
	glScalef(1.1, 1.1, 1.1);
	glTranslatef(-1, 210.5, 1.5);
	lantai3();
	atap_lt2();
	glPopMatrix();

	//lantai4
	glPushMatrix();
	glScalef(0.8, 0.8, 0.8);
	glTranslatef(0, 665.5, 0);
	lantai4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(29 + -31.5 + -50 + -11, 370.5 + 7.5 + 5.5 + 344, -45 + -14 + 71 + 87);
	glScalef(0.4, 0.4, 0.4);
	gelas();
	glPopMatrix();



	glPushMatrix();
	glScalef(1.1, 1.1, 1.1);
	glTranslatef(0, 340, 0);
	atap_atas();
	glPopMatrix();




	ground();
	glFlush();
	cout << "X_GESER = " << x_geser << "	Y_GESER = " << y_geser << "	Z_GESER = " << z_geser << endl;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	camera();
	draw();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, 16.0 / 9.0, 2, 10000);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
	glutPostRedisplay();
	glutWarpPointer(width / 2, height / 2);
	glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y) {
	int dev_x, dev_y;
	dev_x = (width / 2) - x;
	dev_y = (height / 2) - y;
	yaw += (float)dev_x / 20.0;
	pitch += (float)dev_y / 20.0;
}

void camera() {
	if (motion.Forward) {
		camX += cos((yaw + 90) * TO_RADIANS) * 2;
		camZ -= sin((yaw + 90) * TO_RADIANS) * 2;
	}
	if (motion.Backward) {
		camX += cos((yaw + 90 + 180) * TO_RADIANS) * 2;
		camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 2;
	}
	if (motion.Left) {
		camX += cos((yaw + 90 + 90) * TO_RADIANS) * 2;
		camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 2;
	}
	if (motion.Right) {
		camX += cos((yaw + 90 - 90) * TO_RADIANS) * 2;
		camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 2;
	}
	if (motion.Naik) {
		terbang -= 2.0;
	}
	if (motion.Turun) {
		terbang += 2.0;
	}

	if (pitch >= 70)
		pitch = 70;
	if (pitch <= -90)
		pitch = -90;


	glRotatef(-pitch, 1.0, 0.0, 0.0);
	glRotatef(-yaw, 0.0, 1.0, 0.0);

	glTranslatef(-camX, -terbang, -350 - camZ);
	if (terbang < 25)
		terbang = 24;
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'W':
	case 'w':
		motion.Forward = true;
		break;
	case 'A':
	case 'a':
		motion.Left = true;
		break;
	case 'S':
	case 's':
		motion.Backward = true;
		break;
	case 'D':
	case 'd':
		motion.Right = true;
		break;
	case 'E':
	case 'e':
		motion.Naik = true;
		break;
	case 'Q':
	case 'q':
		motion.Turun = true;
		break;
	case '6':
		x_geser += 0.5;
		break;
	case '4':
		x_geser -= 0.5;
		break;
	case '8':
		y_geser += 0.5;
		break;
	case '2':
		y_geser -= 0.5;
		break;
	case '9':
		z_geser -= 0.5;
		break;
	case '1':
		z_geser += 0.5;
		break;
	case '`': // KELUAR DARI PROGRAM
		exit(1);
	}
}

void keyboard_up(unsigned char key, int x, int y) {
	switch (key) {
	case 'W':
	case 'w':
		motion.Forward = false;
		break;
	case 'A':
	case 'a':
		motion.Left = false;
		break;
	case 'S':
	case 's':
		motion.Backward = false;
		break;
	case 'D':
	case 'd':
		motion.Right = false;
		break;
	case 'E':
	case 'e':
		motion.Naik = false;
		break;
	case 'Q':
	case 'q':
		motion.Turun = false;
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("TR GRAFKOM KELOMPOK 3");

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(passive_motion);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);

	glutMainLoop();
	return 0;
}