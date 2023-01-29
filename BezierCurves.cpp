#pragma region Librerias
#ifdef _WIN32
#include <GL/glut.h>
#elif defined(_APPLE_)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif*/disc
#include <iostream>
#include <math.h>
#include <stdlib.h> 
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;
#pragma endregion

#pragma region Variables 
GLdouble x, y, z;
GLdouble tx, ty, tz;
int parametro;
GLfloat cop_x = 4, cop_y = -4, cop_z = -4;
GLdouble ATx = 1.0, ATy = 0, ATz = 0;
GLfloat trasladar;
int op, op2;
GLint var_x1, var_y1, var_x2, var_y2, var_x3, var_y3, var_x4, var_y4;
GLint a1, a2, a3, a4;
float d = 0;
float e = 1;
bool check = false;
//Puntos para Bezier
//para u = 0, u = 1/3, u = 2/3, u = 1
GLfloat P0[3] = { 7,0,0 }, P1[3] = { 5,1,0 }, P2[3] = { 15,0,0 }, P3[3] = { 0,4,0 };
//Tres parametros
Matrix<float, 3, 3> MatrizA;
Matrix<float, 3, 3> MatrizAinversa;
Matrix<float, 3, 1>Matrizb;
Matrix<float, 3, 1> MatrizX;
//Cuatro parametros
Matrix<float, 4, 4> MatrizA2;
Matrix<float, 4, 4> MatrizAinversa2;
Matrix<float, 4, 1>Matrizb2;
Matrix<float, 4, 1> MatrizX2;
#pragma endregion

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 300.0);
	glFlush();
}
void timer(int id) {//Esta función va actualizando la pantalla
	//Idea para la funcion:
	//Para el if usamos la condición u donde u=0 arranca la esfera y u<1 con while donde termina su recorrido
	//Y pasamos a otro else if para qeu vaya al revez en 20 segundos
	if (d <= 1)
	{
		tx = (P0[0] * ((-4.5 * pow(d, 3)) + (9 * pow(d, 2)) - (5.5 * (d)))) + (P1[0] * (13.5 * pow(d, 3) - (22.5 * pow(d, 2) + (9 * d))) + (P2[0] * (-13.5 * pow(d, 3) + (18 * pow(d, 2)) - 4.5 * d)) + (P3[0] * (4.5 + pow(d, 3) - (4.5 * pow(d, 2)) + d)));
		//Para y
		ty = (P0[1] * ((-4.5 * pow(d, 3)) + (9 * pow(d, 2)) - (5.5 * (d)))) + (P1[1] * (13.5 * pow(d, 3) - (22.5 * pow(d, 2) + (9 * d))) + (P2[1] * (-13.5 * pow(d, 3) + (18 * pow(d, 2)) - 4.5 * d)) + (P3[1] * (4.5 + pow(d, 3) - (4.5 * pow(d, 2)) + d)));
		//Para z
		tz = (P0[2] * ((-4.5 * pow(d, 3)) + (9 * pow(d, 2)) - (5.5 * (d)))) + (P1[2] * (13.5 * pow(d, 3) - (22.5 * pow(d, 2) + (9 * d))) + (P2[2] * (-13.5 * pow(d, 3) + (18 * pow(d, 2)) - 4.5 * d)) + (P3[2] * (4.5 + pow(d, 3) - (4.5 * pow(d, 2)) + d)));
		//cout << trasladar << endl;
		d += 0.001;
		glutPostRedisplay();
		glutTimerFunc(10, timer, 1);
		glFlush();
	}
}

