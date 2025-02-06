#include <GL/glut.h>
#include <cmath>
#include <vector>


std::vector<std::pair<float, float>> StarPoints(int num_points, float centerX, float centerY, float width, float height)
{
    std::vector<std::pair<float, float>> points(num_points);

    float rx = width / 2.0f;
    float ry = height / 2.0f;


    double theta = -M_PI / 2.0;
    double dtheta = 4 * M_PI / num_points;

    for (int i = 0; i < num_points; i++)
    {
        float x = centerX + rx * std::cos(theta);
        float y = centerY + ry * std::sin(theta);
        points[i] = std::make_pair(x, y);
        theta += dtheta;
    }

    return points;
}


void DrawFilledStar(const std::vector<std::pair<float, float>>& points, float centerX, float centerY)
{
    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < points.size(); i++)
    {

        glVertex2f(centerX, centerY);
        glVertex2f(points[i].first, points[i].second);
        glVertex2f(points[(i + 1) % points.size()].first, points[(i + 1) % points.size()].second);
    }
    glEnd();
}


void DrawOutlinedStar(const std::vector<std::pair<float, float>>& points)
{
    glBegin(GL_LINE_LOOP);
    for (const auto& point : points)
    {
        glVertex2f(point.first, point.second);
    }
    glEnd();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);


    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(0.0f, -1.0f);
    glEnd();


    float centerX1 = -0.5f;
    float centerY1 = 0.0f;
    float width1 = 0.8f;
    float height1 = 0.8f;

    int num_points1 = 5;
    auto points1 = StarPoints(num_points1, centerX1, centerY1, width1, height1);

    glColor3f(0.0f, 1.0f, 0.0f);
    DrawFilledStar(points1, centerX1, centerY1);


    float centerX2 = 0.5f;
    float centerY2 = 0.0f;
    float width2 = 0.8f;
    float height2 = 0.8f;

    int num_points2 = 5;
    auto points2 = StarPoints(num_points2, centerX2, centerY2, width2, height2);

    glColor3f(1.0f, 0.0f, 0.0f);
    DrawOutlinedStar(points2);

    glFlush();
}


void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("STAR");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
