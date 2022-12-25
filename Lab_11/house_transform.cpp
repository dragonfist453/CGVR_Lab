#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

float house[11][2] = { { 100,200 },{ 200,250 },{ 300,200 },{ 100,200 },{ 100,100 },{ 175,100 },{ 175,150 },{ 225,150 },{ 225,100 },{ 300,100 },{ 300,200 } };
float angle;
float m, c, theta;

void display() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
	//NORMAL HOUSE
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 11; i++)
		glVertex2fv(house[i]);
	glEnd();
	glFlush();
	//ROTATED HOUSE
	glPushMatrix();
	glTranslatef(100, 100, 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(-100, -100, 0);
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 11; i++)
		glVertex2fv(house[i]);
	glEnd();
	glFlush();
	glPopMatrix();
}

void display2() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW); 
	
	//normal house
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 11; i++)
		glVertex2fv(house[i]);
	glEnd();
	glFlush();
	// line
	float x1 = 0, x2 = 500;
	float y1 = m * x1 + c;
	float y2 = m * x2 + c;
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();

	//Reflected
	glPushMatrix();
	glTranslatef(0, c, 0);
	theta = atan(m);
	theta = theta * 180 / 3.14;
	glRotatef(theta, 0, 0, 1);
	glScalef(1, -1, 1);
	glRotatef(-theta, 0, 0, 1);
	glTranslatef(0, -c, 0);
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 11; i++)
		glVertex2fv(house[i]);
	glEnd();
	glFlush();
	glPopMatrix();
}

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-450, 450, -450, 450);
}

void mouse(int btn, int state, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		display();
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		display2();
	}
}

void simpdisplay(){}

int main(int argc, char** argv) {
	cout<<"Enter the rotation angle\n";
	cin>>angle;
	cout<<"Enter c and m value for line y=mx+c\n";
	cin>>c>>m;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("House Rotation");
	glutMouseFunc(mouse);
	glutDisplayFunc(simpdisplay);
	myInit();
	glutMainLoop();
    	return 0;
}
