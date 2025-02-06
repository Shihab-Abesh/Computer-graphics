#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include<math.h>
# define PI           3.14159265358979323846
/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
void display() {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // Set background color to gray and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)

	GLfloat x = 0.2f; GLfloat y = -0.5f; GLfloat radius = 0.4f;
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

    glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) {
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)),
			    y + (radius * sin(i * twicePi / lineAmount))
			);
		}
	glEnd();

	glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
	glutInitWindowSize(320, 320);   // Set the window's initial width & height
	glutPositionWindow(100, 100);   // Change to the position of the current window.
	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutMainLoop();           // Enter the event-processing loop
	return 0;
}
