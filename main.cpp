#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <cmath>
#define PI 3.14159265358979323846
//......................Required variable for ship animation and Translation ...........................//
int currentScenario = 1;
GLfloat tx = 0.0f; // X position
GLfloat ty = 0.0f; // Y position
float yAnimate = 0.05f;
float xAnimate = 0.01f;
int ykey = 1;  // Control vertical movement
int xkey = 1;  // Control horizontal movement
bool animation=true;
bool isRunning = true;
GLfloat position = 0.0f;
GLfloat speedShip = 0.025f;
GLfloat position0 = 0.0f;
GLfloat position2 = 0.0f;
GLfloat position3 = 0.0f;

GLfloat speed = 0.1f;
bool isDay = true; // Flag to indicate day or night
bool isRed = true;

//............required function to draw ships different part......................
void drawRectangle(float centerX, float centerY, float width, float height) {
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    glBegin(GL_QUADS);

    glVertex2f(centerX - halfWidth, centerY - halfHeight); // Bottom-left corner
    glVertex2f(centerX + halfWidth, centerY - halfHeight); // Bottom-right corner
    glVertex2f(centerX + halfWidth, centerY + halfHeight); // Top-right corner
    glVertex2f(centerX - halfWidth, centerY + halfHeight); // Top-left corner

    glEnd();
}

void drawCircle(float centerX, float centerY, float radius) {
    const int segments = 100; // Number of segments to approximate the circle
    const float angleStep = 2.0f * M_PI / segments;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // Center of the circle

    for (int i = 0; i <= segments; ++i) {
        float angle = i * angleStep;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();
}
void drawCircleWithoutFill(float cx, float cy, float r ) {
    int num_segments=100;
    glBegin(GL_LINE_LOOP); // Use line loop for outline
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); // Angle
        float x = r * cosf(theta); // X coordinate
        float y = r * sinf(theta); // Y coordinate
        glVertex2f(x + cx, y + cy); // Add vertex
    }
    glEnd();
}
//''''''''''''''''''''''''''''required function  to animate ship and ship's flag and keyboard input  '''''''''''''''
void update(int value) {
    if (!isRunning)  // Stop execution if the flag is false
        return;

    position += speedShip; // Move the yacht

    // Scenario switching logic
    if (position >= 1.0f) {
        position = -1.0f; // Reset position to left side
        currentScenario++; // Move to the next scenario

        if (currentScenario > 4) {
            currentScenario = 1; // Restart at scenario 1 after scenario 4
        }
    }
	glutPostRedisplay();
	glutTimerFunc(100, update, 0);

}


