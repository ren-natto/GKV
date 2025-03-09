#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>

void Mobil() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glBegin(GL_QUAD_STRIP);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.6, -0.2, 0.0);
    glVertex3f(0.6, -0.2, 0.0);
    glVertex3f(-0.4, 0.05, 0.0);
    glVertex3f(0.8, 0.05, 0.0);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.2, 0.05, 0.0);
    glVertex3f(0.5, 0.05, 0.0);
    glVertex3f(0.0, 0.2, 0.0);
    glVertex3f(0.5, 0.2, 0.0);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.6, 0.05, 0.0);
    glVertex3f(0.65, 0.05, 0.0);
    glVertex3f(0.65, 0.175, 0.0);
    glVertex3f(0.7, 0.175, 0.0);
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.575, -0.175, 0.0);
    glVertex3f(0.575, -0.175, 0.0);
    glVertex3f(-0.375, 0.025, 0.0);
    glVertex3f(0.775, 0.025, 0.0);
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.15, 0.05, 0.0);
    glVertex3f(0.475, 0.05, 0.0);
    glVertex3f(0.0, 0.175, 0.0);
    glVertex3f(0.475, 0.175, 0.0);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-0.55, -0.15, 0.0); 
    glVertex3f(-0.4, -0.15, 0.0);
    glVertex3f(-0.5, -0.1, 0.0);
    glVertex3f(-0.4, -0.1, 0.0);
    glEnd();

    glPushMatrix();
    glTranslatef(-0.3, -0.2, 0.0); 
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 0.0f); 
    glVertex2f(0.0, 0.0); 
    int numSegments = 100;
    float radius = 0.1;
    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * M_PI * float(i) / float(numSegments);
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(dx, dy);
    }
    glEnd();
    glPopMatrix();

    
    glPushMatrix();
    glTranslatef(0.4, -0.2, 0.0); 
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 0.0f); 
    glVertex2f(0.0, 0.0); 
    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * M_PI * float(i) / float(numSegments);
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(dx, dy);
    }
    glEnd();
    glPopMatrix();

    glFlush();
    glPopMatrix();
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitWindowSize(640,480);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Mobil");
	glutDisplayFunc(Mobil);
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}

