
#include <GL/glut.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
GLuint texture;
double angle = 0;
typedef struct
{
	int X;
	int Y;
	int Z;
	double U;
	double V;
}VERTICES;

const double PI = 3.1415926535897;
const int space = 10;
const int VertexCount = (90 / space) * (360 / space) * 4;
VERTICES VERTEX[VertexCount];
GLuint LoadTextureRAW(const char* filename);


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
		int k = 0;
	return t;
}

void DisplaySphere(double R, GLuint texture)
{

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int b;
	glScalef(0.0825 * R, 0.0825 * R, 0.0825 * R);
	//glRotatef (90, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_TRIANGLE_STRIP);
	for (b = 0; b < VertexCount; b++)
	{
		glTexCoord2f(VERTEX[b].U, VERTEX[b].V);
		glVertex3f(VERTEX[b].X, VERTEX[b].Y, -VERTEX[b].Z);
	}



	for (b = 0; b < VertexCount; b++)
	{

		glTexCoord2f(VERTEX[b].U, -VERTEX[b].V);

		glVertex3f(VERTEX[b].X, VERTEX[b].Y, VERTEX[b].Z);

	}

	glEnd();
}
void CreateSphere(double R, double H, double K, double Z) {
	int n;
	double a;
	double b;
	n = 0;
	for (b = 0; b <= 90 - space; b += space) {

		for (a = 0; a <= 360 - space; a += space)
		{
			VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
			VERTEX[n].V = (2 * b) / 360;
			VERTEX[n].U = (a) / 360;

			n++;
			VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
			VERTEX[n].V = (2 * (b + space)) / 360;
			VERTEX[n].U = (a) / 360;
			n++;
			VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
			VERTEX[n].V = (2 * b) / 360;
			VERTEX[n].U = (a + space) / 360;
			n++;
			VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b + space) / 180 * PI) - H;
			VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b + space) / 180 * PI) + K;
			VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
			VERTEX[n].V = (2 * (b + space)) / 360;
			VERTEX[n].U = (a + space) / 360;
			n++;
		}

	}
}
void display(void) {

	glClearDepth(1);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 0, -10);
	glRotatef(angle, 0, 1, 0);
	DisplaySphere(5, texture);
	glutSwapBuffers();
	angle += 0.01;
}
void init(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glDepthFunc(GL_LEQUAL);

	char fn[] = "map.jpg";
	texture = glInitTexture(fn);
	//texture = LoadTextureRAW("map.bmp");

	CreateSphere(30, 0, 0, 0);
}
void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(500, 500);

	glutInitWindowPosition(100, 100);

	glutCreateWindow("A basic OpenGL Window");

	init();

	glutDisplayFunc(display);

	glutIdleFunc(display);

	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}
GLuint LoadTextureRAW(const char* filename)
{

	GLuint texture;

	int width, height;

	unsigned char* data;

	FILE* file;



	file = fopen(filename, "rb");

	if (file == NULL) return 0;



	width = 1024;

	height = 512;

	data = (unsigned char*)malloc(width * height * 3);


	//int size = fseek(file,);
	fread(data, width * height * 3, 1, file);

	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];
		//B = data[index];
		data[index] = R;
		data[index + 2] = B;

	}


	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);





	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}