void SpecialInput(int key, int x, int y)
{

switch(key)
    {
    case GLUT_KEY_UP:
    speed += 0.1f;
    break;
    case GLUT_KEY_DOWN:
    speed -= 0.1f;
    break;
    case GLUT_KEY_LEFT:
        speedShip -= 0.01f;
        break;
    case GLUT_KEY_RIGHT:
        speedShip += 0.01f;

    break;


    }
glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {


    if (key == 'd') isDay = true;
    if (key == 'n') isDay = false;
    if (key == 'w') ty += 0.05f; // Move up
    if (key == 's') ty -= 0.05f; // Move down
    if (key == 'a') tx -= 0.05f; // Move left
    if (key == 'd') tx += 0.05f; // Move right
    if (key == ' ') {
        isRunning = !isRunning; // Toggle animation state
         //isRunning = false;
            glutTimerFunc(100, update, 0);
            tx=0.0;


}
}
void Menu(int n){
  if(n==1){animation = true;}
  else if(n== 2){animation=false;}
  else if(n==4){isRunning=false;
  }
  else if(n==3)
    {if (!isRunning) {
            isRunning = true;
            glutTimerFunc(100, update, 0);
        }}
  else if(n==5)
    exit(0);
  glutPostRedisplay();
}


void Animate() {
    // Vertical animation
    if(animation)
    {


    if (ykey == 1) {
        if (yAnimate > -0.05f) {
            yAnimate -= 0.00005f;  // Increased step size for smooth animation
        } else {
            ykey = 0;  // Switch direction at -0.2
        }
    } else {
        if (yAnimate < 0.05f) {
            yAnimate += 0.00005f;
        } else {
            ykey = 1;  // Switch direction at 0.2
        }
    }

    // Horizontal animation
    if (xkey == 1) {
        if (xAnimate > -0.01f) {
            xAnimate -= 0.00005f;
        } else {
            xkey = 0;  // Switch direction at -0.1
        }
    } else {
        if (xAnimate < 0.01f) {
            xAnimate += 0.00005f;
        } else {
            xkey = 1;  // Switch direction at 0.1
        }
    }
    }
    glutPostRedisplay(); // Request redraw

}
//''''''''''''''''''''''function  to draw flag'''''''''''''''''''''
//start senario 1

void drawFlag() {
    float bx[200], by1[200], by2[200], t;
    int i;

    float x[4] = {0.625f-xAnimate, 0.675f, 0.675f, 0.75f };  // Control points (x-coordinates)
    float y1[4] = {0.325f, 0.325f + yAnimate, 0.325f - yAnimate, 0.325f};
    float y2[4] = {0.2f, 0.2f + yAnimate, 0.2f - yAnimate, 0.2f};  // Control points (y-coordinates)

    for (i = 0, t = 0.0f; i < 200; i++, t += 0.005f) {  // Corrected loop condition
        float u = 1 - t;

        bx[i] = u * u * u * x[0] + 3 * u * u * t * x[1] + 3 * u * t * t * x[2] + t * t * t * x[3];
        by1[i] = u * u * u * y1[0] + 3 * u * u * t * y1[1] + 3 * u * t * t * y1[2] + t * t * t * y1[3];
        by2[i] = u * u * u * y2[0] + 3 * u * u * t * y2[1] + 3 * u * t * t * y2[2] + t * t * t * y2[3];
    }

    glColor3f(0.122, 0.388, 0.063);  // Set color to red
    glLineWidth(2.0f);

    // Draw the flag shape
    glBegin(GL_QUAD_STRIP);  // Use lines instead of points for a smooth flag
    for (i = 0; i < 200; i++) {
        glVertex2f(bx[i], by1[i]);
        glVertex2f(bx[i], by2[i]);
    }
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    drawCircle(bx[110],(by1[110]+by2[110])/2.0,0.035f);

    glColor3f(0.792, 0.839, 0.851);
   drawRectangle(0.75,0.2,0.008,0.28);

glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f); // Set outline thickness
    glColor3f(0.0f, 0.0f, 0.0f); //black color
    drawRectangle(0.75,0.2,0.008,0.28);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



// Function to draw the deck
void drawDeck() {
    //ship Hull
    glColor3f(0.1f, 0.1f, 0.5f); // Darker blue color
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f, -0.25f);
        glVertex2f(0.5f, -0.25f);
        glVertex2f(0.65f, -0.1f);
        glVertex2f(-0.8f, -0.1f);
       glEnd();
   //dwaw black out line
     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f); // Set outline thickness
    glColor3f(0.0f, 0.0f, 0.0f); // White color
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f, -0.25f);
        glVertex2f(0.5f, -0.25f);
        glVertex2f(0.65f, -0.1f);
        glVertex2f(-0.8f, -0.1f);
    glEnd();
 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


     //ships first flor
        glBegin(GL_POLYGON);
        glColor3f(0.6f, 0.0f, 0.6f);
        glVertex2f(-0.45f, -0.1f);
        glVertex2f(0.65f, -0.1f);
        glVertex2f(0.450f, 0.125f);
        glVertex2f(-0.35f, 0.125);
        glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f); // Set outline thickness
    glColor3f(0.0f, 0.0f, 0.0f); // black color
    glBegin(GL_POLYGON);
        glVertex2f(-0.45f, -0.1f);
        glVertex2f(0.65f, -0.1f);
        glVertex2f(0.450f, 0.125f);
        glVertex2f(-0.35f, 0.125);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //first flor black windrow
        glColor3f(0.0f, 0.0f, 0.0f);
        drawRectangle(0.1f, 0.058f, 0.7f, 0.09f);//first flor black windrow
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(3.0f); // Set outline thickness
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    drawRectangle(0.1f, 0.058f, 0.7f, 0.09f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glColor3f(1.0f, 1.0f, 1.0f); // White color
    drawRectangle(0.1f, 0.06f, 0.01f, 0.08f);
    drawRectangle(0.15f, 0.06f, 0.01f, 0.08f);
    drawRectangle(-0.2f, 0.06f, 0.01f, 0.08f);
    drawRectangle(0.2f, 0.06f, 0.01f, 0.08f);

  //second deck
    glColor3f(0.6f, 0.6f, 0.6f); // Metallic gray color
    glBegin(GL_POLYGON);
        glVertex2f(-0.65f, -0.1f);
        glVertex2f(0.65f, -0.1f);
        glVertex2f(0.85f, 0.065f);
        glVertex2f(0.3f, 0.065f);
        glVertex2f(0.25f, 0.02f);
        glVertex2f(-0.65f, 0.02f);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f); // Set outline thickness
    glColor3f(0.0f, 0.0f, 0.0f); //black color
    glBegin(GL_POLYGON);
        glVertex2f(-0.65f, -0.1f);
        glVertex2f(0.65f, -0.1f);
        glVertex2f(0.85f, 0.065f);
        glVertex2f(0.3f, 0.065f);
        glVertex2f(0.25f, 0.02f);
        glVertex2f(-0.65f, 0.02f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

// first deck
    glColor3f(0.1f, 0.6f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.65f, -0.1f);
        glVertex2f(0.65f, -0.1f);
        glVertex2f(0.8f, 0.02f);
        glVertex2f(0.3f, 0.02f);
        glVertex2f(0.25f, -0.025f);
        glVertex2f(-0.65f, -0.025f);
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f); // Set outline thickness
    glColor3f(0.0f, 0.0f, 0.0f); //black color
    glBegin(GL_POLYGON);
        glVertex2f(-0.65f, -0.1f);
        glVertex2f(0.65f, -0.1f);
        glVertex2f(0.8f, 0.02f);
        glVertex2f(0.3f, 0.02f);
        glVertex2f(0.25f, -0.025f);
        glVertex2f(-0.65f, -0.025f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
// first deck windows
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.4f, -0.06f, 0.025f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.3f, -0.06f, 0.025f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.5f, -0.06f, 0.025f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.2f, -0.06f, 0.025f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.3f, -0.06f, 0.025f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.5f, -0.06f, 0.025f);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(3.0f); // Set outline thickness
    glColor3f(1.0f, 0.0f, 0.0f); //red color
    drawCircleWithoutFill(0.5f, -0.06f, 0.025f);
    drawCircleWithoutFill(0.3f, -0.06f, 0.025f);
    drawCircleWithoutFill(-0.2f, -0.06f, 0.025f);
    drawCircleWithoutFill(-0.5f, -0.06f, 0.025f);
    drawCircleWithoutFill(-0.3f, -0.06f, 0.025f);
    drawCircleWithoutFill(-0.4f, -0.06f, 0.025f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    glColor3f(0.208, 0.718, 0.878);
    drawRectangle(0.04f, -0.06f, 0.3f, 0.025f);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f); // Set outline thickness
    glColor3f(1.0f, 1.0f, 1.0f); //black color
    drawRectangle(0.04f, -0.06f, 0.3f, 0.025f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

// Function to draw the sail
void drawSail() {
    //sail deck
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.55f, 0.125f);
        glVertex2f(0.35f, 0.125f);
        glVertex2f(0.3f, 0.15f);
        glVertex2f(-0.5f, 0.15);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f); // Set outline thickness
    glColor3f(0.0f, 0.0f, 0.0f); //black color
    glBegin(GL_POLYGON);
        glVertex2f(-0.55f, 0.125f);
        glVertex2f(0.35f, 0.125f);
        glVertex2f(0.3f, 0.15f);
        glVertex2f(-0.5f, 0.15);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

