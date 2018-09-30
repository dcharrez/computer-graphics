#include <GL/glut.h>
#include <cstdio>
#include <vector>
#include <cmath>
#include <string.h>
#include <iostream>

using namespace std;

int np = 0;
float px [10000];
float py [10000];
float pz [10000];

GLdouble mModel[16];

void display(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void turtle(int sides,float radio,int x,int y);
void draw();

void addPointToTrace() {
	int i;
	GLdouble m[16];
	glGetDoublev (GL_MODELVIEW_MATRIX, m);
	// print the matrix
	printf ("\nMatrix:\n");
	for (i = 0; i < 4; i++) {
	printf ("Row %i: %f \t%f \t%f \t%f \n",
	i+1, m[i+0],m[i+4],m[i+8],m[i+12]);
	}
	// if is the first point
	if (np == 0) { // add the first point
	px [0] = 0;
	py [0] = 0;
	pz [0] = 0;
	np++;
	}
	px [np] = m[0] * px [0] + m[4] * py [0] + m[8] * pz [0] + m[12];
	py [np] = m[1] * px [0] + m[5] * py [0] + m[9] * pz [0] + m[13];
	pz [np] = m[2] * px [0] + m[6] * py [0] + m[10] * pz [0] + m[14];
	printf ("Point %i: %f \t%f \t%f \n",
	np, px[np],py[np],pz[np]);
	np++;
}

void displayTrace() {
	int i;
	glColor3f(0.0,0.0,0.0) ;
	glBegin(GL_LINE_STRIP);
	// glBegin(GL_QUAD_STRIP);
	for (i = 0; i < np; i++) {
	glVertex3f (px[i],py[i],pz[i]);
	}
	glEnd();
}


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

	// glMatrixMode(GL_MODELVIEW);
	// glPushMatrix();
	// glLoadIdentity();
	// glGetDoublev (GL_MODELVIEW_MATRIX, mModel);
	// glPopMatrix();

	return 0;
}

void keyboard(unsigned char key, int x, int y) {

   switch(key) {
    
    case 'w' :
        cout<<"up"<<endl;
        glTranslatef(0.0, 0.1 ,0.0);
        addPointToTrace();
        break;
    case 'a' : 
        cout<<"left"<<endl;
        glTranslatef(-0.1, 0.0 ,0.0);
        addPointToTrace();
        break;
    case 's' :
        cout<<"down"<<endl;
        glTranslatef(0.0, -0.1, 0);
        addPointToTrace();
        break;
    case 'd' :
        cout<<"right"<<endl;
        glTranslatef(0.1, 0 ,0.0);
        addPointToTrace();
        break;
    case 'i' :
        cout<<"up"<<endl;
        glRotatef(5.0, 1.0, 0.0, 0.0);
        addPointToTrace();
        break;
    case 'j' : 
        cout<<"left"<<endl;
        glRotatef(-5.0, 0.0, 1.0, 0.0);
        addPointToTrace();
        break;
    case 'k' :
        cout<<"down"<<endl;
        glRotatef(-5.0, 1.0, 0.0, 0.0);
        addPointToTrace();
        break;
    case 'l' :
        cout<<"right"<<endl;
        glRotatef(5.0, 0.0, 1.0, 0.0);
        addPointToTrace();
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
	glPushMatrix();
	glMultMatrixd(mModel);
	
	glPopMatrix();
	glColor3f(1.0,0.0,0.0);
	draw();
	// glutWireTorus(0.25,0.75, 28, 28);
	glColor3f(0.0,0.0,1.0) ;
	glutWireCube(.60) ;
	displayTrace();
	glutSwapBuffers();
}

// void display(void) {
// 	glClearColor(1.0, 1.0, 1.0, 0.0);
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 	glColor3f(1.0,0.0,0.0);
// 	draw();
// 	// glutWireTorus(0.25,0.75, 28, 28);
// 	glColor3f(0.0,0.0,1.0) ;
// 	glutWireCube(.60) ;
// 	glutSwapBuffers();
// }

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