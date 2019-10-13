#include <GL/glut.h>
#include <iostream>

using namespace std;

typedef float point3[3];
point3 v[]={{0.0, 0.0,0.0}, {6.0, 0.0,0.0}, {3.0, 0.0,6.0}, {3.0,6,3}};
int n;


//triangulo
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);


    glColor3f(0.0,1.0,0.0);
    glVertex2fv(v[1]);
    glVertex2fv(v[2]);
    glVertex2fv(v[3]);

    glColor3f(0.0,0.0,1.0);
    glVertex2fv(v[2]);
    glVertex2fv(v[0]);
    glVertex2fv(v[3]);

    glColor3f(1.0,1.0,10);
    glVertex2fv(v[0]);
    glVertex2fv(v[1]);
    glVertex2fv(v[2]);

    // La función glColor define el color de rellenado actual y lleva como parámetros los valores de las componentes RGB del color deseado
    glColor3f(0.0,1.0,0.0);
    glVertex2fv(v[0]);
    glVertex2fv(v[1]);
    glVertex2fv(v[3]);

    glEnd();
    glFlush();
}
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-6, 10, -10, 10,6,-6);
    glMatrixMode(GL_MODELVIEW);
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0,0.0,0.0);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(500, 500);
    glutCreateWindow("Rellenado de poligono");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}
