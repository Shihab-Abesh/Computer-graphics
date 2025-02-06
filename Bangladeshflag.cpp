#include <GL/glut.h>
#include <cmath>
void display() {
    glClear(GL_COLOR_BUFFER_BIT);


    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.7f, -0.5f);
    glVertex2f(0.7f, -0.5f);
    glVertex2f(0.7f, 0.5f);
    glVertex2f(-0.7f, 0.5f);
    glEnd();


    glColor3f(0.8f, 0.0f, 0.0f);
    float cx = 0.0f, cy = 0.0f;
    float radius = 0.3f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.14159f * i / 100;
        glVertex2f(cx + radius * cos(angle), cy + radius * sin(angle));
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("BANGLADESH FLAG");

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
