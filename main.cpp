#include <GL/glut.h>
#include "Vector_tools.h"
#include "Camara.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool command = false; /* command mode */
char strCommand[256];

static Camara *MiCamara;
static int spot_move = 0;
static int old_x, old_y;


/*
Laboratorio 2:
-Mover la camara con el mouse
-Dotar al programa de una tecla que permita cambiar el modo de proyección entre ORTOGONAL y PERSPECTIVA
-Mover el objeto en la proyeccion (con las teclas)
-Programar otros modos de movimiento de cámara como son el MODO PAN o el MODO TRÍPODE
*/


void display(void) {
    float At[3];
    float Direction[3];
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    MiCamara->SetGLCamera();
    glPushMatrix();

    //Dibujar piramide
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);

      // Right
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);

      // Back
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f, -1.0f, -1.0f);

      // Left
      glColor3f(1.0f,0.0f,0.0f);       // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f,0.0f,1.0f);       // Blue
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glColor3f(0.0f,1.0f,0.0f);       // Green
      glVertex3f(-1.0f,-1.0f, 1.0f);
    
    glEnd();   // Done drawing the pyramid

    glPopMatrix();
    
    glutSwapBuffers();
}

void parseCommand(char* strCommandParse) {
    char *strToken0;
    char *strToken1;
    double val;
    strToken0 = strtok(strCommandParse, " ");
    while ((strToken1 = strtok(NULL, " ")) != NULL) {
        val = atof(strToken1);
        if (!strcmp("fd", strToken0)) { // FORWARD
            glTranslatef(0.0, 0.0, val);
        } else if (!strcmp("bk", strToken0)) { // BACK
            glTranslatef(0.0, 0.0, -val);
        } else if (!strcmp("rt", strToken0)) { // RIGHT
            glRotatef(-val, 0., 1., 0.);
        } else if (!strcmp("lt", strToken0)) { // LEFT
            glRotatef(val, 0., 1., 0.);
        } else if (!strcmp("up", strToken0)) { // UP
            glRotatef(val, 1., 0., 0.);
        } else if (!strcmp("dn", strToken0)) { // DOWN
            glRotatef(-val, 1., 0., 0.);
        }
        strToken0 = strtok(NULL, " ");
        display();
    }
    // EXIT COMMAND MODE
    if (strToken0 != NULL && strncmp(strToken0, "exit", 4) == 0) {
        command = false;
    } else if (strToken0 != NULL && !strcmp("home", strToken0)) {
        glLoadIdentity();
    }
}

/* Para que al cambiar el aspecto de la ventana se mantengan las proporciones de la escena y esta no se deforme. */
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    MiCamara->SetGLAspectRatioCamera();
}

void MouseMotion(int x, int y) {
    old_y = y;
    old_x = x;
}

void Tripode(int x, int y){
    float rotacion_x, rotacion_y;
    rotacion_x = (float)(old_x - x) * DEGREE_TO_RAD / 5;
    rotacion_y = (float)(old_y - y) * DEGREE_TO_RAD / 5;
    MiCamara->YawCamera(rotacion_x);
    MiCamara->PitchCamera(rotacion_y);
    old_y = y;
    old_x = x;
    glutPostRedisplay();
}

void Zoom(int x, int y) {

    float zoom;

    zoom = (float) ((y - old_y) * DEGREE_TO_RAD);
    old_y = y;

    switch (MiCamara->camMovimiento) {

        case CAM_EXAMINAR:
            if (MiCamara->camAperture + zoom > (5 * DEGREE_TO_RAD) && MiCamara->camAperture + zoom < 175 * DEGREE_TO_RAD)
                MiCamara->camAperture = MiCamara->camAperture + zoom;
            break;

    }

    glutPostRedisplay();
}


/* La función Examinar(int x, int y) moverá la cámara en el modo Examinar según los movimientos del ratón: */
void Examinar(int x, int y) {

    float rot_x, rot_y;

    rot_y = (float) (old_y - y);
    rot_x = (float) (x - old_x);
    MiCamara->Rotar_Latitud( rot_y * DEGREE_TO_RAD);
    MiCamara->Rotar_Longitud(rot_x * DEGREE_TO_RAD);

    old_y = y;
    old_x = x;

    glutPostRedisplay();

}


void Andar(int x, int y) {

    float rotacion_x, avance_y;

    avance_y = (float) (y - old_y) / 10;
    rotacion_x = (float) (old_x - x) * DEGREE_TO_RAD / 5;
    MiCamara->YawCamera(rotacion_x);
    MiCamara->AvanceFreeCamera(avance_y);

    old_y = y;
    old_x = x;

    glutPostRedisplay();
}

//-Mover la camara con el mouse
/*
La función mouse() que es pasada como parámetro será llamada cada vez que ocurra un
evento de pulsado de un botón del ratón. En ella se define qué operaciones se realizan cuando
se pulse un botón y se encuentra en un modo de movimiento de cámara o en otro:
*/
void mouse(int button, int state, int x, int y) {

    old_x = x;
    old_y = y;

    switch (button) {

        case GLUT_LEFT_BUTTON:

            switch (MiCamara->camMovimiento) {

                case CAM_EXAMINAR:
                    if (state == GLUT_DOWN)
                        glutMotionFunc(Zoom);
                    if (state == GLUT_UP) {
                        glutPassiveMotionFunc(Examinar);
                        glutMotionFunc(NULL);
                    }
                    break;

                case CAM_PASEAR:
                    if (state == GLUT_DOWN)
                        glutMotionFunc(Andar);
                    if (state == GLUT_UP)
                        glutMotionFunc(NULL);
                    break;

                case CAM_TRIPODE:
                    if (state == GLUT_DOWN) glutMotionFunc(Tripode);
                    if (state == GLUT_UP) glutMotionFunc(NULL);
                    break;
            }

        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                //glutMotionFunc(scale);
                break;

        default:
            break;

    }

    glutPostRedisplay();
}



