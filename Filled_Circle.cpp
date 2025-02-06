#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include<math.h>
# define PI           3.14159265358979323846

/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
void display() {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // Set background color to gray and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
	int i;

	GLfloat x=0.2f; GLfloat y=0.3f; GLfloat radius =0.2f;
	int triangleAmount = 100; //# of lines used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f( x + (radius * cos(i *  twicePi / triangleAmount)),
                        y + (radius * sin(i * twicePi / triangleAmount)) );
		}
	glEnd();

	glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
    glutInitWindowSize(400, 400);   // Set the window's initial width & height
	glutCreateWindow("Filled Circle Drawing Test"); // Create a window with the given title
    glutPositionWindow(30, 50);   // Change to the position of the current window.
	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutMainLoop();           // Enter the event-processing loop
	return 0;
}
