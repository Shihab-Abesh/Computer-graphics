#include <GL/glut.h>
#include <cmath>


void Rectangle(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}



void Star(float cx, float cy, float outer_r, float inner_r, int num_points, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_points * 2; i++) {
        float angle = i * M_PI / num_points;
        float radius = (i % 2 == 0) ? outer_r : inner_r;
        glVertex2f(cx + radius * cos(angle), cy + radius * sin(angle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // vertical
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();

    // horizontal
    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glEnd();

    // Sudan Flag
    Rectangle(0.2f, 0.7f, 0.9f, 0.85f, 1.0f, 0.0f, 0.0f);
    Rectangle(0.2f, 0.55f, 0.9f, 0.7f, 1.0f, 1.0f, 1.0f);
    Rectangle(0.2f, 0.4f, 0.9f, 0.55f, 0.0f, 0.0f, 0.0f);
    Triangle(0.2f, 0.4f, 0.2f, 0.85f, 0.45f, 0.625f,0.0f,0.8f,0.0f);

    // Somalia Flag
    Rectangle(-0.9f, 0.4f, -0.2f, 0.9f, 0.0f, 0.5f, 1.0f);
    Star(-0.55f, 0.65f, 0.15f, 0.07f, 5, 1.0f, 1.0f, 1.0f);


    // Tonga Flag
Rectangle(-0.9f, -0.9f, -0.2f, -0.2f, 1.0f, 0.0f, 0.0f);
Rectangle(-0.9f, -0.2f, -0.55f, -0.45f, 1.0f, 1.0f, 1.0f);
Rectangle(-0.75f, -0.28f, -0.69f, -0.41f, 1.0f, 0.0f, 0.0f);
Rectangle(-0.82f, -0.32f, -0.63f, -0.37f, 1.0f, 0.0f, 0.0f);

    // Denmark Flag
Rectangle(0.2f, -0.9f, 0.9f, -0.2f, 1.0f, 0.0f, 0.0f);
Rectangle(0.2f, -0.55f, 0.9f, -0.45f, 1.0f, 1.0f, 1.0f);
Rectangle(0.45f, -0.9f, 0.55f, -0.2f, 1.0f, 1.0f, 1.0f);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("4 FLAGS");
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
