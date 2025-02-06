/// Draw Sample Polygon

/*
* GL02Primitive.cpp: Vertex, Primitive and Color
* Draw Simple 2D colored Shapes: quad, triangle and polygon.
*/
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

/* Initialize OpenGL Graphics */
void initGL()
{
	// Set "clearing" or background color
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // yellow and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

	glBegin(GL_POLYGON);            // These vertices form a closed polygon
	glColor3f(0.0f, 1.0f, 1.0f); // cyan
	glVertex2f(0.4f, 0.2f);
	glVertex2f(0.6f, 0.2f);
	glVertex2f(0.7f, 0.4f);
	glVertex2f(0.6f, 0.6f);
	glVertex2f(0.4f, 0.6f);
	glVertex2f(0.3f, 0.4f);
	glEnd();

	glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);          // Initialize GLUT
	glutInitWindowSize(320, 320);   // Set the window's initial width & height
	glutInitWindowPosition(80, 50);  // Set the window's initial position according to the monitor
	glutCreateWindow("Vertex, Primitive & Color");  // Create window with the given title
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	initGL();                       // Our own OpenGL initialization
	glutMainLoop();                 // Enter the event-processing loop
	return 0;
}
