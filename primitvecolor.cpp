#include <GL/glut.h>

void display() {
  glClear(GL_COLOR_BUFFER_BIT);


  glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, 1.0);
    glVertex2f(0.0, -1.0);
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    glEnd();


 glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.75, 0.25);
    glVertex2f(-0.5, 0.75);
    glVertex2f(-0.25, 0.25);
    glEnd();


  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_POLYGON);
  glVertex2f(0.4f, 0.2f);
glVertex2f(0.6f, 0.2f);
glVertex2f(0.7f, 0.4f);
glVertex2f(0.6f, 0.6f);
glVertex2f(0.4f, 0.6f);
glVertex2f(0.3f, 0.4f);
  glEnd();


  glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.75, -0.25);
    glVertex2f(-0.75, -0.75);
    glVertex2f(-0.25, -0.75);
    glVertex2f(-0.25, -0.25);
    glEnd();


  glColor3f(1.0f, 0.5f, 0.0f);
  glBegin(GL_TRIANGLES);
  glVertex2f(0.50f, -0.20f);
  glVertex2f(0.35f, -0.80f);
  glVertex2f(0.60f, -0.80f);
  glEnd();

  glFlush();

}

int main(int argc, char** argv) {

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(450, 450);
   glutCreateWindow("Vertex,Primitive & color");
   glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
   gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
