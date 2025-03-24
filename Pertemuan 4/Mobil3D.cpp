#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


float angle = 0.0, deltaAngle = 0.0, ratio;
float x = 0.0f, y = 1.75f, z = 15.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
int deltaMove = 0, h, w;
int bitmapHeight = 12;

void Reshape(int w1, int h1) {
    if (h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void orientMe(float ang) {
    lx = sin(ang);
    lz = -cos(ang);
}

void moveMeFlat(int i) {
    float speed = 0.01f; 
    x = x + i * (lx) * speed;
    z = z + i * (lz) * speed;
}

void Grid() {
    double i;
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float gap = 1.5;

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);

    for (i = Z_MIN; i < Z_MAX; i += gap) {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }
    for (i = X_MIN; i < X_MAX; i += gap) {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }

    glEnd();
}

void Mobil3D() {
    glPushMatrix();
    
    // Body bawah merah
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
        glScalef(4.0f, 1.0f, 2.0f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Body atas biru muda
    glColor3f(0.53f, 0.81f, 0.92f);
    glPushMatrix();
        glTranslatef(0.0f, 0.75f, 0.0f);
        glScalef(2.0f, 1.0f, 1.5f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Jendela depan
    glColor3f(0.8f, 0.9f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0f, 0.75f, 0.76f);
        glScalef(1.8f, 0.8f, 0.05f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Jendela belakang
    glPushMatrix();
        glTranslatef(0.0f, 0.75f, -0.76f);
        glScalef(1.8f, 0.8f, 0.05f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Jendela kiri
    glPushMatrix();
        glTranslatef(-1.01f, 0.75f, 0.0f);
        glScalef(0.05f, 0.8f, 1.4f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Jendela kanan
    glPushMatrix();
        glTranslatef(1.01f, 0.75f, 0.0f);
        glScalef(0.05f, 0.8f, 1.4f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Roda hitam
    glColor3f(0.1f, 0.1f, 0.1f);


    glPushMatrix();
        glTranslatef(-1.5f, -0.5f, 1.2f);  
        glRotatef(90, 0, 0, 1); 
        glutSolidTorus(0.1f, 0.4f, 12, 36);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.5f, -0.5f, 1.2f);
        glRotatef(90, 0, 0, 1);
        glutSolidTorus(0.1f, 0.4f, 12, 36);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.5f, -0.5f, -1.2f);
        glRotatef(90, 0, 0, 1);
        glutSolidTorus(0.1f, 0.4f, 12, 36);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.5f, -0.5f, -1.2f);
        glRotatef(90, 0, 0, 1);
        glutSolidTorus(0.1f, 0.4f, 12, 36);
    glPopMatrix();

    glPopMatrix();
}

void display() {
    if (deltaMove) moveMeFlat(deltaMove);
    if (deltaAngle) {
        angle += deltaAngle;
        orientMe(angle);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);

    Grid();
    Mobil3D();

    glutSwapBuffers();
    glFlush();
}

void pressKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: deltaAngle = -0.01f; break;
        case GLUT_KEY_RIGHT: deltaAngle = 0.01f; break;
        case GLUT_KEY_UP: deltaMove = 1; break;
        case GLUT_KEY_DOWN: deltaMove = -1; break;
    }
}

void releaseKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: if (deltaAngle < 0.0f) deltaAngle = 0.0f; break;
        case GLUT_KEY_RIGHT: if (deltaAngle > 0.0f) deltaAngle = 0.0f; break;
        case GLUT_KEY_UP: if (deltaMove > 0) deltaMove = 0; break;
        case GLUT_KEY_DOWN: if (deltaMove < 0) deltaMove = 0; break;
    }
}

const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void lighting() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void init(void) {
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Mobil 3D");

    glutIgnoreKeyRepeat(1);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);

    lighting();
    init();
    glutMainLoop();

    return 0;
}















