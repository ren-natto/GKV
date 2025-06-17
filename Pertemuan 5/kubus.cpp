// main.cpp
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

#include "imageloader.h"
#include "imageloader.cpp"

using namespace std;

const float BOX_SIZE = 7.0f;
float _angle = 0;

// IDs for our six textures
GLuint _textureId[6];

// Loads a texture from a file and returns its ID
GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    return textureId;
}

// Initialization
void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    // Load 6 textures
    Image* images[6];
    images[0] = loadBMP("fish.bmp");
    images[1] = loadBMP("fish.bmp");
    images[2] = loadBMP("fish.bmp");
    images[3] = loadBMP("fish.bmp");
    images[4] = loadBMP("fish.bmp");
    images[5] = loadBMP("fish.bmp");

    for (int i = 0; i < 6; i++) {
        _textureId[i] = loadTexture(images[i]);
        delete images[i];
    }
}

// Window resize handler
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

// Drawing scene
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -20.0f);
    glRotatef(-_angle, 1.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white

    // Front Face (face1.bmp)
    glBindTexture(GL_TEXTURE_2D, _textureId[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();

    // Back Face (face2.bmp)
    glBindTexture(GL_TEXTURE_2D, _textureId[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

    // Top Face (face3.bmp)
    glBindTexture(GL_TEXTURE_2D, _textureId[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

    // Bottom Face (face4.bmp)
    glBindTexture(GL_TEXTURE_2D, _textureId[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();

    // Right face (face5.bmp)
    glBindTexture(GL_TEXTURE_2D, _textureId[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();

    // Left Face (face6.bmp)
    glBindTexture(GL_TEXTURE_2D, _textureId[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

// Update for animation
void update(int value) {
    _angle += 1.0f;
    if (_angle > 360) {
        _angle -= 360;
    }
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

void handleKeypress(unsigned char key, int x, int y) {
    if (key == 27) { // Escape key
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Cube with 6 Textures");

    initRendering();

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}