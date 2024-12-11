// 绘制分形图形

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

GLsizei winWidth = 600, winHeight = 600;
GLfloat xComplexMin = -0.25, xComplexMax = 1.25;
GLfloat yComplexMin = -0.75, yComplexMax = 0.75;
GLint numPoints = 10000;
GLint numPoints1 ;
GLint numPoints2 ;
GLint iteration =1;
int choose = -1;

struct complexNum {
	GLfloat x, y;
};
void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
}
void plotPoint(complexNum z){
  glBegin(GL_POINTS);
	glVertex2f(z.x, z.y);
	glEnd();
}
void solveQuadraticEq(complexNum lambda, complexNum* z) {
	GLfloat lambdaMagSq, discrMag;
	complexNum discr;
	static complexNum four0verLambda = { 0.0, 0.0 };
	static GLboolean firstPoint = true;
	if (firstPoint) {
		lambdaMagSq = lambda.x * lambda.x + lambda.y * lambda.y;
		four0verLambda.x = 4.0 * lambda.x / lambdaMagSq;
		four0verLambda.y = -4.0 * lambda.y / lambdaMagSq;
		firstPoint = false;
	}
	discr.x = 1.0 - (z->x * four0verLambda.x - z->y * four0verLambda.y);
	discr.y = z->x * four0verLambda.y + z->y * four0verLambda.x;
	discrMag = sqrt(discr.x * discr.x + discr.y * discr.y);
	if (discrMag + discr.x < 0)z->x = 0;
	else z->x = sqrt((discrMag + discr.x) / 2.0);
	if (discrMag - discr.x < 0)z->y = 0;
	else z->y = 0.5 * sqrt((discrMag - discr.x) / 2.0);
	if (rand() < RAND_MAX / 2) {
		z->x = -z->x;
		z->y = -z->y;
	}
	if (discr.y < 0)z->x = -z->x;
	z->x = 0.5 * (1 - z->x);
}
void selfSqTransf(complexNum lambda, complexNum z, GLint numPoints) {
	GLint k;
	for (k = 0;k < numPoints;k++) {
		solveQuadraticEq(lambda, &z);
		plotPoint(z);
	}
}
void displayFcn(void)
{
	complexNum lambda = { 3.0,0.0 };
	complexNum z0 = { 1.5,0.4 };
	complexNum z1 = { -1.5,0.4 };
	complexNum z2 = { 1.5,0.4 };
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	if (choose == 1)
	{
		selfSqTransf(lambda, z0, numPoints);
	}
	else if (choose == 3) {
		selfSqTransf(lambda, z0, iteration);
	}
	else if (choose ==2)
	{
		glViewport(0, 0, winWidth/2, winHeight);
		glColor3f(0.0, 0.0, 1.0);
		selfSqTransf(lambda, z1, numPoints1);

		glViewport(winWidth / 2, 0, winWidth / 2, winHeight);
		glColor3f(0.0, 0.0, 1.0);
		selfSqTransf(lambda, z2, numPoints2);
	}
	glFlush();
}
void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0,newWidth,newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xComplexMin, xComplexMax, yComplexMin, yComplexMax);
	glClear(GL_COLOR_BUFFER_BIT);
}
void timer(int value) {
	if(iteration<10000){ iteration += 3; }
	else { iteration =10000; }
	glutPostRedisplay();
	glutTimerFunc(30, timer, 0);
}
int main(int argc, char** argv)
{ 
	//cout << "请选择功能" << endl;
	//cout << "1.选择迭代参数" << endl << "2.实现动画效果" << endl << "3.多个视图显示" << endl;
	
   
	while (choose != 0)
	{
		cout << "1.迭代次数" << endl << "2.多视图" << endl << "3.动画" << endl;
		cin >> choose;
		if (choose == 1)
		{
			cout << "请输入迭代次数" << endl;
			cin >> numPoints;
		}
		else if (choose == 2)
		{
			cout << "请输入第一个视口的迭代次数" << endl;
			cin >> numPoints1;
			cout << "请输入第二个视口的迭代次数" << endl;
			cin >> numPoints2;
		}
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowPosition(50,50);
		glutInitWindowSize(winWidth, winHeight);
		//glutCreateWindow("Self-Squaring Fractal");
		glutCreateWindow("分形");
		init();
		glutDisplayFunc(displayFcn);
		glutReshapeFunc(winReshapeFcn);
		if (choose == 3) {
			glutTimerFunc(30, timer, 0);
		}
		glutMainLoop();
	}
	
}