#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

int w_width = 640;
int w_height = 480;
float x_1, y_1, x_2, y_2;

void drawLineMiddlePoint(float x1,float y1,float x2,float y2) {
    float dx, dy, incE, incNE, d, x,y;
    dx = x2 - x1; dy = y2 - y1;
    d = 2* dy-dx;
    incE = 2*dy;
    incNE = 2*(dy-dx);
    x = x1; y = x1;
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    while( x < x2){
      if(d <= 0) {
        d = d + incE;
        x = x+0.01;
      } else {
        d = d + incNE;
        x = x + 0.01; y = y + 0.01;
      }
      glVertex2f(x,y);
    }
    glEnd();
}

void myInit (void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void myDisplay() {
    glClear( GL_COLOR_BUFFER_BIT );
    glColor3f (0.0, 0.0, 0.0);
    glPointSize(1.0);
    drawLineMiddlePoint(x_1,y_1,x_2,y_2);
    glFlush ();
}

int main( int argc, char **argv )
{
    cout << "Enter x1 : "; cin >> x_1;
    cout << "Enter y1 : "; cin >> y_1;
    cout << "Enter x2 : "; cin >> x_2;
    cout << "Enter y2 : "; cin >> y_2;

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (w_width, w_height);
    glutInitWindowPosition(100, 150);
    glutCreateWindow( "Line using mid point algorithm" );
    glutDisplayFunc( myDisplay );
    myInit ();
    glutMainLoop();

    return 0;
}