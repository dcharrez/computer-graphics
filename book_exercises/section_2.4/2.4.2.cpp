#include <stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glut.h>
using namespace std;

int w_width = 640;
int w_height = 480;
const double PI=3.14159265358979323846;
double radius;
int n_sides;

void draw_polygon(double radius, int n_sides) {
	if(n_sides<3) return;
	glBegin(GL_LINE_STRIP);
	for(int i=0;i<=n_sides;i++){
		double angle=i*2*PI/n_sides;
		glVertex2d(w_width/2+radius*cos(angle),w_height/2+radius*sin(angle));	
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

void myDisplay(void) {
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 0.0, 0.0);
	glPointSize(1.0);
	draw_polygon(radius, n_sides);
	glFlush ();
}

int main(int argc, char** argv) {
	cout << "Enter radius : "; cin >> radius;
	cout << "Enter the number of edges : "; cin >> n_sides;
	
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (w_width, w_height);
	glutInitWindowPosition (100, 150);
	glutCreateWindow ("Polygon with radius and # edges");
	glutDisplayFunc(myDisplay);
	myInit ();
	glutMainLoop();

	return 0;
}