void keyboard(unsigned char key, int x, int y) {
    if (command) {
        if (key == 13) {
            strcat(strCommand, " ");
            if (strlen(strCommand) == 1) command = false;
            parseCommand(strCommand);
            strcpy(strCommand, "");
        } else {
            char strKey[2] = " ";
            strKey[0] = key;
            printf(strKey);
            strcat(strCommand, strKey);
        }
    } else {
        switch (key) {
            case 'h':
                printf("help\n\n");
                printf("c - Toggle culling\n");
                printf("q/escape - Quit\n\n");
                break;
            case 'c':
                if (glIsEnabled(GL_CULL_FACE))
                    glDisable(GL_CULL_FACE);
                else
                    glEnable(GL_CULL_FACE);
                break;
            case '1':
                glRotatef(1.0, 1., 0., 0.);
                break;
            case '2':
                glRotatef(1.0, 0., 1., 0.);
                break;
            case 'i':
                command = true;
                break;
            case 'q':
            case 27:
                delete MiCamara;
                exit(0);
                break;
        }
    }
    glutPostRedisplay();
}

//Cambios de perspectiva de la camara (ortogonal a perspectiva)
//Mover el objeto en la proyeccion (con las teclas)
static void SpecialKey(int key, int x, int y) {
    switch (key) {

        case GLUT_KEY_F1:
            glutPassiveMotionFunc(MouseMotion);
            MiCamara->camMovimiento = CAM_STOP;
            printf("%s\n","F1, CAM_STOP" );
            break;
        case GLUT_KEY_F2:
            glutPassiveMotionFunc(Examinar);
            MiCamara->camMovimiento = CAM_EXAMINAR;
            printf("%s\n","F2, CAM_EXAMINAR" );
            break;
        case GLUT_KEY_F3:
            glutPassiveMotionFunc(MouseMotion);
            MiCamara->camMovimiento = CAM_PASEAR;
            MiCamara->camAtY = 0;
            MiCamara->camViewY = 0;
            MiCamara->SetDependentParametersCamera();
            printf("%s\n","F3, CAM_PASEAR: PERSPECTIVA" );
            break;
        
        
        case GLUT_KEY_PAGE_UP:
            //AvanceFreeCamera( MiCamara, 0.5f );
            if (MiCamara->camAperture < 175 * DEGREE_TO_RAD)
                MiCamara->camAperture = MiCamara->camAperture + 2.5f * DEGREE_TO_RAD;
            break;

        case GLUT_KEY_PAGE_DOWN:
            if (MiCamara->camAperture > 5 * DEGREE_TO_RAD)
                MiCamara->camAperture = MiCamara->camAperture - 2.5f * DEGREE_TO_RAD;
            break;

        case GLUT_KEY_UP:
            MiCamara->Rotar_Latitud( 2.5f * DEGREE_TO_RAD);
            break;

        case GLUT_KEY_DOWN:
            MiCamara->Rotar_Latitud( -2.5f * DEGREE_TO_RAD);
            break;

        case GLUT_KEY_LEFT:
            MiCamara->Rotar_Longitud( -2.5f * DEGREE_TO_RAD);
            break;

        case GLUT_KEY_RIGHT:
            MiCamara->Rotar_Longitud(2.5f * DEGREE_TO_RAD);
            break;
        
        case GLUT_KEY_F4: //RESET: VISTA NORMAL
            MiCamara->camAtX = 0;
            MiCamara->camAtY = 0;
            MiCamara->camAtZ = 0;
            MiCamara->camViewX = 0;
            MiCamara->camViewY = 1;
            MiCamara->camViewZ = -3;
            MiCamara->SetDependentParametersCamera();
            printf("%s\n","F4, Reset, vista normal" );
            break;

        case GLUT_KEY_F5:
            /*
            if (current_mode != 0) break;
            current_mode = 3;*/
            MiCamara->camAtY = 0;
            MiCamara->camViewY = 0;
            MiCamara->camMovimiento = CAM_TRIPODE;
            MiCamara->SetDependentParametersCamera();
            printf("%s\n","F5, CAM TRIPODE" );
            break;
        default:
            printf("key %d %c X %d Y %d\n", key, key, x, y);
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);

    // Colocamos la cámara en (0,1,-3) mirando hacia (0,0,0)
    MiCamara = new Camara(0.0f, 1.0f, -3.0f);

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Piramide");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKey);

    //Mouse
    glutMouseFunc(mouse); //Pulsado de Botones
    glutMotionFunc(NULL); //Movimiento con Botones pulsados
    glutPassiveMotionFunc(MouseMotion); //Movimientos sin Botones pulsados

    glutMainLoop();
    return 0;
}
