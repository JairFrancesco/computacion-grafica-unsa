#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;
bool fullscreen = false;
bool mouseDown = false;

GLfloat xRotated, yRotated, zRotated;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

//LINEA 3D USANDO ALGORITMO INCREMENTAL
void line3dIncremental(float x1, float y1, float z1, float x2,float y2,float z2)
{
  glBegin(GL_POINTS);
  float m,x,y,z,dy,dx;
  dy=y2-y1;
  dx=x2-x1;
  m=dy/dx;
  for(x=x1;x<=x2;x+=0.01){
      y=(y1+m*(x-x1));
      glVertex3f(x,y,x);
  }
  glEnd();
  glFlush();
}

void displayLine3d(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 3.0f,0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,1,0);
    glBegin(GL_LINES); //y
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 2.0f, 0.0f);
    glEnd();
    glColor3f(0,1,0);
    glBegin(GL_LINES);//x
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(2.0f, 0.0f, 0.0f);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_LINES); //z
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 2.0f);
    glEnd();

    glColor3f(1,1,1);
    glPointSize(4);
    line3dIncremental(-0.5f, -0.5f,-0.5f,0.5f,0.5f,0.5f);
    glColor3f(0,1,1);

    glFlush();
    glutSwapBuffers();
}

void resize(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    mouseDown = true;
    xdiff = x - yrot;
    ydiff = -y + xrot;
  }
  else
    mouseDown = false;
}

void mouseMotion(int x, int y)
{
  if (mouseDown)
  {
    yrot = x - xdiff;
    xrot = y + ydiff;
    glutPostRedisplay();
  }

}


void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

int main( int argc, char **argv )
{
    glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
    glutCreateWindow("Line 3D using Incremental Algorithm");

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0f);


    glutDisplayFunc(displayLine3d);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutReshapeFunc(resize);

    glutMainLoop();
    return 0;
}










