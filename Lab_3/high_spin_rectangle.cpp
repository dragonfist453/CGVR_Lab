#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500
int wid1,wid2,t;
static GLfloat spin=0.0;
int spinval = 1;
float i = 0.01, delta = 0.0005;
void display() {
  glutSetWindow(t);
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glLoadIdentity();
  glRotatef(spin,0,0,1);
  glBegin(GL_POLYGON);
  glColor3f(1,0,0);
  glVertex3f(i-0.5,i-0.25,i+0.25);
  glColor3f(0,1,0);  
  glVertex3f(i+0.25,i-0.25,i+0.25);
  glColor3f(0,0,1);
  glVertex3f(i+0.25,i+0.25,i+0.25);
  glColor3f(0,0,1);
  glVertex3f(i-0.5,i+0.25,i+0.25);
  glEnd();
  i+=delta;
  if(i>1 || i<-1){
	  delta=-delta;
	  spinval=-spinval;
  }
  glPopMatrix();
  if(t==wid1) {
    glFlush();
    t=wid2;
  }
  else {
    glutSwapBuffers();
    t=wid1;
  }
}

void myInit() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(-1,1,-1,1,-1,1);
  glClearColor(1,1,1,1);
  glColor3f(1,0,0);
}

void spinRect() {
  spin+=spinval;
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
  switch(button) {
    case GLUT_LEFT_BUTTON: if(state == GLUT_DOWN)
                              glutIdleFunc(spinRect);
                            break;
    case GLUT_RIGHT_BUTTON: if(state == GLUT_DOWN)
                              glutIdleFunc(NULL);
                            break;
    default: break;
  }
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
  wid1 = glutCreateWindow("Single Buffer");
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutDisplayFunc(display);
  myInit();

  glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
  wid2 = glutCreateWindow("Double Buffer");
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  myInit();

  t=wid1;

  glutMainLoop();
  return 0;
}