void timer2(int id) {//Esta función va actualizando la pantalla
	//Idea para la funcion:
	//Para el if usamos la condición u donde u=0 arranca la esfera y u<1 con while donde termina su recorrido
	//Y pasamos a otro else if para qeu vaya al revez en 20 segundos
	if (d >= 0)
	{
		tx = (P0[0] * ((-4.5 * pow(d, 3)) + (9 * pow(d, 2)) - (5.5 * (d)))) + (P1[0] * (13.5 * pow(d, 3) - (22.5 * pow(d, 2) + (9 * d))) + (P2[0] * (-13.5 * pow(d, 3) + (18 * pow(d, 2)) - 4.5 * d)) + (P3[0] * (4.5 + pow(d, 3) - (4.5 * pow(d, 2)) + d)));
		//Para y
		ty = (P0[1] * ((-4.5 * pow(d, 3)) + (9 * pow(d, 2)) - (5.5 * (d)))) + (P1[1] * (13.5 * pow(d, 3) - (22.5 * pow(d, 2) + (9 * d))) + (P2[1] * (-13.5 * pow(d, 3) + (18 * pow(d, 2)) - 4.5 * d)) + (P3[1] * (4.5 + pow(d, 3) - (4.5 * pow(d, 2)) + d)));
		//Para z
		tz = (P0[2] * ((-4.5 * pow(d, 3)) + (9 * pow(d, 2)) - (5.5 * (d)))) + (P1[2] * (13.5 * pow(d, 3) - (22.5 * pow(d, 2) + (9 * d))) + (P2[2] * (-13.5 * pow(d, 3) + (18 * pow(d, 2)) - 4.5 * d)) + (P3[2] * (4.5 + pow(d, 3) - (4.5 * pow(d, 2)) + d)));
		//cout << trasladar << endl;
		d -= 0.001;
		glutPostRedisplay();
		glutTimerFunc(20, timer2, 1);
		glFlush();
	}
}
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}
void menuTresPar() {
	cout << "Ingrese un punto (x1,y1):" << endl;
	cin >> var_x1;
	cin >> var_y1;
	cout << "Ingrese un punto (x2,y2):" << endl;
	cin >> var_x2;
	cin >> var_y2;
	cout << "Ingrese un punto (x3,y3):" << endl;
	cin >> var_x3;
	cin >> var_y3;
}
void TresParametros() {
	//Calculos
	menuTresPar();
	MatrizA << 1, var_x1, pow(var_x1, 2), 1, var_x2, pow(var_x2, 2), 1, var_x3, pow(var_x3, 2);
	MatrizAinversa = MatrizA.inverse();
	Matrizb << var_y1, var_y2, var_y3;
	MatrizX = MatrizAinversa * Matrizb;
	cout << "La matriz es:" << endl;
	cout << MatrizX << endl;
	cout << "La funcion es:" << endl;
	cout << MatrizX(0, 0) << " + " << MatrizX(1, 0) << "x + " << MatrizX(2, 0) << "x^2" << endl;
}
void menu4Par() {
	cout << "Ingrese un punto (x1,y1):" << endl;
	cin >> var_x1;
	cin >> var_y1;
	cout << "Ingrese un punto (x2,y2):" << endl;
	cin >> var_x2;
	cin >> var_y2;
	cout << "Ingrese un punto (x3,y3):" << endl;
	cin >> var_x3;
	cin >> var_y3;
	cout << "Ingrese un punto (x4,y4):" << endl;
	cin >> var_x4;
	cin >> var_y4;
}
void CuatroParametros() {
	menu4Par();
	//Rellenamos la matriz
	MatrizA2 << 1, var_x1, pow(var_x1, 2), pow(var_x1, 3),
		1, var_x2, pow(var_x2, 2), pow(var_x2, 3),
		1, var_x3, pow(var_x3, 2), pow(var_x3, 3),
		1, var_x4, pow(var_x4, 2), pow(var_x4, 3);
	//Los otros calculos
	MatrizAinversa2 = MatrizA2.inverse();
	Matrizb2 << var_y1, var_y2, var_y3, var_y4;
	MatrizX2 = MatrizAinversa2 * Matrizb2;
	//Consola
	cout << "La matriz es:" << endl;
	cout << MatrizX2 << endl;
	cout << "La funcion es:" << endl;
	cout << MatrizX2(0, 0) << " + " << MatrizX2(1, 0) << "x + " << MatrizX2(2, 0) << "x^2" << MatrizX2(3, 0) << "x^3" << endl;
}

