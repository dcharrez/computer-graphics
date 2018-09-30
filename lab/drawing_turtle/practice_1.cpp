#include <GL/glut.h>
#include <cstdio>
#include <vector>
#include <cmath>
#include <string.h>
#include <iostream>

using namespace std;

void display(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void turtle(int sides,float radio,int x,int y);
void draw();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("csunsa");
	glutDisplayFunc(display);

	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}

void keyboard(unsigned char key, int x, int y) {

   switch(key) {
    
    case 'w' :
        cout<<"up"<<endl;
        glTranslatef(0.0, 0.1 ,0.0);
        break;
    case 'a' : 
        cout<<"left"<<endl;
        glTranslatef(-0.1, 0.0 ,0.0);
        break;
    case 's' :
        cout<<"down"<<endl;
        glTranslatef(0.0, -0.1, 0);
        break;
    case 'd' :
        cout<<"right"<<endl;
        glTranslatef(0.1, 0 ,0.0);
        break;
    case 'i' :
        cout<<"up"<<endl;
        glRotatef(5.0, 1.0, 0.0, 0.0);
        break;
    case 'j' : 
        cout<<"left"<<endl;
        glRotatef(-5.0, 0.0, 1.0, 0.0);
        break;
    case 'k' :
        cout<<"down"<<endl;
        glRotatef(-5.0, 1.0, 0.0, 0.0);
        break;
    case 'l' :
        cout<<"right"<<endl;
        glRotatef(5.0, 0.0, 1.0, 0.0);
        break;     
    case '+' :
        glScalef(2,2,2);
        break;

    case '-' :
        glScalef(0.5,0.5,0.5);
        break;    
    }
    glutPostRedisplay();
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void display(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	draw();
	// glutWireTorus(0.25,0.75, 28, 28);
	glColor3f(0.0,0.0,1.0) ;
	glutWireCube(.60) ;
	glutSwapBuffers();
}

void turtle(int sides,float radio,int x,int y) {

	std::vector<float> point_x;
    std::vector<float> point_y;
    float PI = 3.14159f;
    float step = (2 * PI )/sides;
    
    for (int i =0; i < sides; i++) {
		point_x.push_back(x+radio*cos(2*PI*i/sides));
		point_y.push_back(y+radio*sin(2*PI*i/sides));
    }

    point_x.push_back(point_x[0]);
    point_y.push_back(point_y[0]);

    glBegin(GL_LINES);
    for(int  i= 0; i < point_x.size()-1; ++i) {
        glVertex2f(point_x[i],point_y[i]);
        glVertex2f(point_x[i+1],point_y[i+1]);
    }
    glEnd();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	turtle(30,1,0,0);
	turtle(30,0.5,0,1);
	turtle(30,0.4,1,1);	
	turtle(30,0.4,1,-1);
	turtle(30,0.4,-1,1);
	turtle(30,0.4,-1,-1);
	glFlush();
}