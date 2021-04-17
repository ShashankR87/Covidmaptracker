#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <thread>
#include <chrono>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;
int datecnt = 0;
string datesarray[100];
char dateschararray[100][100];
int cnt = 0;
GLuint texture;
int start = 1;
GLfloat xRotated, yRotated, zRotated;
GLdouble radius = 1;
void init() {
	glOrtho(-1000 / 2, 1000 / 2, -1000 / 2, 1000 / 2, -500, 500);
}


GLuint glInitTexture(char* filename)
{
	GLuint t = 0;
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

	glGenTextures(1, &t);
	glBindTexture(GL_TEXTURE_2D, t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//unsigned char data[] = { 255, 0, 0, 255 };
	if (data)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else
		std::cout << "fail";
	return t;
}



void drawImage(GLuint file, float x, float y, float w, float h,float travalue)
{
    static GLfloat theta[] = { 290.0,0.0,0.0 };
    static GLint axis = 2.0;
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glPushMatrix();
    //glTranslatef(x, y, 0.0);
    //glRotatef(angle, 0.0, 0.0, 1.0);
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, file);

    glEnable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, travalue);//default is -3.5

    //glRotatef(yRotated, 0.0, 1.0, 0.0);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    GLUquadric* qobj = gluNewQuadric();
    gluQuadricTexture(qobj, GL_TRUE);
    gluSphere(qobj, radius, 20, 20);
    gluDeleteQuadric(qobj);
    glDisable(GL_TEXTURE_2D);

    glFlush();

    //yRotated += 0.01;
    theta[axis] += 0.1;
    if (theta[axis] > 360.0)
        theta[axis] -= 360.0;

    //glBindTexture(GL_TEXTURE_2D, 0);
    glFlush();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);



}


//Displays map on screen
void drawMap() {
	std::cout << "\nDraw map\n";

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(60.0, w / h, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -15);

	for (int i = 0; i < 2800+(1-1)*3600 ; i++) {						// 2800(1),6400(2),10000(3)..... ap-> 2800+(3-1)3600
		glClear(GL_DEPTH_BUFFER_BIT);
		drawImage(texture, 0, 0, 100, 200,-3.5);
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(800));
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -3.3);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -3.2);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -3.1);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -3.0);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.9);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.8);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.7);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.6);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.5);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.4);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.3);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.2);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.1);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.0);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -1.9);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -1.8);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -1.7);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -1.6);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -1.5);
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -1.4);


			

	glutSwapBuffers();
	glEnd();
	glFlush();

}
void render()

{





	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);



	//glFlush();


	glPointSize(5);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3f(-450, -450, 10);
	glVertex3f(-450, -250, 10);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-450, -450, 10);
	glVertex3f(-250, -450, 10);

	glEnd();

	


	

	drawMap();

	//plotPoints();
	glFlush();



}
void Kbevent(unsigned char key, int x, int y) {
	if (key == 's') {
		start = start % 2;
		glutPostRedisplay();
	}

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Applying Textures");
	init();
	xRotated = yRotated = zRotated = 30.0;
	xRotated = 33;
	yRotated = 40;


	char fn[] = "map.jpg";
	texture = glInitTexture(fn);
	glutDisplayFunc(render);
	//glutReshapeFunc(reshapeFunc);
	//glutIdleFunc(idleFunc);
	glutKeyboardFunc(Kbevent);
	glutMainLoop();

	return 0;
}