//ship second floor
    glColor3f(0.9f, 0.8f, 0.95f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, 0.225f);
        glVertex2f(-0.4f, 0.2f);
        glVertex2f(-0.2f, 0.2);
        glVertex2f(-0.2f, 0.15f);
        glVertex2f(0.3f, 0.15f);
         glVertex2f(0.2f, 0.225f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f); // Set outline thickness
    glColor3f(0.0f, 0.0f, 0.0f); //black color
    glBegin(GL_POLYGON);
       glVertex2f(-0.4f, 0.225f);
        glVertex2f(-0.4f, 0.2f);
        glVertex2f(-0.2f, 0.2);
        glVertex2f(-0.2f, 0.15f);
        glVertex2f(0.3f, 0.15f);
         glVertex2f(0.2f, 0.225f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
// second floor windows
     glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(0.1f, 0.215f);
        glVertex2f(0.21f, 0.215f);
        glVertex2f(0.29f, 0.16);
        glVertex2f(0.1f, 0.16f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.1f, 0.1875f, 0.0275f);

    glColor3f(0.0, 0.0, 0.0);
    drawRectangle(-0.08f, 0.1875f, 0.225f, 0.05f);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(3.0f); // Set outline thickness
    glColor3f(1.0f, 1.0f, 1.0f); //black color
     drawRectangle(-0.08f, 0.1875f, 0.225f, 0.05f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


//third floor
      glColor3f(0.9f, 0.9f, 0.9f);
        glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.225f);
        glVertex2f(0.2f, 0.225f);
        glVertex2f(0.12f, 0.3);
        glVertex2f(0.0f, 0.3f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f); // Set outline thickness
    glColor3f(0.0f, 0.0f, 0.0f); //black color
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.225f);
        glVertex2f(0.2f, 0.225f);
        glVertex2f(0.12f, 0.3);
        glVertex2f(0.0f, 0.3f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
 // third floor windows
     glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
       glVertex2f(0.05f, 0.235f);
        glVertex2f(0.19f, 0.235f);
        glVertex2f(0.13f, 0.29);
        glVertex2f(0.05f, 0.29f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.05f, 0.2625f, 0.0275f);

//ship rudder
    glColor3f(0.9f, 0.9f, 0.9f);
        glBegin(GL_POLYGON);
        glVertex2f(-0.25f, 0.225f);
        glVertex2f(-0.15f, 0.225f);
        glVertex2f(-0.2f, 0.35);
        glVertex2f(-0.25f, 0.35f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f); // Set outline thickness
    glColor3f(0.0f, 0.0f, 0.0f); //black color
    glBegin(GL_POLYGON);
        glVertex2f(-0.25f, 0.225f);
        glVertex2f(-0.15f, 0.225f);
        glVertex2f(-0.2f, 0.35);
        glVertex2f(-0.25f, 0.35f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

// rudder designs
    glColor3f(0.0f, 0.0f, 1.0f);
    drawRectangle(-0.215,0.3,0.07,0.01);
      glColor3f(0.0f, 0.0f, 1.0f);
    drawRectangle(-0.22,0.325,0.06,0.01);


//frence
     glColor3f(0.412, 0.549, 0.722);
     drawRectangle(-0.3,0.175,0.4,0.007);
     drawRectangle(-0.5,0.165,0.007,0.03);
     drawRectangle(-0.45,0.165,0.007,0.03);
     drawRectangle(-0.4,0.165,0.007,0.03);
     drawRectangle(-0.35,0.165,0.007,0.03);
     drawRectangle(-0.3,0.165,0.007,0.03);
     drawRectangle(-0.25,0.165,0.007,0.03);
     drawRectangle(-0.2,0.165,0.007,0.03);
     drawRectangle(-0.15,0.165,0.007,0.03);
     drawRectangle(-0.1,0.165,0.007,0.03);

// antenna platform
   glColor3f(0.9f, 0.9f, 0.9f);
        glBegin(GL_POLYGON);
        glVertex2f(0.02f, 0.3f);
        glVertex2f(0.085f, 0.3f);
        glVertex2f(0.0625f, 0.35f);
        glVertex2f(0.03f, 0.35f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f); // Set outline thickness
    glColor3f(0.0f, 0.0f, 0.0f); //black color
        glBegin(GL_POLYGON);
        glVertex2f(0.02f, 0.3);
        glVertex2f(0.085f, 0.3f);
        glVertex2f(0.0625f, 0.35);
        glVertex2f(0.03f, 0.35f);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
 // antenna
    glColor3f(0.412, 0.549, 0.722);
     drawRectangle(0.04625,0.425,0.008,0.15);
     drawRectangle(0.04625,0.435,0.06,0.008);
     drawRectangle(0.04625,0.455,0.07,0.008);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(1.0f); // Set outline thickness
    glColor3f(0.0f, 0.0f, 0.0f); //black color
    drawRectangle(0.04625,0.425,0.008,0.15);
     drawRectangle(0.04625,0.435,0.06,0.008);
     drawRectangle(0.04625,0.455,0.07,0.008);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}


void drawYacht(float scaleX,float scaleY,float translateX,float translatefY)
{   glPushMatrix();
        glTranslatef(translateX, translatefY, 0.0f);



    glPushMatrix();        // Save current state
    glScalef(scaleX, scaleY, 0.0f);
    drawFlag();  // Scale 2x on X and Y axes
    drawDeck();
    drawSail();
    drawFlag();
    glEnd();

     glPopMatrix();
     glPopMatrix();      // Restore state

}
//'''''''''''''''senario2'''''''''''''
// Flag to toggle circle color

//watchtowerlighttoggle
void toggleCircleColor(int value) {
    isRed = !isRed; // Toggle the color flag
    glutPostRedisplay();
    glutTimerFunc(500, toggleCircleColor, 0); // Set next toggle
}



//planeupdte
void updateP(int value) {
if(position0 >=  1.0) // kondike jabe
        position0 = -1.f;
    position0 += speed;
	glutPostRedisplay();
	glutTimerFunc(200, updateP, 0); // speed
}



//cloudupdte
void updateC(int value) {
if(position2 >=  1.0) // kondike jabe
        position2 = -1.0f;
    position2 += speed;
	glutPostRedisplay();
	glutTimerFunc(500, updateC, 0); // speed
}

//float  tx = 10, bx = 10, rx = 10, sx = 10, hx = 0;


void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

void Bushes()
{
     // lowright Bushes
    glColor3f(0.13f, 0.55f, 0.13f);
    circle(0.1f, 0.35f, 0.95f, -0.98f);
    glColor3f(0.13f, 0.55f, 0.13f);
    circle(0.2f, 0.1f, 0.85f, -0.9f);

    glColor3f(0.13f, 0.55f, 0.13f);
    circle(0.15f, 0.1f, 0.8f, -0.8f);

    // lowleft Bushes
    glColor3f(0.13f, 0.55f, 0.13f);
    circle(0.1f, 0.35f, -0.95f, -0.98f);
    glColor3f(0.13f, 0.55f, 0.13f);
    circle(0.2f, 0.1f, -0.85f, -0.9f);

    glColor3f(0.13f, 0.55f, 0.13f);
    circle(0.15f, 0.1f, 0.8f, -0.8f);

    //treebushR
    glColor3f(0.13f, 0.55f, 0.13f);
    circle(0.1f, 0.1f, 0.8f, -0.48f);
    glColor3f(0.13f, 0.55f, 0.13f);
    circle(0.15f, 0.1f, 0.7f, -0.48f);
    glColor3f(0.13f, 0.55f, 0.13f);
    circle(0.11f, 0.1f, 0.8f, -0.4f);
    glColor3f(0.13f, 0.55f, 0.13f);
    circle(0.1f, 0.1f, 0.9f, -0.56f);


    //treebushL
    glColor3f(0.13f, 0.55f, 0.13f);
    circle(0.1f, 0.1f, -0.8f, -0.48f);
    glColor3f(0.13f, 0.55f, 0.13f);
    circle(0.15f, 0.1f, -0.7f, -0.48f);
    glColor3f(0.13f, 0.55f, 0.13f);
    circle(0.11f, 0.1f, -0.8f, -0.4f);
    glColor3f(0.13f, 0.55f, 0.13f);
    circle(0.1f, 0.1f, -0.9f, -0.56f);





}


void scenario1() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
    glShadeModel(GL_SMOOTH); // Enable smooth shading


    // BEACH
   glColor3f(0.75f, 0.74f, 0.48f);
    glBegin(GL_POLYGON);


    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.7f);
    glVertex2f(-1.0f, -0.5f);
    glEnd();


    //SKY
   glBegin(GL_TRIANGLE_STRIP);
    if (isDay) {
        // Top (Bright Blue)
        glColor3f(0.53f, 0.81f, 0.98f);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);

        // Middle-High (Sky Blue)
        glColor3f(0.3f, 0.6f, 1.0f);
        glVertex2f(-1.0f, 0.6f);
        glVertex2f(1.0f, 0.6f);

        // Middle-Low (Soft Blue)
        glColor3f(0.5f, 0.5f, 0.8f);
        glVertex2f(-1.0f, 0.3f);
        glVertex2f(1.0f, 0.3f);

        // Bottom (Reddish Horizon Effect)
        glColor3f(0.9f, 0.3f, 0.2f);
        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
    }
    else {
         // Top (deep Blue)
        glColor3f(0.1f, 0.1f, 0.3f);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);

        // Middle-High (dark purple)
        glColor3f(0.3f, 0.0f, 0.3f);
        glVertex2f(-1.0f, 0.6f);
        glVertex2f(1.0f, 0.6f);

        // Middle-Low (dark grey)
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex2f(-1.0f, 0.3f);
        glVertex2f(1.0f, 0.3f);

        // Bottom (dark black)
        glColor3f(0.0f, 0.0f, 0.f);
        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
    }

    glEnd();



    //SUN
