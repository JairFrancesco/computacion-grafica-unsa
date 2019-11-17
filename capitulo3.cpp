#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>


/*
Capitulo 3: TRABAJOS PROPUESTOS
- Dibujar un rastro que consista en unas superficie en lugar de una línea. Para ello se puede utilizar glBegin(GL_QUAD_STRIP) que dibuja una
sucesión de rectángulos para cada pareja de puntos que recibe, como se muestra en la figura 3. Ya no bastará con tener un solo punto
inicial, el origen, sino que será necesario disponer además de otro perpendicular a él, por ejemplo el (0.1, 0.0, 0.0). En cada nuevo movimiento
será necesario añadir estos dos puntos transformados. El resultado es el que se muestra en la figura 4, en la que
se dibuja el rastro después de haber realizado 5 “fd .2”, 10 “rt 9 fd .2” y 5 “fd .2”.

3.4 PUNTOS A REALIZAR
Utilizando los comandos de logo representar una esfera compuesta por un conjunto de circunferencias en el espacio.
Utilizando los comandos de logo realizar la representación de una helicoidal. En la figura 5 se muestra el resultado de dicho comando.
*/


using namespace std;
float pi2 = 6.28318530718;
int np = 0;
float px[10000];
float py[10000];
float pz[10000];
GLdouble mModel[16];

void draw_line(float x1, float y1, float x2, float y2, float z1, float z2){
  glBegin(GL_LINES);

      glVertex3f(x1, y1, z1);
      glVertex3f(x2, y2, z2);


  glEnd();
}

void addPointToTrace()
{
	int i;
	GLdouble m[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, m);

  for (i = 0; i < 4; i++) {
  printf ("Row %i: %f \t%f \t%f \t%f \n", i+1, m[i+0],m[i+4],m[i+8],m[i+12]);
  }

	if (np == 0)
	{
		px[0] = 0;
		py[0] = 0;
		pz[0] = 0;
		np++;
	}
	px[np] = m[0] * px[0] + m[4] * py[0] +  m[8] * pz[0] + m[12];
	py[np] = m[1] * px[0] + m[5] * py[0] +  m[9] * pz[0] + m[13];
	pz[np] = m[2] * px[0] + m[6] * py[0] + m[10] * pz[0] + m[14];

  cout << "Punto: " << px[np] << " " << py[np] << " " << pz[np] << endl;


	np++;
}




void draw_circle(float radio, int num_vertices, float pos_x, float pos_y, float pos_z){
  float d_teta;
  d_teta = (pi2) / num_vertices;
  float teta = 0;




  float x2, y2,x1, y1;

  for(int i = 0; i < num_vertices; i++){
    x1 = cos(d_teta * i) * radio;
    y1 = sin(d_teta * i) * radio;
    x2 = cos(d_teta * (i + 1)) * radio;
    y2 = sin(d_teta * (i + 1)) * radio;
    draw_line(pos_x + x1, pos_y + y1, pos_x + x2, pos_y + y2, pos_z, pos_z);

  }

  // glFlush();

}

void draw(){
  glColor3f(1.0,1.0,1.0);

  // dibujando caparazon
  draw_circle(0.4, 34, 0.0, 0.0, 0.0);
  draw_circle(0.3, 34, 0.0, 0.0, 0.1);
  draw_circle(0.2, 34, 0.0, 0.0, 0.15);
  draw_circle(0.1, 34, 0.0, 0.0, 0.165);

  // dibujando cabeza
  draw_circle(0.15, 24, 0.0, 0.5, 0.0);

  //dibujando extremidades
  draw_circle(0.1, 24, -0.4, 0.3, 0.0);
  draw_circle(0.1, 24, 0.4,  0.3, 0.0);
  draw_circle(0.1, 24, -0.4, -0.3, 0.0);
  draw_circle(0.1, 24, 0.4,  -0.3, 0.0);

}

void displayTrace()
{
	int i;
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < np; i++){
		glVertex3f(px[i], py[i], pz[i]);
	}
	glEnd();
}


void display(void) {


  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glMultMatrixd(mModel);

  draw();

  glPopMatrix();

  displayTrace();

  glutSwapBuffers();

}

void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  gluLookAt(-2.0, 3.0, 4.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0);
  glGetDoublev(GL_MODELVIEW_MATRIX, mModel);
	glPopMatrix();

}


void keyboard(unsigned char key, int x, int y)
{
  glPushMatrix();
  glLoadIdentity();
  glMultMatrixd(mModel);


	switch (key)
	{
	case '8':
		glRotatef(1.0,1.,0.,0.);
		break;
	case '5':
		glRotatef(1.0,-1.,0.,0.);
		break;
	case '4':
		glRotatef(1.0,0.,0.,1.);
		break;
	case '6':
		glRotatef(1.0,0.,0.,-1.);
		break;
	case 'w':
		glTranslatef(0.0,0.1,0.);
    addPointToTrace();

		break;
	case 'a':
		glTranslatef(-0.1,0.,0.0);
    addPointToTrace();

		break;
	case 's':
		glTranslatef(0.0,-0.1,0.);
    addPointToTrace();

		break;
	case 'd':
		glTranslatef(0.1,0.0,0.0);
    addPointToTrace();

		break;
	case 'q':
		exit(0);
		break;
	}

  glGetDoublev(GL_MODELVIEW_MATRIX, mModel);
	glPopMatrix();
	glutPostRedisplay();
}


int main(int argc, char** argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Rastro");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
