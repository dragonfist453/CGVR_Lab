#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

// sphere radius
#define SPR 75
// degrees to pi conversion factor
#define DPI (3.1415/180.f)
// coordinates function macro
#define SPHERE_GA(theta,phi) {SPR*sin(DPI*(theta))*cos(DPI*(phi)),SPR*cos(DPI*(theta))*cos(DPI*(phi)),SPR*sin(DPI*(phi))}

void displayLoop() {
	//glClearColor(0, 0, 0, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(int i=-80;i<80;i+=10){
		glBegin(GL_QUAD_STRIP);
		for(int thet=-180;thet<=180;thet+=10){
			// glColor3f(c0,c0,c0);c0+=.00125;
      glColor3f(1,1,1);
			float p1[3] = SPHERE_GA(thet,i);
			glVertex3fv(p1);
      glColor3f(.8f,.8f,.8f);
			float p2[3] = SPHERE_GA(thet,i+10);
			glVertex3fv(p2);
		}
		glEnd();
	}

	//north cap
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1,0,0);
	glVertex3f(0,0,SPR);

	for(int thet=-180;thet<=180;thet+=10){
		// glColor3f((thet+180)/360,.25,.25);
		float p1[3] = SPHERE_GA(thet,80);
		glVertex3fv(p1);
	}
	glEnd();

	//south cap
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0,1,0);
	glVertex3f(0,0,-SPR);
	
	for(int thet=-180;thet<=180;thet+=10){
		// glColor3f((thet+180)/360,.25,.25);
		float p1[3] = SPHERE_GA(thet,-80);
		glVertex3fv(p1);
	}

	glEnd();
	
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	//single buffer+rgb+depth
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	int w = 800,h=600;
	glutInitWindowSize(w, h);
	glutCreateWindow("Sphere Approximation");

	glutDisplayFunc(displayLoop);
	// 3d depth test
	glEnable(GL_DEPTH_TEST);

	glClearColor(0, 0, 0, 1.f);
	// set up how the camera will look like
	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
	// glFrustum(-w/2,w/2,-h/2,h/2,.1,2000);
  gluPerspective(120,((float)w)/h,.1,1000);
	glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();glTranslatef(0,0,-100);
  // glRotatef(-20,1,0,0);
  glRotatef(-20,0,1,0);
	glutMainLoop();
}
