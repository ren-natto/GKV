#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <cstdio>

struct Camera {
    float eyeX, eyeY, eyeZ;
    float centerX, centerY, centerZ;
    float upX, upY, upZ;
    
    Camera(float ex, float ey, float ez, float cx, float cy, float cz, float ux, float uy, float uz) :
        eyeX(ex), eyeY(ey), eyeZ(ez), centerX(cx), centerY(cy), centerZ(cz), upX(ux), upY(uy), upZ(uz) {}
};

std::vector<Camera> orthoCameras;
std::vector<Camera> perspCameras;

int projectionType = 0;
int viewType = 0;
float angle = 0.0f;
bool showAxes = false;

void initCameras() {
    orthoCameras.push_back(Camera(5.0f, 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
    orthoCameras.push_back(Camera(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
    orthoCameras.push_back(Camera(10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
    orthoCameras.push_back(Camera(0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f));
    orthoCameras.push_back(Camera(5.0f, 5.0f, 2.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
    orthoCameras.push_back(Camera(5.0f, 3.0f, 7.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
 
    perspCameras.push_back(Camera(0.0f, 3.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
    perspCameras.push_back(Camera(8.0f, 8.0f, 8.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
    perspCameras.push_back(Camera(8.0f, 8.0f, -8.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
}

void drawWheel(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    
    glColor3f(0.3f, 0.3f, 0.3f);
    glutSolidTorus(0.1, 0.5, 20, 20);
    
    glColor3f(0.7f, 0.7f, 0.7f);
    for(int i = 0; i < 8; i++) {
        glPushMatrix();
        glRotatef(45*i, 0, 0, 1);
        glScalef(1, 0.1, 0.1);
        glutSolidCube(0.8);
        glPopMatrix();
    }
    
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidSphere(0.2, 20, 20);
    
    glPopMatrix();
}

void drawWindows() {
    for(int side = -1; side <= 1; side += 2) {
        glColor3f(0.7f, 0.9f, 1.0f);
        for(int i = -1; i <= 1; i++) {
            glPushMatrix();
            glTranslatef(i*1.2f, 0.5f, 0.76f * side);
            glScalef(0.8f, 0.6f, 0.01f);
            glutSolidCube(1.0);
            glPopMatrix();
        }
        
        glColor3f(0.9f, 0.8f, 0.2f);
        for(int i = -1; i <= 1; i++) {
            glPushMatrix();
            glTranslatef(0.0f, -0.4f + i*0.3f, 0.76f * side);
            glScalef(3.9f, 0.03f, 0.01f);
            glutSolidCube(1.0);
            glPopMatrix();
        }
        
        for(float x = -1.8f; x <= 1.8f; x += 0.6f) {
            glPushMatrix();
            glTranslatef(x, 0.0f, 0.76f * side);
            glScalef(0.03f, 1.0f, 0.01f);
            glutSolidCube(1.0);
            glPopMatrix();
        }
    }
}

void drawTrainBody() {
    glColor3f(0.8f, 0.2f, 0.2f);
    glPushMatrix();
    glScalef(4.0f, 1.5f, 1.5f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glColor3f(0.6f, 0.6f, 0.8f);
    glPushMatrix();
    glTranslatef(0.0f, 1.1f, 0.0f);
    glScalef(3.8f, 0.2f, 1.3f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    drawWindows();
    
    glColor3f(1.0f, 0.9f, 0.6f);
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();
}

void drawTrainConnector() {
    glColor3f(0.4f, 0.4f, 0.4f);
    glPushMatrix();
    glTranslatef(-2.2f, 0.0f, 0.0f);
    glScalef(0.4f, 0.4f, 0.4f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawAstralExpress() {
    drawTrainBody();
    
    drawWheel(-1.5f, -0.9f, -0.8f);
    drawWheel(1.5f, -0.9f, -0.8f);
    drawWheel(-1.5f, -0.9f, 0.8f);
    drawWheel(1.5f, -0.9f, 0.8f);
    
    drawTrainConnector();
}

void drawAxes() {
    if(!showAxes) return;
    
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); 
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(3.0f, 0.0f, 0.0f);
    
    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 3.0f, 0.0f);
    
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 3.0f);
    glEnd();
    glEnable(GL_LIGHTING);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    Camera cam = projectionType == 0 ? perspCameras[viewType % perspCameras.size()] : orthoCameras[viewType % orthoCameras.size()];
    
    gluLookAt(cam.eyeX, cam.eyeY, cam.eyeZ,
              cam.centerX, cam.centerY, cam.centerZ,
              cam.upX, cam.upY, cam.upZ);
    
    glRotatef(angle, 0, 1, 0);
    drawAstralExpress();
    drawAxes();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aspect = (float)w / (float)h;
    
    if(projectionType == 0) {
        gluPerspective(45.0, aspect, 0.1, 100.0);
    } else {
        if(aspect > 1) {
            glOrtho(-8.0*aspect, 8.0*aspect, -8.0, 8.0, -20.0, 20.0);
        } else {
            glOrtho(-8.0, 8.0, -8.0/aspect, 8.0/aspect, -20.0, 20.0);
        }
    }
    
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'p': projectionType = 0; break;
        case 'o': projectionType = 1; break;
        case 'v': viewType = (viewType + 1) % (projectionType ? orthoCameras.size() : perspCameras.size()); break;
        case 'r': angle += 5.0f; break;
        case 'R': angle -= 5.0f; break;
        case 'a': showAxes = !showAxes; break;
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void init() {
    initCameras();
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    GLfloat light_pos[] = {5.0f, 5.0f, 5.0f, 1.0f};
    GLfloat light_color[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Kereta");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    printf("Kontrol:\n");
    printf("o - Orthographic projection\n");
    printf("p - Perspective projection\n");
    printf("v - Ganti view type\n");
    printf("r/R - Rotasi model\n");
    printf("a - Toggle axes display\n");
    printf("ESC - Keluar\n");
    
    glutMainLoop();
    return 0;
}





