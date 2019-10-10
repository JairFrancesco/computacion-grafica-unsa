#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

using namespace std;

void Circulo_Poligono(int lados,double radio, double x, double y)
{
	glColor3f(1,0,0);

	float step = M_PI/lados;

	glBegin(GL_LINES);
	for(int i=0; i < lados; i++)
	{
		glVertex2f(x + cos(i*2*step)*radio,y + sin(i*2*step)*radio);
		glVertex2f(x + cos((i+1) * 2*step)*radio, y + sin((i+1) * 2*step)*radio);
	}
	glEnd();
	glFlush();




}


void Tortuga()
{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /** borra el fondo de la ventana */
		Circulo_Poligono(30,0.8,0,0);
		/*
		Circulo_Poligono(30,0.3,0,1.1);
		Circulo_Poligono(30,0.25,-0.95,0.4);
		Circulo_Poligono(30,0.25,0.95,0.4);
		Circulo_Poligono(30,0.25,-1,-0.3);
		Circulo_Poligono(30,0.25,1,-0.3);
		*/
		glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0,0,width,height); /* Donde se puede dibujar */
	glMatrixMode(GL_PROJECTION); /** Afecta la perspectiva */
	glLoadIdentity(); /** carga como matriz de proyeccion a la matriz identidad */
	gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0); /* define el angulo de campo de vista*/
	glMatrixMode(GL_MODELVIEW);/** OPeraciones que afectaran a la matriz de modelado */
	glLoadIdentity();
	gluLookAt(0.0,1.0,3.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 'w':
				glTranslatef(0.0,0.1,0.0);
				break;
		case 's':
				glTranslatef(0.0,-0.1,0.0);
				break;
		case 'a':
				glTranslatef(-0.1,0.0,0.0);
				break;
		case 'd':
				glTranslatef(0.1,0.0,0.0);
				break;
		case 'x':
				glTranslatef(0.0,0.0,-0.1);
				break;
		case 'z':
				glTranslatef(0.0,0.0,0.1);
				break;
		case 'j':
			glRotatef(1.0,0.0,0.0,1.0);
			break;
		case 'l':
			glRotatef(-1.0,0.0,0.0,1.0);
			break;
		case 'k':
			glRotatef(1.0,1.0,0.0,0.0);
			break;
		case 'i':
			glRotatef(-1.0,1.0,0.0,0.0);
			break;
		case 'm':
			glRotatef(1.0,0.0,1.0,0.0);
			break;
		case 'n':
			glRotatef(-1.0,0.0,1.0,0.0);
			break;
		case '-':
			glScalef(0.9,0.9,0.9);
			break;
		case '+':
			glScalef(1.1,1.1,1.1);
			break;
		case 'e':
				exit(0);
				break;
		}
		glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(512,512);
	glutInitWindowPosition(200,200);
	glutCreateWindow("Tortuga");
	glClearColor(1,1,1,1); /* color de fondo de la ventana */
	glutDisplayFunc(Tortuga);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
