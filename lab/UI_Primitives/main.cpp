#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <map>
#include <string>
#include <vector>
using namespace std;



GLsizei winWidth , winHeight; // Initial display window size.
int xi, xf, xt;
int yi ,yf, yt;
int background = 0;
int drawing = 3;
int figure = 6;
typedef enum {background_1 ,background_2 ,background_3 ,drawing_1 ,drawing_2 ,drawing_3 ,gLine ,gCircle ,gSquare ,gElipse} opcionesMenu;
void put_pixel(int x, int y)
{
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
void DDA (int x1,int y1,int x2,int y2)
{
	float ax,ay,x,y,orientacion;
	abs(x2-x1)>=abs(y2-y1)?orientacion=abs(x2-x1):orientacion=abs(y2-y1);
	ax=(x2-x1)/orientacion;
	ay=(y2-y1)/orientacion;
	x=(float)x1;
	y=(float)y1;
	for (int i = 0; i <= orientacion; ++i){
		put_pixel(floor(x),floor(y));
		x=x+ax;
		y=y+ay;
	}
}
void LSquare(int x1, int y1, int x2, int y2)
{
	DDA(x1,y1,x2,y1);
	DDA(x1,y2,x2,y2);
	DDA(x1,y1,x1,y2);
	DDA(x2,y2,x2,y1);
}
void Square(int x1,int y1,int x2,int y2)
{
	int tam;
	bool def_axis;
	abs(x2-x1)>=abs(y2-y1)?def_axis=true:def_axis=false;
	if(def_axis) tam=abs(x2-x1);
	else tam=abs(y2-y1);
	// Cuadrantes
	if(x2-x1>=0 && y2-y1 >=0)
		LSquare(x1,y1,x1+tam,y1+tam);
	else if(x2-x1>0 && y2-y1<0)
		LSquare(x1,y1,x1+tam,y1-tam);
	else if(x2-x1<0 && y2-y1<0)
		LSquare(x1,y1,x1-tam,y1-tam);
	else if(x2-x1<0 && y2-y1>0)
		LSquare(x1,y1,x1-tam,y1+tam);
}
void circlePlotPoints (int x1, int y1, int x2, int y2)
{
	put_pixel (x1 + x2, y1 + y2);
	put_pixel (x1 - x2, y1 + y2);
	put_pixel (x1 + x2, y1 - y2);
	put_pixel (x1 - x2, y1 - y2);
	put_pixel (x1 + y2, y1 + x2);
	put_pixel (x1 - y2, y1 + x2);
	put_pixel (x1 + y2, y1 - x2);
	put_pixel (x1 - y2, y1 - x2);
}

void circleMidpoint (int x, int y, GLint radius)
{
	GLint x1, y1;
	GLint p = 1 - radius; // Initial value for midpoint parameter.
	x1 = 0;
	y1 = radius;
	circlePlotPoints(x, y, x1, y1);
	/* Plot the initial point in each circle quadrant. */
	circlePlotPoints (x, y, x1, y1);
	/* Calculate next point and plot in each octant. */
	while (x1 < y1) {
		x1++;
		if (p < 0)
			p += 2 * x1 + 1;
		else {
			y1--;
			p += 2 * (x1-y1) + 1;
		}
		circlePlotPoints (x, y, x1, y1);
	}
}
void circle(int x1, int y1, int x2, int y2)
{
	GLint r = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
	circleMidpoint(x1,y1,r);
}
void PlotPoints(int xc,int yc, int x, int y)
{
	put_pixel(xc+x,yc+y);
	put_pixel(xc-x,yc+y);
	put_pixel(xc+x,yc-y);
	put_pixel(xc-x,yc-y);
}
void ElipseMidPoints(int xc, int yc, int rx, int ry)
{
	float x,y,rx2,ry2,p1,p2;
	x=0;
	y=ry;
	rx2=pow(rx,2);
	ry2=pow(ry,2);
	p1=ry2-(rx2*ry)+(0.25*rx2);
	while((ry2*x)<(rx2*y)){
		if(p1<0){ x++;
		p1=p1+(2*ry2*x)+ry2;
		}
		else{
			x++; y--;
			p1=p1+(2*ry2*x)-(2*rx2*y)+ry2;
		}
		PlotPoints(xc,yc,x,y);
	}
	p2=(ry2)*pow((x+0.5) ,2)+(rx2)*pow((y-1) ,2)-(rx2*ry2);
	while(y>0){
		if (p2>0){
			y--;
			p2=p2-(2*rx2*y) +rx2;
		}
		else{
			x++; y--;
			p2=p2+ (2*ry2*x)-(2*rx2*y)+rx2;
		}
		PlotPoints(xc,yc,x,y);
	}
}
void Elipse(int x1, int y1, int x2, int y2)
{
	GLint rx = abs(x2-x1);
	GLint ry = abs(y2-y1);
	ElipseMidPoints(x1,y1,rx,ry);
}
void Paint(int myFig)
{
	switch(myFig){
	case gLine: DDA(xi,yi,xf,yf); break;
	case gSquare: Square(xi,yi,xf,yf); break;
	case gCircle: circle(xi,yi,xf,yf); break;
	case gElipse: Elipse(xi,yi,xf,yf); break;
	}
}
void onMenu(int opcion)
{
	switch(opcion){
	case background_1: background = 0; break;
	case background_2: background = 1; break;
	case background_3: background = 2; break;
	case drawing_1: drawing = 3; break;
	case drawing_2: drawing = 4; break;
	case drawing_3: drawing = 5; break;
	case gLine: figure = 6; break;
	case gCircle: figure = 7; break;
	case gSquare: figure = 8; break;
	case gElipse: figure = 9; break;
	}
	glutPostRedisplay();
}
void creacionMenu()
{
	int mFigure , mBack , mDrawing , mMain;
	mFigure = glutCreateMenu(onMenu);
	glutAddMenuEntry("Line", gLine);
	glutAddMenuEntry("Circle", gCircle);
	glutAddMenuEntry("Square", gSquare);
	glutAddMenuEntry("Elipse", gElipse);
	mBack = glutCreateMenu(onMenu);
	glutAddMenuEntry("Black",background_1);
	glutAddMenuEntry("Dark Green",background_2);
	glutAddMenuEntry("Dark Blue",background_3);
	mDrawing = glutCreateMenu(onMenu);
	glutAddMenuEntry("White",drawing_1);
	glutAddMenuEntry("Light Green",drawing_2);
	glutAddMenuEntry("Light Blue",drawing_3);
	mMain = glutCreateMenu(onMenu);
	glutAddSubMenu("Figure",mFigure);
	glutAddSubMenu("Background Color",mBack);
	glutAddSubMenu("Drawing Color",mDrawing);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void resize(GLsizei w, GLsizei h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,w,0,h,1.f,-1.f);
	printf("Resize:: %dx%d\n",w,h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void display(void)
{
	int i;
	float colores[6][3] = {
		{0.00f, 0.00f, 0.00f},
	{0.06f, 0.25f, 0.13f},
		{0.10f, 0.07f, 0.33f},
	{1.00f, 1.00f, 1.00f},
		{0.12f, 0.50f, 0.26f},
	{0.20f, 0.14f, 0.66f},
	};
	glClearColor (colores[background][0],colores[background][1],colores[background][2], 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(colores[drawing][0],colores[drawing][1],colores[drawing][2]);
	Paint(figure);
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	for (i = -1; i <= 1; i++){
		glVertex2i(xi+i,yi);
		glVertex2i(xi,yi-i);
	}
	glEnd();
	glutSwapBuffers();
}
void mouse_move(int x, int y)
{
	xt = x;
	yt = winHeight -y;
	glutPostRedisplay();
}
void mouse_drag(int x, int y)
{
	xf = x;
	yf = winHeight - y;
	glutPostRedisplay();
}
typedef GLubyte Color[3];
void getPixel(int x, int y, Color rgb)
{
	glReadPixels(x, y, 1, 1, GL_RGB , GL_UNSIGNED_BYTE , rgb);
}
void mouse_click(int button , int state , int x, int y)
{
	Color c;
	if(state== GLUT_DOWN){
		xi=x;
		yi=winHeight - y;
		xf=xi;
		yf=yi;
		getPixel(xi, yi, c);
		printf("Position: %3d, %3d\n",xi,yi);
	}
	if(state==GLUT_UP){
		printf("Position 2: %3d, %3d\n",xf,yf);
	}
	glutPostRedisplay();
}
void normal_key(GLubyte key, int x, int y)
{
	char s[80] = "";
	if(glutGetModifiers() & GLUT_ACTIVE_SHIFT) sprintf(s, "%s SHIFT ", s);
	if(glutGetModifiers() & GLUT_ACTIVE_CTRL) sprintf(s, "%s CTRL ", s);
	if(glutGetModifiers() & GLUT_ACTIVE_ALT) sprintf(s, "%s ALT ", s);
	if(key >= 32 && key <= 128)
		printf("normal key: �%c� dec:%d %s\n", key, key, s);
	else
		printf("normal key: dec:%d %s\n",key,s);
	if(key==27)
		exit(0);
}
void special_key(int key, int x, int y)
{
	printf("special key # %d\n",key);
}
void timer_function(int value)
{
	printf("pointer %d, %d\n",xt,yt);
	glutTimerFunc(8000, timer_function , 1);
}
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(800,0);
	glutCreateWindow("CSUNSA");
	glutDisplayFunc(display);
	creacionMenu();
	glutReshapeFunc(resize);
	glutPassiveMotionFunc(mouse_move);
	glutMotionFunc(mouse_drag);
	glutMouseFunc(mouse_click);
	glutKeyboardFunc(normal_key);
	glutSpecialFunc(special_key);
	glutTimerFunc(33,timer_function ,1);
	glutMainLoop();
	return 0;
}
