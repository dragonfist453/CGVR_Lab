#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500
int wid1,wid2;

void plot_circle_points(int xc,int yc,int x,int y) {
  glColor3f(1,0,1);
  glPointSize(3);
  glBegin(GL_POINTS);
  glVertex2i(xc+x,yc+y);
  glVertex2i(xc-x,yc+y);
  glVertex2i(xc+x,yc-y);
  glVertex2i(xc-x,yc-y);
  glVertex2i(xc+y,yc+x);
  glVertex2i(xc+y,yc-x);
  glVertex2i(xc-y,yc+x);
  glVertex2i(xc-y,yc-x);
  glEnd();
}

void draw_circle(int xc,int yc,int r) {
  int x=0,y=r;
  int d=3-2*r;
  while(x<y) {
    plot_circle_points(xc,yc,x,y);
    x++;
    if(d<0) {
      d+=4*x+6;
    }
    else {
      y--;
      d+=4*(x-y)+10;
    }
    plot_circle_points(xc,yc,x,y);
  }
  glFlush();
}

void display_cylinder() {
  glutSetWindow(wid1);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1,0,1);
  int xc=250,yc=150,r=50;
  for(int i=100;i<150;i+=5) {
    draw_circle(xc,yc+i,r);
  }
  glFlush();
}

void draw_quad(int x,int y,int w,int h) {
  glColor3f(1,0,0);
  glBegin(GL_LINE_LOOP);
  glVertex2i(x,y);
  glVertex2i(x+w,y);
  glVertex2i(x+w,y+h);
  glVertex2i(x,y+h);
  glEnd();
}

void display_parallelopiped() {
  glutSetWindow(wid2);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1,0,0);
  int x=150,y=150,w=150,h=100;
  for(int i=100;i<150;i+=5) {
    draw_quad(x+i,y+i,w,h);
  }
  glFlush(); 
}

void myInit() {
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,WINDOW_WIDTH,0,WINDOW_HEIGHT);
  glClearColor(1,1,1,1);
  glColor3f(1,0,0);
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
  wid1 = glutCreateWindow("Cylinder");
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutDisplayFunc(display_cylinder);
  myInit();

  glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
  wid2 = glutCreateWindow("Parallelopiped");
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutDisplayFunc(display_parallelopiped);
  myInit();

  glutMainLoop();
  return 0;
}