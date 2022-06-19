#include <GLUT/glut.h>
#include<math.h>
#include<iostream>
using namespace std;

#define WIDTH 500
#define HEIGHT 500


void Init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3d(1.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250, 250.0, -250.0, 250.0);
	glMatrixMode(GL_MODELVIEW);

}

float r;
void BresenhamCircle(void)
{
    float d, x, y;

    glClear(GL_COLOR_BUFFER_BIT);
    x = 0;
    y = r;
    d = 1 - r;

    while (x <= y)
    {
        glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);//线的颜色为红色
        glVertex3f(x, y, 0);
        glVertex3f(-x, -y, 0);
        glVertex3f(-x, y, 0);
        glVertex3f(x, -y, 0);
        glVertex3f(y, -x, 0);
        glVertex3f(-y, -x, 0);
        glVertex3f(-y, x, 0);
        glVertex3f(y, x, 0);
        glEnd();

        if (d < 0)
        {

            d += 2 * x + 3;

        }
        else
        {

            d += 2 * (x - y) + 5;
            y--;

        }
        x++;
        glFlush();
    }

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("中点breseham画圆");
    cout << "输入r" << endl;
    cin >> r;

	Init();
	glutDisplayFunc(BresenhamCircle);
	glutMainLoop();
}
