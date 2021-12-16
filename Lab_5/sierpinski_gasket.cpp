#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500
typedef float point3[3];
point3 tetra[4] = {
  {0,250,-250},
  {0,0,250},
  {250,-250,250},
  {-250,-250,-250}
};
int iter;

void drawTriangle(point3 p1, point3 p2, point3 p3)  {
  glVertex3fv(p1);
  glVertex3fv(p2);
  glVertex3fv(p3);
}

void drawTetra(point3 p1, point3 p2, point3 p3, point3 p4) {
  glColor3f(0,0,0);
  drawTriangle(p1,p2,p3);
  glColor3f(1,0,0);
  drawTriangle(p1,p3,p4);
  glColor3f(0,1,0);
  drawTriangle(p1,p4,p2);
  glColor3f(0,0,1);
  drawTriangle(p2,p3,p4);
}

void divideTetra(point3 p1, point3 p2, point3 p3, point3 p4, int iter) {
  point3 mid[6];
  int j;
  if(iter > 0) {
    for(j=0;j<3;j++) mid[0][j] = (p1[j] + p2[j])/2;
    for(j=0;j<3;j++) mid[1][j] = (p1[j] + p3[j])/2;
    for(j=0;j<3;j++) mid[2][j] = (p1[j] + p4[j])/2;
    for(j=0;j<3;j++) mid[3][j] = (p2[j] + p3[j])/2;
    for(j=0;j<3;j++) mid[4][j] = (p3[j] + p4[j])/2;
    for(j=0;j<3;j++) mid[5][j] = (p2[j] + p4[j])/2;

    divideTetra(p1, mid[0], mid[1], mid[2], iter-1);
    divideTetra(mid[0], p2, mid[3], mid[5], iter-1);
    divideTetra(mid[1], mid[3], p3, mid[4], iter-1);
    divideTetra(mid[2], mid[5], mid[4], p4, iter-1);
  }
  else {
    drawTetra(p1, p2, p3, p4);
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  divideTetra(tetra[0],tetra[1],tetra[2],tetra[3],iter);
  glEnd();
  glFlush();
}

void myInit() {
  glOrtho(-250,250,-250,250,-250,250);
  glClearColor(1,1,1,1);
  glColor3f(1,0,0);
}

int main(int argc, char* argv[]) {
  cout<<"Enter the number of subdivisions: ";
  cin>>iter;
  glutInit(&argc, argv);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
  glutCreateWindow("Sierpinski Gasket");
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutDisplayFunc(display);
  myInit();

  glutMainLoop();
  return 0;
}