void CurvaBezier() {
	//Cambio parametros de camara
	cop_x = 40.0, cop_y = -40.0, cop_z = -40.0;
	for (float u = 0; u <= 1; u += 0.001) {
		//Para x
		x = (P0[0] * ((-4.5 * pow(u, 3)) + (9 * pow(u, 2)) - (5.5 * (u)))) + (P1[0] * (13.5 * pow(u, 3) - (22.5 * pow(u, 2) + (9 * u))) + (P2[0] * (-13.5 * pow(u, 3) + (18 * pow(u, 2)) - 4.5 * u)) + (P3[0] * (4.5 + pow(u, 3) - (4.5 * pow(u, 2)) + u)));
		//Para y
		y = (P0[1] * ((-4.5 * pow(u, 3)) + (9 * pow(u, 2)) - (5.5 * (u)))) + (P1[1] * (13.5 * pow(u, 3) - (22.5 * pow(u, 2) + (9 * u))) + (P2[1] * (-13.5 * pow(u, 3) + (18 * pow(u, 2)) - 4.5 * u)) + (P3[1] * (4.5 + pow(u, 3) - (4.5 * pow(u, 2)) + u)));
		//Para z
		z = (P0[2] * ((-4.5 * pow(u, 3)) + (9 * pow(u, 2)) - (5.5 * (u)))) + (P1[2] * (13.5 * pow(u, 3) - (22.5 * pow(u, 2) + (9 * u))) + (P2[2] * (-13.5 * pow(u, 3) + (18 * pow(u, 2)) - 4.5 * u)) + (P3[2] * (4.5 + pow(u, 3) - (4.5 * pow(u, 2)) + u)));
		glPointSize(1);
		glBegin(GL_POINTS);
		glColor3f(0.5, 1, 1);
		glVertex3f(x, y, z);
		glEnd();
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cop_x, cop_y, cop_z, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	switch (op2) {
	case 1:
		for (float i = var_x1; i <= var_x3; i += 0.5) {
			parametro = (MatrizX(0, 0)) + (MatrizX(1, 0) * i) + (MatrizX(2, 0) * ((pow(i, 2))));
			glPointSize(10);
			glBegin(GL_POINTS);
			glColor3f(0, 1, 0.5);
			glVertex2f(i, parametro);
			glEnd();
		}
		break;
	case 2:
		for (float i = var_x1; i <= var_x4; i += 0.5) {
			parametro = (MatrizX2(0, 0)) + (MatrizX2(1, 0) * i) + (MatrizX2(2, 0) * (pow(i, 2)) + (MatrizX2(3, 0) * (pow(i, 3))));
			glPointSize(10);
			glBegin(GL_POINTS);
			glColor3f(0, 0.5, 1);
			glVertex2f(i, parametro);
			glEnd();
		}
		break;
	case 3:
		CurvaBezier();
		break;
	case 4:
		CurvaBezier();
		glTranslatef(tx, ty, tz); //Aqui traladamos el objeto en pantalla eje x , eje y, eje z
		//Dibujamos la esfera
		glColor3f(1, 0, 0);
		glutSolidSphere(1, 20, 20);
		glFlush();
		break;
	}
}


int main(int argc, char* argv[])
{
	cout << "Para seleccionar algun punto:" << endl << endl;
	cout << "1. Interpolacion con 3 parametros." << endl;
	cout << "2. Interpolacion con 4 parametros." << endl;
	cout << "3. Interpolacion de Bezier." << endl;
	cout << "4. Animacion esfera." << endl;
	cin >> op;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Tarea Corte 3");
	glutTimerFunc(1, timer, 1);
	glutTimerFunc(2, timer2, 1);
	glutReshapeFunc(reshape);
	init();
	switch (op) {
	case 1:
	{
		TresParametros();
		op2 = op;
		display();
	}
	break;
	case 2:
		CuatroParametros();
		op2 = op;
		display();
		break;
	case 3:
		CurvaBezier();
		op2 = op;
		display();
		break;
	default:
		CurvaBezier();
		op2 = op;
		display();
		break;
	}
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}