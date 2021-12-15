#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500
int x1,yc1,x2,y2;

void drawPixel(int x, int y) {
  glColor3f(0,0,1);
  glPointSize(5);
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}

void drawLine() {
  int dx=x2-x1,dy=y2-yc1,incx=1,incy=1,inc1,inc2;
  int x=x1,y=yc1,p;

  // Vertical line
  if(dx == 0) {
    for(int i=0;i<=dy;i++)
      drawPixel(x1,yc1+i);
    return;
  }

  // Horizontal line
  if(dy == 0) {
    for(int i=0;i<=dx;i++)
      drawPixel(x1+i,yc1);
    return;
  }

  // To get everything in first quadrant
  if(dx < 0) {
    dx = fabs(dx);
    incx = -1;
  }

  if(dy < 0) {
    dy = fabs(dy);
    incy = -1;
  }

  // Any line with slope < 1
  if(dx>dy) {
    drawPixel(x,y);
    p = 2*dy-dx;
    inc1 = 2*(dy-dx);
    inc2 = 2*dy;
    for(int i=0;i<dx;i++) {
      if(p>0) {
        y+=incy;
        p+=inc1;
      }
      else {
        p+=inc2;
      }
      x+=incx;
      drawPixel(x,y);
    }
  }
  else {
    drawPixel(x,y);
    p = 2*dx-dy;
    inc1 = 2*(dx-dy);
    inc2 = 2*dx;
    for(int i=0;i<dy;i++) {
      if(p>0) {
        x+=incx;
        p+=inc1;
      }
      else {
        p+=inc2;
      }
      y+=incy;
      drawPixel(x,y);
    }
  }
  glFlush();
}

void display() {}

void myInit() {
  glClearColor(1,1,1,1);
  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(-250,250,-250,250);
}

void mouse(int button, int state, int x, int y) {
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    x1 = x - WINDOW_WIDTH/2;
    yc1 = WINDOW_HEIGHT/2 - y;
  }
  if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    x2 = x - WINDOW_WIDTH/2;
    y2 = WINDOW_HEIGHT/2 - y;
    cout<<"Drawn line from ("<<x1<<","<<yc1<<") to ("<<x2<<","<<y2<<")\n";
    drawLine();
  }
}

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Bresenham Line Drawing");
  myInit();
  glutMouseFunc(mouse);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}