if (isDay) {
    glColor3f(1.0f, 0.5f, 0.0f);
    circle(0.07f, 0.12f, 0.78f, 0.78f);
    }

// Moon
    if (!isDay) {
        glColor3f(1.0f, 1.0f, 1.0f);
        circle(0.07f, 0.12f, 0.78f, 0.78f);
    }

    glutSwapBuffers(); // Double buffering for smoother animation



    //CLOUD
    glPushMatrix();
    glTranslatef(position2, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    circle(0.12f, 0.08f, 0.0f, 0.68f);
    circle(0.07f, 0.11f, 0.0f, 0.75f);
    circle(0.12f, 0.08f, 0.4f, 0.5f);
    circle(0.07f, 0.11f, 0.4f, 0.57f);
    glPopMatrix();
    glEnd();



    //SEA
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.75f);  //light teal blue
    glVertex2f(-1.0f, 0.5f);
    glColor3f(0.0f, 0.2f, 0.3f);  //dark blue green
    glVertex2f(-1.0f, -0.5f);
    glColor3f(0.0f, 0.2f, 0.3f);   //dark blue green
    glVertex2f(1.0f, -0.7f);
    glColor3f(0.0f, 0.5f, 0.75f);  //medium teal blue
    glVertex2f(1.0f, 0.2f);
    glEnd();




    //backscene

    glColor3f(0.5f, 0.5f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 0.5f);
    glVertex2f(-1.0f, 0.2f);
    glVertex2f(1.0f, 0.2f);
    glEnd();

//mountain
    glColor3f(0.36f, 0.25f, 0.20f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 0.2f);
    glVertex2f(-0.8f, 0.45f);
    glVertex2f(-0.6f, 0.2f);
    glEnd();

    glColor3f(0.68f, 0.85f, 0.90f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.88f, 0.35f);
    glVertex2f(-0.8f, 0.45f);
    glVertex2f(-0.72f, 0.35f);
    glEnd();
    glColor3f(0.68f, 0.85f, 0.90f);
    /*circle(0.03f, 0.028f, -0.8f, 0.415f);
    glEnd();

     glColor3f(0.68f, 0.85f, 0.90f);*/
    glBegin(GL_POLYGON);
    glVertex2f(-0.67f, 0.275f);
    glVertex2f(-0.6f, 0.2f);
    glVertex2f(-0.54f, 0.2f);
    glVertex2f(-0.58f, 0.4f);
    glVertex2f(-0.4f, 0.2f);
    glEnd();
   /* glColor3f(0.68f, 0.85f, 0.90f);
    circle(0.03f, 0.028f, -0.58f, 0.37f);
    glEnd();*/

    glColor3f(0.65f, 0.50f, 0.39f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6f, 0.2f);
    glVertex2f(-0.3f, 0.4f);
    glVertex2f(-0.1f, 0.2f);
    glEnd();
    /*glColor3f(0.65f, 0.50f, 0.39f);
    circle(0.03f, 0.028f, -0.31f, 0.379f);
    glEnd();*/

    glColor3f(0.68f, 0.85f, 0.90f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, 0.2f);
    glVertex2f(-0.1f, 0.4f);
    glVertex2f(0.1f, 0.2f);
    glEnd();

    glColor3f(0.36f, 0.25f, 0.20f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.2f);
    glVertex2f(0.2f, 0.3f);
    glVertex2f(0.6f, 0.2f);
    glEnd();




//UMBRELLA line
    glLineWidth(5);
	// Draw a Red 1x1 Square centered at origin
	glBegin(GL_LINES);              // Each set of 4 vertices form a quad
	glColor3f(0.3f, 0.3f, 0.3f); // Red
	glVertex2f(0.2f, -0.9f);    // x, y
	glVertex2f(0.2f, -0.7f);
	glVertex2f(0.6f, -0.9f);    // x, y
	glVertex2f(0.6f, -0.7f);

	glEnd();



	//umbrella1st
	glColor3f(0.5f, 0.0f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(0.2f, -0.6f);
    glVertex2f(0.05f, -0.7f);
    glVertex2f(0.35f, -0.7f);
    glEnd();




    //umbrella2nd
	glColor3f(0.5f, 0.0f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(0.6f, -0.6f);
    glVertex2f(0.45f, -0.7f);
    glVertex2f(0.75f, -0.7f);
    glEnd();



    Bushes();


    //grassbottomright
   //1
    glColor3f(0.60, 0.80f, 0.50f);
    glBegin(GL_POLYGON);
    glVertex2f(0.8f, -1.0f);
    glVertex2f(0.7f, -0.87f);
    glVertex2f(0.82f, -1.0f);
//2
    glColor3f(0.60, 0.80f, 0.50f);
    glBegin(GL_POLYGON);
    glVertex2f(0.8f, -1.0f);
    glVertex2f(0.75f, -0.84f);
    glVertex2f(0.82f, -1.0f);
    //3
    glColor3f(0.60, 0.80f, 0.50f);
    glBegin(GL_POLYGON);
    glVertex2f(0.8f, -1.0f);
    glVertex2f(0.73f, -0.7f);
    glVertex2f(0.82f, -1.0f);
    //4
    glColor3f(0.60, 0.80f, 0.50f);
    glBegin(GL_POLYGON);
    glVertex2f(0.8f, -1.0f);
    glVertex2f(0.8f, -0.84f);
    glVertex2f(0.82f, -1.0f);
    //5
    glColor3f(0.60, 0.80f, 0.50f);
    glBegin(GL_POLYGON);
    glVertex2f(0.8f, -1.0f);
    glVertex2f(0.7f, -0.87f);
    glVertex2f(0.82f, -1.0f);
    //6
    glColor3f(0.60, 0.80f, 0.50f);
    glBegin(GL_POLYGON);
    glVertex2f(0.82f, -1.0f);
    glVertex2f(0.88f, -0.7f);
    glVertex2f(0.83f, -1.0f);



    glEnd();




    //grassbottomLEFT
   //1
    glColor3f(0.60, 0.80f, 0.50f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8f, -1.0f);
    glVertex2f(-0.7f, -0.87f);
    glVertex2f(-0.82f, -1.0f);
//2
    glColor3f(0.60, 0.80f, 0.50f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8f, -1.0f);
    glVertex2f(-0.75f, -0.84f);
    glVertex2f(-0.82f, -1.0f);
    //3
    glColor3f(0.60, 0.80f, 0.50f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8f, -1.0f);
    glVertex2f(-0.73f, -0.7f);
    glVertex2f(-0.82f, -1.0f);
    //4
    glColor3f(0.60, 0.80f, 0.50f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8f, -1.0f);
    glVertex2f(-0.8f, -0.84f);
    glVertex2f(-0.82f, -1.0f);
    //5
    glColor3f(0.60, 0.80f, 0.50f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8f, -1.0f);
    glVertex2f(-0.7f, -0.87f);
    glVertex2f(-0.82f, -1.0f);
    //6
    glColor3f(0.60, 0.80f, 0.50f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.82f, -1.0f);
    glVertex2f(-0.88f, -0.7f);
    glVertex2f(-0.83f, -1.0f);




    glEnd();

//righttreemain
    glColor3f(0.65, 0.16f, 0.16f);
    glBegin(GL_POLYGON);
    glVertex2f(0.8f, -1.0f);
    glVertex2f(0.8f, -0.5f);
    glVertex2f(0.83f, -0.5f);
    glVertex2f(0.82f, -1.0f);

     glEnd();



    //righttreemainR
    glColor3f(0.65, 0.16f, 0.16f);
    glBegin(GL_POLYGON);
    glVertex2f(0.82f, -0.62f);
    glVertex2f(0.82f, -0.66f);
    glVertex2f(0.9f, -0.54f);
    glVertex2f(0.92f, -0.58f);

     glEnd();



    //lefttreemain
    glColor3f(0.65, 0.16f, 0.16f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8f, -1.0f);
    glVertex2f(-0.8f, -0.5f);
    glVertex2f(-0.83f, -0.5f);
    glVertex2f(-0.82f, -1.0f);

     glEnd();



    //lefttreemainL
    glColor3f(0.65, 0.16f, 0.16f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.82f, -0.62f);
    glVertex2f(-0.82f, -0.66f);
    glVertex2f(-0.9f, -0.54f);
    glVertex2f(-0.92f, -0.58f);

     glEnd();


    //lefttreemainR
    glColor3f(0.65, 0.16f, 0.16f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8f, -0.6f);
    glVertex2f(-0.8f, -0.625f);
    glVertex2f(-0.72f, -0.525f);
    glVertex2f(-0.72f, -0.575f);

     glEnd();


    //planeface

    glPushMatrix();
       glTranslatef(position0, 0.0f, 0.0f);
    glColor3f(1.0f, 0.36f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, 0.7f);
    glVertex2f(-0.5f, 0.75f);
    glVertex2f(-0.5f, 0.65f);

     glEnd();
     glPopMatrix();

//planebody

glPushMatrix();
       glTranslatef(position0, 0.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, 0.75f);
    glVertex2f(-0.8f, 0.75f);
    glVertex2f(-0.5f, 0.65f);
    glVertex2f(-0.7f, 0.65f);
    glVertex2f(-0.8f, 0.7f);
    glVertex2f(-0.8f, 0.75f);

     glEnd();
     glPopMatrix();


    //planewingsLEFT

    glPushMatrix();
       glTranslatef(position0, 0.0f, 0.0f);

     glColor3f(0.08f, 0.39f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.54f, 0.75f);
    glVertex2f(-0.64f, 0.75f);
    glVertex2f(-0.68f, 0.825f);
    glVertex2f(-0.64f, 0.85f);

    glEnd();
    glPopMatrix();


    //planewingsRIGHT

    glPushMatrix();
       glTranslatef(position0, 0.0f, 0.0f);

    glColor3f(0.08f, 0.39f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.62f, 0.65f);
    glVertex2f(-0.54f, 0.65f);
    glVertex2f(-0.62f, 0.575f);
    glVertex2f(-0.7f, 0.575f);

    glEnd();
    glPopMatrix();


    //planewingsUPPER

    glPushMatrix();
       glTranslatef(position0, 0.0f, 0.0f);

    glColor3f(0.08f, 0.39f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8f, 0.75f);
    glVertex2f(-0.8f, 0.9f);
    glVertex2f(-0.72f, 0.75f);


    glEnd();
    glPopMatrix();


    //planewingsWINDOW

    glPushMatrix();
       glTranslatef(position0, 0.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    circle(0.02f, 0.02f, -0.53f, 0.715f);
    circle(0.02f, 0.02f, -0.59f, 0.715f);
    circle(0.02f, 0.02f, -0.65f, 0.715f);
    circle(0.02f, 0.02f, -0.7f, 0.715f);


    glEnd();
    glPopMatrix();




    //watchhouse

    glColor3f(0.80f, 0.25f, 0.33f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6f, -0.9f);
    glVertex2f(-0.6f, -0.4f);
    //glVertex2f(-0.55f, -0.7f);
    glVertex2f(-0.5f, -0.4f);
    glVertex2f(-0.5f, -0.9f);
    glEnd();
     //uppertriangle
    glColor3f(0.00f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6f, -0.4f);
    glVertex2f(-0.5f, -0.4f);
    glVertex2f(-0.55f, -0.35f);
    glEnd();


    //watchhouseupperline
    glLineWidth(2);
	// Draw a Red 1x1 Square centered at origin
	glBegin(GL_LINES);              // Each set of 4 vertices form a quad
	glColor3f(0.0f, 0.0f, 0.0f); // Red
	glVertex2f(-0.55f, -0.4f);
	glVertex2f(-0.55f, -0.1f);
    glEnd();


    glPushMatrix();
    glTranslatef(position3, 0.0f, 0.0f);

    if (isRed) {
        glColor3f(1.0f, 0.0f, 0.0f); //red
    } else {
        glColor3f(0.0f, 1.0f, 0.0f); //green
    }
    circle(0.02f, 0.02f, -0.55f, -0.1f);
    glPopMatrix();
     // Double buffering for smoother animation
    glEnd();
    glutSwapBuffers();







}
//'''''''''''''senario 2''''''''''
bool isNight = false; // Track day/night mode



// Cloud Animation
float cloudinitial = 0.0f;
void updateClouds(int value) {
    cloudinitial -= 0.01f;
    if (cloudinitial < -1.5f) {
        cloudinitial = 1.5f;
    }
    glutPostRedisplay();
    glutTimerFunc(100, updateClouds, 0);
}

// Draw Sun
void drawSun() {
    if (isNight) return; // Hide the sun at night

    float x = 0.7f, y = 0.67f, radius = 0.14f;
    int triangleAmount = 50;
    float twicePi = 2.0f * 3.14159265359f;

    glColor3f(1.0f, 0.9f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

// Draw Moon
void drawMoon() {
    if (!isNight) return; // Hide the moon during the day

    float x = 0.7f, y = 0.67f, radius = 0.14f;
    int triangleAmount = 50;
    float twicePi = 2.0f * 3.14159265359f;

    glColor3f(0.9f, 0.9f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

// Draw Clouds
void drawCloud(float x, float y, float baseRadius) {
    int triangleAmount = 50;
    float twicePi = 2.0f * 3.14159265359f;

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (baseRadius * cos(i * twicePi / triangleAmount)),
            y + (baseRadius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void drawClouds() {
    drawCloud(-0.43f + cloudinitial, 0.78f, 0.056f);
    drawCloud(-0.35f + cloudinitial, 0.83f, 0.056f);
    drawCloud(-0.27f + cloudinitial, 0.78f, 0.056f);
    drawCloud(0.43f + cloudinitial, 0.89f, 0.056f);
    drawCloud(0.51f + cloudinitial, 0.94f, 0.056f);
    drawCloud(0.59f + cloudinitial, 0.89f, 0.056f);

    drawCloud(-0.8f + cloudinitial, 0.85f, 0.06f);
    drawCloud(-0.72f + cloudinitial, 0.9f, 0.06f);
    drawCloud(-0.64f + cloudinitial, 0.85f, 0.06f);
    drawCloud(0.0f + cloudinitial, 0.8f, 0.065f);
    drawCloud(0.08f + cloudinitial, 0.85f, 0.065f);
    drawCloud(-0.08f + cloudinitial, 0.8f, 0.065f);
    drawCloud(0.85f + cloudinitial, 0.8f, 0.06f);
    drawCloud(0.93f + cloudinitial, 0.85f, 0.065f);
    drawCloud(0.98f + cloudinitial, 0.8f, 0.065f);
}

// Draw Sea
void drawSea() {
    if (isNight) {
        glColor3f(0.0f, 0.1f, 0.3f); // Darker sea at night
    } else {
        glColor3f(0.0f, 0.4f, 0.8f);
    }
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f);
    glEnd();
}

// Mouse Click Event
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int width = glutGet(GLUT_WINDOW_WIDTH);
        int height = glutGet(GLUT_WINDOW_HEIGHT);

        float glX = (float)x / (width / 2.0f) - 1.0f;
        float glY = 1.0f - (float)y / (height / 2.0f);

        float sunX = 0.7f, sunY = 0.67f, radius = 0.14f;

        float dist = sqrt(pow(glX - sunX, 2) + pow(glY - sunY, 2));
        if (dist <= radius) {
            isNight = !isNight;
            glClearColor(isNight ? 0.0f : 0.6f, isNight ? 0.0f : 0.9f, isNight ? 0.2f : 1.0f, 1.0f);
            glutPostRedisplay();
        }
    }
}

// Draw Mountains
void drawMountains() {
    if (isNight) {
        glColor3f(0.2f, 0.2f, 0.3f); // Darker mountains at night
    } else {
        glColor3f(0.0f, 0.39f, 0.0f);
    }

    glBegin(GL_TRIANGLES);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(0.0f, 0.0f);

    glVertex2f(-0.3f, 0.0f);
    glVertex2f(0.3f, 0.6f);
    glVertex2f(0.8f, 0.0f);

    glVertex2f(0.2f, 0.0f);
    glVertex2f(0.7f, 0.4f);
    glVertex2f(1.2f, 0.0f);
    glEnd();
}

void drawScenario2()
{

    drawSun();
    drawMoon();
    drawSea();
    drawClouds();
    drawMountains();


}

//'''''''senario3''''''
//Cloud Animation
float cloudinitial3 = 0.0f;
void updateClouds3(int value) {
    cloudinitial3 -= 0.01f;
    if (cloudinitial3 < -1.5f) {
        cloudinitial3 = 1.5f;
    }

    glutPostRedisplay();
    glutTimerFunc(100, updateClouds3, 0);
}

void drawSun3() {
    float x = 0.0f, y = 0.67f, radius = 0.14f;
    int triangleAmount = 50;
    float twicePi = 2.0f * 3.14159265359f;

    glColor3f(1.0f, 0.9f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

// Draw Moon
void drawMoon3() {
    if (!isNight) return; // Hide the moon during the day

    float x = 0.0f, y = 0.67f, radius = 0.14f;
    int triangleAmount = 50;
    float twicePi = 2.0f * 3.14159265359f;

    glColor3f(0.9f, 0.9f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void drawCloud3(float x, float y, float baseRadius) {
    int triangleAmount = 50;
    float twicePi = 2.0f * 3.14159265359f;

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (baseRadius * cos(i * twicePi / triangleAmount)),
            y + (baseRadius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void drawClouds3() {
    drawCloud3(-0.43f + cloudinitial, 0.78f, 0.056f);
    drawCloud3(-0.35f + cloudinitial, 0.83f, 0.056f);
    drawCloud3(-0.27f + cloudinitial, 0.78f, 0.056f);
    drawCloud3(0.43f + cloudinitial, 0.89f, 0.056f);
    drawCloud3(0.51f + cloudinitial, 0.94f, 0.056f);
    drawCloud3(0.59f + cloudinitial, 0.89f, 0.056f);
}

void drawSea3() {
    glColor3f(0.0f, 0.4f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f);
    glEnd();
}

void drawLand3() {
    glColor3f(0.5f, 0.35f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 0.07f);
    glVertex2f(-1.0f, 0.07f);
    glEnd();
}

void drawTree(float x, float y) {
    // Tree trunk (brown rectangle)
    glColor3f(0.6f, 0.3f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.02f, y);
    glVertex2f(x + 0.02f, y);
    glVertex2f(x + 0.02f, y + 0.2f);
    glVertex2f(x - 0.02f, y + 0.2f);
    glEnd();

    // Tree leaves (green circle)
    int triangleAmount = 50;
    float radius = 0.08f;
    float twicePi = 2.0f * 3.14159265359f;
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y + 0.2f);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + 0.2f + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void drawBuilding3(float x, float y, float width, float height, float r, float g, float b) {
    // Draw building
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

   // Draw windows on the building
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for windows
    float windowWidth = width / 4.0f;
    float windowHeight = height / 6.0f;
    for (float i = x + 0.05f; i < x + width; i += windowWidth + 0.05f) {
        for (float j = y + 0.05f; j < y + height; j += windowHeight + 0.05f) {
            glBegin(GL_QUADS);
            glVertex2f(i, j);
            glVertex2f(i + windowWidth, j);
            glVertex2f(i + windowWidth, j + windowHeight);
            glVertex2f(i, j + windowHeight);
            glEnd();


        }
    }


    // Draw outline of the building
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void drawBuildings3() {
    drawBuilding3(-0.8f, 0.07f, 0.2f, 0.4f, 0.8f, 0.1f, 0.1f); // Red
    drawBuilding3(-0.5f, 0.07f, 0.2f, 0.6f, 0.1f, 0.6f, 0.1f); // Green
    drawBuilding3(-0.2f, 0.07f, 0.2f, 0.35f, 0.1f, 0.1f, 0.8f); // Blue
    drawBuilding3(0.1f, 0.07f, 0.2f, 0.6f, 0.9f, 0.6f, 0.1f); // Yellow
    drawBuilding3(0.4f, 0.07f, 0.2f, 0.6f, 0.6f, 0.1f, 0.6f); // Purple
    drawBuilding3(0.7f, 0.07f, 0.2f, 0.4f, 0.3f, 0.3f, 0.3f); // Gray

    // Add trees beside buildings
    drawTree(-0.9f, 0.07f); // Tree beside red building
    drawTree(-0.55f, 0.07f); // Tree beside green building
    drawTree(-0.2f, 0.07f); // Tree beside blue building
    drawTree(0.35f, 0.07f); // Tree beside yellow building
    drawTree(0.65f, 0.07f); // Tree beside purple building
    drawTree(0.9f, 0.07f); // Tree beside gray building
}

// Mouse Click Event
void mouseClick3(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int width = glutGet(GLUT_WINDOW_WIDTH);
        int height = glutGet(GLUT_WINDOW_HEIGHT);

        float glX = (float)x / (width / 2.0f) - 1.0f;
        float glY = 1.0f - (float)y / (height / 2.0f);

        float sunX = 0.0f, sunY = 0.67f, radius = 0.14f;

        float dist = sqrt(pow(glX - sunX, 2) + pow(glY - sunY, 2));
        if (dist <= radius) {
            isNight = !isNight;
            glClearColor(isNight ? 0.0f : 0.6f, isNight ? 0.0f : 0.9f, isNight ? 0.2f : 1.0f, 1.0f);
            glutPostRedisplay();
        }
    }
}

void drawScenario3()
{

    drawSun3();
    drawSea3();
    drawMoon3();
    drawLand3();
    drawBuildings3();
    drawClouds3();
}


//'''''''''''''''''''senario4'''''''''''''

//float cloudinitial = 0.0f;
void updateClouds4(int value) {
    cloudinitial -= 0.01f;
    if (cloudinitial < -1.5f) {
        cloudinitial = 1.5f;
    }

    glutPostRedisplay();
    glutTimerFunc(100, updateClouds4, 0);
}


//Boat Animation
float boatinitial = 0.0f;
float boatinitial2= 0.0f;
void updateBoatsX(int value) {
    boatinitial+= 0.02f;
    if (boatinitial > 1.5) {
        boatinitial = -1.5;
    }


    glutPostRedisplay();
    glutTimerFunc(100, updateBoatsX, 0);
}
void updateBoatsY (int value) {
        boatinitial2+=0.01;
    if (boatinitial2 >0.2f){
        boatinitial2 = 0.2f;
    }
     glutPostRedisplay();
    glutTimerFunc(90, updateBoatsY, 0);
}


void drawSun4() {
    float x = 0.0f, y = 0.67f, radius = 0.14f;
    int triangleAmount = 50;
    float twicePi = 2.0f * 3.14159265359f;

    glColor3f(1.0f, 0.9f, 0.0f); // yellow
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}


void drawCloud4(float x, float y, float baseRadius) {
    int triangleAmount = 50;
    float twicePi = 2.0f * 3.14159265359f;

    glColor3f(1.0f, 1.0f, 1.0f); // white

    // Central circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (baseRadius * cos(i * twicePi / triangleAmount)),
            y + (baseRadius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    // Additional circles
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x - 0.04f, y + 0.02f);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x - 0.04f + (baseRadius * 0.8f * cos(i * twicePi / triangleAmount)),
            y + 0.02f + (baseRadius * 0.8f * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + 0.04f, y + 0.02f);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + 0.04f + (baseRadius * 0.8f * cos(i * twicePi / triangleAmount)),
            y + 0.02f + (baseRadius * 0.8f * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void drawClouds4() {
    drawCloud4(-0.43f + cloudinitial, 0.78f, 0.056f);
    drawCloud4(-0.35f + cloudinitial, 0.83f, 0.056f);
    drawCloud4(-0.27f + cloudinitial, 0.78f, 0.056f);
    drawCloud4(0.43f + cloudinitial, 0.89f, 0.056f);
    drawCloud4(0.51f + cloudinitial, 0.94f, 0.056f);
    drawCloud4(0.59f + cloudinitial, 0.89f, 0.056f);
}


void drawSea4() {
    glColor3f(0.0f, 0.4f, 0.8f); // blue
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f);
    glEnd();
}

void drawDockyard4() {
    glColor3f(0.5f, 0.35f, 0.05f); // brown
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 0.07f);
    glVertex2f(-1.0f, 0.07f);
    glEnd();
}

void drawCargoContainer4(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b); // Container color
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // outline
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // texture
    glLineWidth(0.5f);
    float spacing = width / 6.0f;
    for (int i = 1; i <= 5; i++) {
        float lineX = x + i * spacing;
        glBegin(GL_LINES);
        glVertex2f(lineX, y);
        glVertex2f(lineX, y + height);
        glEnd();
    }
}

void drawCargoContainers4() {
    //Bottom layer
    drawCargoContainer4(-0.84f, 0.05f, 0.20f, 0.05f, 0.9f, 0.9f, 0.08f); // Yellow left
    drawCargoContainer4(0.45f, 0.05f, 0.20f, 0.05f, 0.9f, 0.9f, 0.08f); // Yellow right
    drawCargoContainer4(-0.71f, 0.07f, 0.20f, 0.05f, 0.4f, 0.6f, 0.26f); // green
    drawCargoContainer4(-0.5f, 0.07f, 0.20f, 0.05f, 0.1f, 0.1f, 0.8f); // Blue
    drawCargoContainer4(-0.29f, 0.07f, 0.20f, 0.05f, 0.4f, 0.2f, 0.15f); // Brown
    drawCargoContainer4(-0.075f, 0.07f, 0.20f, 0.05f, 0.8f, 0.1f, 0.1f); // Red
    drawCargoContainer4(0.14f, 0.07f, 0.20f, 0.05f, 0.1f, 0.1f, 0.8f); // Blue
    drawCargoContainer4(0.35f, 0.07f, 0.20f, 0.05f, 0.455f, 0.5f, 0.055f); // olive
    //2nd layer
    drawCargoContainer4(-0.605f, 0.12f, 0.20f, 0.05f, 0.3f, 0.05f, 0.5f); // Purple
    drawCargoContainer4(-0.395f, 0.12f, 0.20f, 0.05f, 0.455f, 0.5f, 0.055f); // Olive
    drawCargoContainer4(-0.182f, 0.12f, 0.20f, 0.05f, 0.1f, 0.1f, 0.8f); // Blue
    drawCargoContainer4(0.0325f, 0.12f, 0.20f, 0.05f, 0.4f, 0.2f, 0.15f); // Brown
    drawCargoContainer4(0.245f, 0.12f, 0.20f, 0.05f, 0.8f, 0.1f, 0.1f); // Red

}


void drawBoat4(float x, float y) {
    // Boat body
    glColor3f(0.2f, 0.2f, 0.2f); //dark gray
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + 0.25f, y);
    glVertex2f(x + 0.22f, y - 0.05f);
    glVertex2f(x + 0.03f, y - 0.05f);
    glEnd();

    // Boat deck
    glColor3f(0.3f, 0.3f, 0.3f); //light gray
    glBegin(GL_QUADS);
    glVertex2f(x + 0.04f, y);
    glVertex2f(x + 0.21f, y);
    glVertex2f(x + 0.21f, y + 0.02f);
    glVertex2f(x + 0.04f, y + 0.02f);
    glEnd();

    // Boat cabin
    glColor3f(0.7f, 0.7f, 0.7f); //light gray
    glBegin(GL_QUADS);
    glVertex2f(x + 0.08f, y + 0.02f);
    glVertex2f(x + 0.17f, y + 0.02f);
    glVertex2f(x + 0.17f, y + 0.08f);
    glVertex2f(x + 0.08f, y + 0.08f);
    glEnd();

    // Chimney
    glColor3f(0.5f, 0.1f, 0.1f); //dark red
    glBegin(GL_QUADS);
    glVertex2f(x + 0.12f, y + 0.08f);
    glVertex2f(x + 0.14f, y + 0.08f);
    glVertex2f(x + 0.14f, y + 0.12f);
    glVertex2f(x + 0.12f, y + 0.12f);
    glEnd();

}


void drawBoats4() {
    drawBoat4(-0.98f + boatinitial, -0.15f - boatinitial2);
    drawBoat4(0.35f + boatinitial, -0.25f - boatinitial2/2);
}

void drawBigShip4(float x, float y) {
     // Ship hull
    glColor3f(0.2f, 0.2f, 0.3f); // Dark blue-gray
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.3375f, y - 0.135f);
    glVertex2f(x + 0.3375f, y - 0.135f);
    glVertex2f(x + 0.30375f, y - 0.16875f);
    glVertex2f(x - 0.30375f, y - 0.16875f);
    glEnd();

    // Red base strip
    glColor3f(0.8f, 0.1f, 0.1f); // Red
    glBegin(GL_QUADS);
    glVertex2f(x - 0.3375f, y - 0.16875f);
    glVertex2f(x + 0.3375f, y - 0.16875f);
    glVertex2f(x + 0.3375f, y - 0.189f);
    glVertex2f(x - 0.3375f, y - 0.189f);
    glEnd();

    // Containers (top row)
    drawCargoContainer4(x - 0.27f, y - 0.0675f, 0.1215f, 0.0675f, 0.1f, 0.6f, 0.1f); // Green
    drawCargoContainer4(x - 0.135f, y - 0.0675f, 0.1215f, 0.0675f, 0.6f, 0.1f, 0.1f); // Red
    drawCargoContainer4(x, y - 0.0675f, 0.1215f, 0.0675f, 0.3f, 0.05f, 0.5f);       // Purple

    // Containers (bottom row)
    drawCargoContainer4(x - 0.27f, y - 0.135f, 0.1215f, 0.0675f, 0.2f, 0.4f, 0.6f); // Blue
    drawCargoContainer4(x - 0.135f, y - 0.135f, 0.1215f, 0.0675f, 0.8f, 0.5f, 0.2f); // Orange
    drawCargoContainer4(x, y - 0.135f, 0.1215f, 0.0675f, 0.4f, 0.4f, 0.4f);       // Gray

    // Cabin base
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glBegin(GL_QUADS);
    glVertex2f(x + 0.10125f, y - 0.135f);
    glVertex2f(x + 0.27f, y - 0.135f);
    glVertex2f(x + 0.27f, y + 0.135f);
    glVertex2f(x + 0.10125f, y + 0.135f);
    glEnd();

// Cabin windows (top row)
glColor3f(0.0f, 0.0f, 0.0f); // Black color

// 1st window
glBegin(GL_QUADS);
glVertex2f(x + 0.1215f, y + 0.03375f);
glVertex2f(x + 0.14175f, y + 0.03375f);
glVertex2f(x + 0.14175f, y + 0.054f);
glVertex2f(x + 0.1215f, y + 0.054f);
glEnd();

// 2nd window
glBegin(GL_QUADS);
glVertex2f(x + 0.15525f, y + 0.03375f);
glVertex2f(x + 0.1755f, y + 0.03375f);
glVertex2f(x + 0.1755f, y + 0.054f);
glVertex2f(x + 0.15525f, y + 0.054f);
glEnd();

// 3rd window
glBegin(GL_QUADS);
glVertex2f(x + 0.189f, y + 0.03375f);
glVertex2f(x + 0.20925f, y + 0.03375f);
glVertex2f(x + 0.20925f, y + 0.054f);
glVertex2f(x + 0.189f, y + 0.054f);
glEnd();

// 4th window
glBegin(GL_QUADS);
glVertex2f(x + 0.22275f, y + 0.03375f);
glVertex2f(x + 0.243f, y + 0.03375f);
glVertex2f(x + 0.243f, y + 0.054f);
glVertex2f(x + 0.22275f, y + 0.054f);
glEnd();


    // Chimney
    glColor3f(0.8f, 0.1f, 0.1f); // Red
    glBegin(GL_QUADS);
    glVertex2f(x + 0.2025f, y + 0.135f);
    glVertex2f(x + 0.23625f, y + 0.135f);
    glVertex2f(x + 0.23625f, y + 0.2025f);
    glVertex2f(x + 0.2025f, y + 0.2025f);
    glEnd();
}

void drawBigShip4(){
    drawBigShip4(-0.1, -0.01);
}

void drawBuilding4(float x, float y, float width, float height) {
    // Building body
    glColor3f(0.6f, 0.6f, 0.6f); // Light gray
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // windows for each floor
    float floorHeight = height / 7.0f;
    float windowWidth = width / 6.0f;
    float windowHeight = floorHeight / 2.0f;
    float gap = (width - (5 * windowWidth)) / 6.0f;

    glColor3f(0.2f, 0.2f, 0.8f); // Blue

    for (int floor = 0; floor < 7; ++floor) {
        float floorBase = y + (floor * floorHeight) + (floorHeight / 4.0f);

        for (int window = 0; window < 5; ++window) {
            float windowX = x + gap + (window * (windowWidth + gap));

            glBegin(GL_QUADS);
            glVertex2f(windowX, floorBase);
            glVertex2f(windowX + windowWidth, floorBase);
            glVertex2f(windowX + windowWidth, floorBase + windowHeight);
            glVertex2f(windowX, floorBase + windowHeight);
            glEnd();
        }
    }

}

void drawBuilding4(){
drawBuilding4(0.68, 0.07, 0.30, 0.7);
}

void displaySenario4() {


    drawSun4();
    drawClouds4();
    drawSea4();
    drawCargoContainers4();
    drawDockyard4();
    drawBoats4();
    drawBigShip4();
    drawBuilding4();


}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

   glLoadIdentity();

    // Display the active scenario
    switch (currentScenario) {
        case 1:
            scenario1();
        drawYacht(0.7,0.7,tx+position,ty);
        glFlush;
            break;
        case 2:
           drawScenario2();

        drawYacht(0.5,0.5,tx+position,ty-0.2);
        glFlush;
            break;
        case 3:
            drawScenario3();
             drawYacht(0.5,0.5,tx+position,ty-0.2);
        glFlush;
            break;
        case 4:
            displaySenario4();
            drawYacht(0.4,0.4,tx+position,ty-0.4);
        glFlush;

            break;
    }

    //drawYacht(0.5,0.5,tx+position,ty); // Yacht moves only on X-axis
    glFlush();
}

// Function to set up the OpenGL environment
void  MyInit() {
   glClearColor(0.6f, 0.9f, 1.0f, 1.0f); // Set background color to white
    glMatrixMode(GL_PROJECTION); // Switch to projection matrix mode
    glLoadIdentity(); // Reset any previous transformations
   // glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set up an orthogonal projection matrix (2D)
    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix mode
    glutCreateMenu(Menu);
    glutAddMenuEntry("start Flag",1);
    glutAddMenuEntry("stop Flag",2);
    glutAddMenuEntry("stop ship",4);
    glutAddMenuEntry("start ship",3);
    glutAddMenuEntry("EXIT",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutSpecialFunc(SpecialInput);
    glutIdleFunc(Animate);
   glutKeyboardFunc(keyboard);
     glutTimerFunc(100, update, 0);
    glutTimerFunc(100, updateClouds, 0);
    glutMouseFunc(mouseClick3);
    glutMouseFunc(mouseClick);
      glutTimerFunc(100, updateClouds4, 0);
    glutTimerFunc(100, updateBoatsX, 0);
    glutTimerFunc(90, updateBoatsY, 0);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("OpenGL Ship Animation");
    MyInit();  // Initialize OpenGL settings

    glutPositionWindow(100, 20);
    glutDisplayFunc(display);
      glutTimerFunc(16, updateP, 0);
    glutTimerFunc(16, updateC, 0);
    glutTimerFunc(16, toggleCircleColor, 0);
    sndPlaySound("yacht", SND_ASYNC);

 //glutKeyboardFunc(KeyboardInput);
    glutMainLoop();
    return 0;
}
