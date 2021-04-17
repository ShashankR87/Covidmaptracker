#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <GL/glut.h>
#include <thread>
#include <chrono>
#include <math.h>
#include <Windows.h>
#include<algorithm> 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
void renderMap();
char statenames[29][100] = { "Andaman Nicobar","Andhra Pradesh","Bihar","Chhattisgarh","Delhi","Goa","Gujarat","Haryana","Himachal Pradesh","J and K","Jharkhand","Karnataka","Kerala","Madhya Pradesh","Maharashtra","NorthEast","Odisha","Punjab","Rajasthan","Tamil Nadu","Telengana","Uttar Pradesh","Uttarakhand","West Bengal" };
int finalc[26];
int rankc[24];
int win, Statewin, oldWin;
int statecode = -1;
using namespace std;
vector <string> dates;
vector <int> cases, deaths;
vector <float> statemids[27];
vector <int> statezones[29];
vector <int> casesState[26];
vector <int> deathsState[26];
int datecnt = 0;
string datesarray[100];
char dateschararray[100][100];
int cnt = 0;
GLuint texture;
int start = 1;
GLfloat xRotated, yRotated, zRotated;
GLdouble radius = 1;
double finalcases = 0;
double finaldeath = 0;
bool blink = false;
int loadingcount = 0;
bool firsttime = true;
int menuname = -1;
string base = "INITIALIZING ";
GLfloat dlr = 1.0;
GLfloat dlg = 1.0;
GLfloat dlb = 1.0;

GLfloat alr = 1.0;
GLfloat alg = 1.0;
GLfloat alb = 1.0;

GLfloat lx = 1.0;
GLfloat ly = 1.0;
GLfloat lz = 1.0;
GLfloat lw = 1.0;

void renderstateMap();
void KbeventState(unsigned char key, int x, int y);
void drawEarth();
void plotPointsState(int);
//Initializes the 3D Orthogonal Coordinate System for first screen
void init() {

	glOrtho(-1000 / 2, 1000 / 2, -1000 / 2, 1000 / 2, -500, 500);

}
//Initializes the 3D Orthogonal Coordinate System for Earth screen + Sets up Lighting
void init0() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat qaAmbientLight[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat qaDiffuseLight[] = { 1, 1, 1, 1.0 };
	GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	//glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
	GLfloat qaLightPosition[] = { 2000, 0, 0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.75);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 100.0);


	glColor3f(1, 1, 1);

}

//Draws a maroon circle to be used in state screens
void draw_deathcircle(float radius, float x1, float y1) {
	float x2, y2;
	float angle;
	glColor3f(0.5, 0, 0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x1, y1, 0);

	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x2 = x1 + sin(angle) * radius;
		y2 = y1 + cos(angle) * radius;
		glVertex3f(x2, y2, 0);
	}

	glEnd();

}

void drawZoneCircle(float radius, float x1, float y1, float r, float g, float b) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
	float x2, y2;
	float angle;
	glColor4f(r,g,b,0.1);
	
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x1, y1, 0);

	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x2 = x1 + sin(angle) * radius;
		y2 = y1 + cos(angle) * radius;
		glVertex3f(x2, y2, 0);
	}

	glEnd();
	glDisable(GL_BLEND);
}
//Draws a maroon circle
void draw_thecircle_red(float radius, float x1, float y1) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
	float x2, y2;
	float angle;
	glColor3f(0.5, 0, 0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x1, y1, 0);

	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x2 = x1 + sin(angle) * radius * 0.8;
		y2 = y1 + cos(angle) * radius * 2;
		glVertex3f(x2, y2, 0);
	}

	glEnd();
	glDisable(GL_BLEND);
}
void draw_thecircle_blue(float radius, float x1, float y1) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
	float x2, y2;
	float angle;
	glColor3f(0, 0, 0.5);

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x1, y1, 0);

	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x2 = x1 + sin(angle) * radius * 0.8;
		y2 = y1 + cos(angle) * radius * 2;
		glVertex3f(x2, y2, 0);
	}

	glEnd();
	glDisable(GL_BLEND);
}

//Draws blue circle to be used in state screens
void draw_casecircle(float radius, float x1, float y1) {
	float x2, y2;
	float angle;
	glColor3f(0, 0.0, 0.5);

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x1, y1, 1);

	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x2 = x1 + sin(angle) * radius;
		y2 = y1 + cos(angle) * radius;
		glVertex3f(x2, y2, 1);
	}

	glEnd();
}

//Displays text on screen
void renderbitmap(float x, float y, void* font, char* string, float r, float g, float b)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glColor3f(r, g, b);
	char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

//Initializes the texture from image
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
	if (data)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else
		std::cout << "fail";
	return t;
}


//Applies the earth texture on the sphere + Displays loading bar 
void drawImage(GLuint file, float x, float y, float w, float h, float travalue)
{
	GLfloat eEmissionColor[] = { 0, 0, 0, 1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, eEmissionColor);

	static GLfloat theta[] = { 290.0,0.0,0.0 };
	static GLint axis = 2.0;
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, file);

	glEnable(GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();




	glTranslatef(0.0, 0.0, travalue);//default is -3.5

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

	theta[axis] += 0.1;
	if (theta[axis] > 360.0)
		theta[axis] -= 360.0;

	glFlush();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);


	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);

	//glTranslatef(0.0, 0.0, -travalue);
	GLfloat surfEmissionColor[] = { 0.8, 0.8, 0.8, 1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, surfEmissionColor);

	loadingcount++;
	char string[100000];
	strcpy(string, base.c_str());

	char* c;
	glRasterPos3f(-20, -9, travalue - 1);
	for (c = string; *c != '\0'; c++)
	{
		glColor3f(1, 1, 1);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}

	glFlush();

	glColor3f(1.0, 1.0, 1.0);
	if (loadingcount % 140 == 0) {
		for (int m = 0; m < loadingcount / 140; m++) {
			base = base + "|";
		}
	}
	





}

//Displays texture of map onto a quad
void drawImageofMap(GLuint file, float x, float y, float w, float h)
{

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, file);

	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-5.1, -5.6);
	glTexCoord2f(0.0, 1.0); glVertex2f(-5.1, 4.7);
	glTexCoord2f(1.0, 1.0); glVertex2f(4.8, 4.7);
	glTexCoord2f(1.0, 0.0); glVertex2f(4.8, -5.6);
	glEnd();
	glFlush();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);



}

void bruh(int why) {

}

//Clicking on a state centre redirects the user to that state's screen
void Mouseevent(int button, int action, int x, int y) {
	
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {

		if (menuname!=-1) {
			glutDestroyMenu(menuname);
			menuname = -1;
		}



		std::cout << "Pinged at " << x << " " << y << "\n";
		for (int i = 0; i < 24; i++) {
			int p = statemids[i][2];
			int q = statemids[i][3];

			if (x > p - 20 && x<p + 20 && y>  q - 20 && y < q + 20) {
				std::cout << "Pinged at " << i << "\n";
				statecode = i;
				string statenamewind = statenames[i];
				string winName = statenamewind;
				char wn[20];
				strcpy(wn, winName.c_str());

				Statewin = glutCreateWindow(wn);
				init();
				glutDisplayFunc(renderstateMap);
				glutKeyboardFunc(KbeventState);
				menuname = -1;
				break;
			}

		}
	}
	if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN && menuname==-1) {

		std::cout << "Right Pinged at " << x << " " << y << "\n";
		for (int i = 0; i < 24; i++) {
			int p = statemids[i][2];
			int q = statemids[i][3];

			if (x > p - 20 && x<p + 20 && y>  q - 20 && y < q + 20) {

				statecode = i;
				string statenamewind = statenames[i];
				string winName = statenamewind;
				char wn[20];

				string gzone = "Number of Green Zones: " + to_string(statezones[i][0]);
				char greenzone[100];
				strcpy(greenzone, gzone.c_str());

				string ozone = "Number of Orange Zones: " + to_string(statezones[i][1]);
				char orangezone[100];
				strcpy(orangezone, ozone.c_str());

				string rzone = "Number of Red Zones: " + to_string(statezones[i][2]);
				char redzone[100];
				strcpy(redzone, rzone.c_str());
				strcpy(wn, winName.c_str());
				std::cout << "Created " << wn << "\n";
				std::cout << "zones " << statezones[i][0] << " " << statezones[i][1] << " " << statezones[i][2] << "\n";
				menuname = glutCreateMenu(bruh);
				glutAddMenuEntry(wn, 1);
				glutAddMenuEntry(greenzone, 2);
				glutAddMenuEntry(orangezone, 3);
				glutAddMenuEntry(redzone, 4);
				glutAttachMenu(GLUT_RIGHT_BUTTON);
				break;
			}

		}


		
	}



}

//Clicking anywhere on the title screen begins the earth rotation
void MouseeventFirst(int button, int action, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {

		x = x - (1560 / 2) + 40;
		y = (810 / 2) - y - 25;

		std::cout << "Pinged at " << x << " " << y << "\n";
		init0();
		drawEarth();

	}
}

//Displays the earth, zooms in on India and opens new window
void drawEarth() {
	glClearColor(0.0, 0.0, 0.0, 0.0);


	std::cout << "\nDraw earth\n";
	GLfloat qaYellow[] = { 1.0, 0.7, 0.0, 1.0 };
	GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaYellow);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaWhite);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 60.0);
	glNormal3f(0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(60.0, w / h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -15);
	for (int i = 0; i < 2800 + (1 - 1) * 3600; i++) {						// 2800(1),6400(2),10000(3)..... ap-> 2800+(3-1)3600
		glClear(GL_DEPTH_BUFFER_BIT);
		drawImage(texture, 0, 0, 100, 200, -3.5);
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(800));
	glClear(GL_DEPTH_BUFFER_BIT);

	drawImage(texture, 0, 0, 100, 200, -3.3);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -3.2);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -3.1);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -3.0);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.9);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.8);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.7);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.6);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.5);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.4);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.3);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.2);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.1);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -2.0);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -1.9);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -1.8);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -1.7);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -1.6);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -1.5);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glClear(GL_DEPTH_BUFFER_BIT);
	drawImage(texture, 0, 0, 100, 200, -1.4);
	std::this_thread::sleep_for(std::chrono::milliseconds(25));;
	glutSwapBuffers();
	glEnd();
	glFlush();
	std::this_thread::sleep_for(std::chrono::milliseconds(900));

	glutDestroyWindow(win);
	oldWin = glutCreateWindow("India");
	init();
	glutDisplayFunc(renderMap);
	glutMouseFunc(Mouseevent);
	glutMainLoop();

}
//Displays India map
void drawMap() {
	std::cout << "\nDraw map\n";

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(45.0, w / h, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -15);
	drawImageofMap(texture, 0, 0, 3, 4);

	glutSwapBuffers();
	glEnd();
	glFlush();

}

//Displays state centre points, plots the graphs and displays the circle
void plotPoints() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	gluOrtho2D(-41.8, 41.8, -80, 80);
	glMatrixMode(GL_PROJECTION);
	glPointSize(5);
	glColor3f(1, 0, 0);
	auto i = cases.begin();
	int j = 0;
	auto k = deaths.begin();
	int datecnt = 0;
	auto l = cases.back();
	auto l1 = deaths.back();
	auto quo = l / (l1*7);
	for (; i < cases.end(); i++, k++, j += 200 / (cnt), datecnt++) {	//draw the points cases
		glPointSize(5);
		glColor3f(1, 0, 0);
		glBegin(GL_POINTS);
		glColor3f(0, 1, 1);
		glVertex2f(j - 453.0000, *i * (200.0000 / finalcases) - 446);		//200/9145   
		glColor3f(1, 0, 0);
		glVertex2f(j + 280.0000, *k * (200.0000 / finaldeath) - 446);		//200/308
		glEnd();
		glFlush();
		glColor3f(0, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(-470 - 40, 450 + 40);
		glVertex2f(-470 + 40, 450 + 40);
		glVertex2f(-470 + 40, 450 - 50);
		glVertex2f(-470 - 40, 450 - 50);
		glEnd();
		//glClear(GL_DEPTH_BUFFER_BIT);
		glColor3f(1, 1, 1);
		char buf[100] = { 0 };
		sprintf_s(buf, dateschararray[datecnt]);
		char datetext[] = "Date: ";
		char country[] = "India";
		renderbitmap(-470, 410, GLUT_BITMAP_HELVETICA_18, buf, 1, 1, 1);
		renderbitmap(-470, 450, GLUT_BITMAP_HELVETICA_18, datetext, 1, 1, 1);
		renderbitmap(420, 450, GLUT_BITMAP_HELVETICA_18, country, 1, 1, 1);
		glFlush();

		int state = 0;
		for (; state < 24; state++) {
			int numofcases = casesState[state][datecnt];

			int x = statemids[state][0];

			int y = statemids[state][1];
			glPointSize(5);
			glColor3f(0, 1, 0);
			glBegin(GL_POINTS);
			for (int s = 0; s < 24; s++) {
				glVertex2f(statemids[s][0], statemids[s][1]);
			}
			glEnd();
		}
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
		draw_thecircle_red((*k * (200/quo) / l1), 0, 0);
		draw_thecircle_blue((*i * 200 / l), 0, 0);
        //max radius 196
		glDisable(GL_BLEND);
		glFlush();
		glClear(GL_DEPTH_BUFFER_BIT);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	std::cout << statemids[0][0] << " " << statemids[0][1] << " linesss\n";
}

//Plots the graphs and displays the circles (cases and deaths) for specified state
void plotPointsState(int zzz) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	int numofcases = casesState[zzz][(casesState[zzz].size()) - 1];
	int numofdeaths = deathsState[zzz][(deathsState[zzz].size()) - 1];
	int x = 0;
	int y = 0;
	gluOrtho2D(-41.8, 41.8, -41.8, 41.8);
	glMatrixMode(GL_PROJECTION);
	glPointSize(5);
	glColor3f(1, 0, 0);
	auto i = casesState[zzz].begin();
	float i1 = 0;
	int j = 0;
	auto k = deathsState[zzz].begin();
	float k1 = 0;
	int datecnt = 0;
	auto l = casesState[zzz].back();
	auto m = l / 5;
	int numOfIter = casesState[zzz].size();

	int green = statezones[zzz][0];
	int orange = statezones[zzz][1];
	int red = statezones[zzz][2];
	float gp[3] = { 0,0.5,0 };
	float op[3] = { 0.8,0.4,0 };
	float rp[3] = { 0.5,0,0 };
	int totalzones = green + orange + red;
	double greenshare = green *250/ totalzones;
	double orangeshare = orange *250/ totalzones;
	double redshare = red *250/ totalzones;
	int grad = 0, orad = 0, rrad = 0;
	if (greenshare > 0 && greenshare < 40) greenshare = 40;
	if (orangeshare > 0 && orangeshare < 40) orangeshare = 40;
	if (redshare > 0 && redshare < 40) redshare = 40;
	std::cout << "Green " << greenshare <<" Orange " <<orangeshare<<" Red "<<redshare<<"\n";
	float w = 0;
	//drawZoneCircle(30, 0, 0, 1, 1, 1);
	for (; i < casesState[zzz].end(); k1 += (*k / 96.00), i++, k++, j += 200 / (cnt), datecnt++, grad= roundf(grad + greenshare/numOfIter), orad = roundf(orad+ orangeshare / numOfIter), rrad = roundf(rrad + redshare / numOfIter), w+=(1/30)) {	//draw the points cases	
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
	
		//draw_casecircle((*i * 196 / l), 0, 0);//max radius 196
		//draw_deathcircle((*k * 196 / m), 0, 0);
		vector<pair<float, float*>>colormap;
		colormap.push_back(make_pair(grad, gp));
		colormap.push_back(make_pair(orad, op));
		colormap.push_back(make_pair(rrad, rp));
		sort(colormap.begin(), colormap.end());
		float *color0 = colormap[0].second;
		float *color1 = colormap[1].second;
		float *color2 = colormap[2].second;
		float radi0 = colormap[0].first;
		float radi1 = colormap[1].first;
		float radi2 = colormap[2].first;
		std:: cout << "Radi0 " << radi0 << " Redshare "<<redshare<<" Num of it "<< numOfIter <<endl;
		std::cout << "Radi1 " << radi1 << " Oshare " << orangeshare << " Num of it " << numOfIter << endl;
		std::cout << "Radi2 " << radi2 << " Gshare " << greenshare << " Num of it " << numOfIter << endl;
		std::cout << endl;

		//drawZoneCircle(radi0, 50, 0, 1, 1, 1);
		
		drawZoneCircle(radi0, -80, 20,color0[0],color0[1],color0[2]);
		drawZoneCircle(radi1, 50, -20, color1[0], color1[1], color1[2]);
		drawZoneCircle(radi2, -15, 0, color2[0], color2[1], color2[2]);
		glDisable(GL_BLEND);
		glPointSize(5);
		glBegin(GL_POINTS);
		glColor3f(0, 1, 1);
		glVertex2f(j - 454.0000, *i * (200.0000 / casesState[zzz][(casesState[zzz].size()) - 1]) * 0.5225 - 235);		//200/9145   
		glColor3f(1, 0, 0);
		glVertex2f(j + 280.0000, *k * (200.0000 / deathsState[zzz][(deathsState[zzz].size()) - 1]) * 0.5225 - 235);		//200/308
		glEnd();
		glFlush();
		glColor3f(0, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(-470 - 40, 230 + 40);
		glVertex2f(-470 + 40, 230 + 40);
		glVertex2f(-470 + 40, 230 - 40);
		glVertex2f(-470 - 40, 230 - 40);
		glEnd();
		glClear(GL_DEPTH_BUFFER_BIT);
		glColor3f(1, 1, 1);
		char buf[100] = { 0 };
		sprintf_s(buf, dateschararray[datecnt]);
		renderbitmap(-470, 210, GLUT_BITMAP_HELVETICA_18, buf, 1, 1, 1);
		char datetext[] = "Date: ";
		renderbitmap(-470, 230, GLUT_BITMAP_HELVETICA_18, datetext, 1, 1, 1);
		char buf1[100] = { 0 };
		sprintf_s(buf1, statenames[zzz]);
		renderbitmap(380, 230, GLUT_BITMAP_HELVETICA_18, buf1, 1, 1, 1);
		char buf3[100] = { 0 };
		sprintf_s(buf3, "Impact rank:");
		renderbitmap(380, 200, GLUT_BITMAP_HELVETICA_18, buf3, 1, 1, 1);
		char buf2[100] = { 0 };
		_itoa(rankc[zzz], buf2, 10);
		renderbitmap(450, 200, GLUT_BITMAP_HELVETICA_18, buf2, 1, 1, 1);

		string gzone = "Number of Green Zones: " + to_string(statezones[zzz][0]);
		char greenzone[100];
		strcpy(greenzone, gzone.c_str());
		renderbitmap(-470, 170, GLUT_BITMAP_HELVETICA_18, greenzone, 0, 0.5, 0);
		string ozone = "Number of Orange Zones: " + to_string(statezones[zzz][1]);
		char orangezone[100];
		strcpy(orangezone, ozone.c_str());
		renderbitmap(-470, 140, GLUT_BITMAP_HELVETICA_18, orangezone, 0.8, 0.4, 0);
		string rzone = "Number of Red Zones: " + to_string(statezones[zzz][2]);
		char redzone[100];
		strcpy(redzone, rzone.c_str());
		renderbitmap(-470, 110, GLUT_BITMAP_HELVETICA_18, redzone, 1, 0, 0);

		char buf4[100] = { 0 };
		sprintf_s(buf4, "Press ESC to exit");
		renderbitmap(380, 170, GLUT_BITMAP_HELVETICA_18, buf4, 0.8, 1, 0);
		glFlush();
		std::this_thread::sleep_for(std::chrono::milliseconds(70));
	}
}
//Draws the cases graph
void drawGraphCases(int casesScale[]) {  //cases
	auto i = cases.begin();
	auto j = 0;
	glColor3f(1, 1, 1);
	char str[] = "Cases";
	glRasterPos2f(-499, -350);
	for (int k = 0; k < strlen(str); k++) {	//cases string
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[k]);
	}
	char st[] = "Dates";
	glRasterPos2f(-365, -485);
	for (int k = 0; k < strlen(st); k++) {		//string dates
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
	}
	glColor3f(1, 0, 0);
	glPointSize(10);
	for (int z = 0; i < cases.end(); i++, j += 200 / (cnt), z++) {	//draw the points cases
		if (z % 7 == 0) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);						//Draw small vertical lines
			glVertex2f(j - 450, -450);
			glVertex2f(j - 450, -455);
			glEnd();
			char buf[100] = { 0 };
			sprintf_s(buf, dateschararray[z]);
			renderbitmap(j - 450, -465, GLUT_BITMAP_HELVETICA_10, buf, 1, 1, 1);
			glColor3f(1, 0, 0);
		}
		glFlush();
	}
	glFlush();
}

//Draws the deaths graph
void drawGraphDeaths()
{
	auto i = deaths.begin();
	auto j = 0;
	glColor3f(1, 1, 1);
	char str[] = "Deaths";
	glRasterPos2f(230, -350);
	for (int k = 0; k < strlen(str); k++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[k]);
	}
	char st[] = "Dates";
	glRasterPos2f(360, -485);
	for (int k = 0; k < strlen(st); k++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
	}
	glColor3f(1, 0, 0);
	glPointSize(10);
	for (int z = 0; i < deaths.end(); i++, j += 200 / (cnt), z++) {
		if (z % 7 == 0) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);					//Draw small vertical lines
			glVertex2f(j + 275, -450);
			glVertex2f(j + 275, -455);
			glEnd();
			char buf[100] = { 0 };
			sprintf_s(buf, dateschararray[z]);
			renderbitmap(j + 275, -465, GLUT_BITMAP_HELVETICA_10, buf, 1, 1, 1);
			glColor3f(1, 0, 0);
		}
		glFlush();
	}
	glFlush();
}

//Title screen with blinking text
void render()
{
	glClearColor(0.15f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	char rnsit[] = "RNS INSTITUTE OF TECHNOLOGY";
	renderbitmap(-150, 400, GLUT_BITMAP_TIMES_ROMAN_24, rnsit, 1, 1, 1);
	char dept[] = "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING";
	renderbitmap(-250, 300, GLUT_BITMAP_TIMES_ROMAN_24, dept, 1, 1, 1);
	char cg[] = "COMPUTER GRAPHICS MINI PROJECT ON:";
	renderbitmap(-180, 200, GLUT_BITMAP_TIMES_ROMAN_24, cg, 1, 1, 1);
	char submitted[] = "SUBMITTED BY:";
	renderbitmap(-450, -150, GLUT_BITMAP_HELVETICA_18, submitted, 1, 1, 1);
	char line[] = "_____________";
	renderbitmap(-450, -160, GLUT_BITMAP_HELVETICA_18, line, 1, 1, 1);
	char shash[] = "SHASHANK R 1RN17CS088";
	renderbitmap(-450, -200, GLUT_BITMAP_HELVETICA_18, shash, 1, 1, 1);
	char shreyas[] = "SHREYAS B 1RN17CS093";
	renderbitmap(-450, -250, GLUT_BITMAP_HELVETICA_18, shreyas, 1, 1, 1);
	char teach[] = "UNDER THE GUIDANCE OF:";
	renderbitmap(250, -150, GLUT_BITMAP_HELVETICA_18, teach, 1, 1, 1);
	char line1[] = "______________________";
	renderbitmap(250, -160, GLUT_BITMAP_HELVETICA_18, line1, 1, 1, 1);
	char mam[] = "DR. SUDHAMANI M  J";
	renderbitmap(250, -200, GLUT_BITMAP_HELVETICA_18, mam, 1, 1, 1);


	char title[] = "COVID-19 VISUALIZATION: INDIA";
	renderbitmap(-150, 0, GLUT_BITMAP_TIMES_ROMAN_24, title, 1, 1, 1);
	if (blink == false) {

		char subtitle[] = "[ Click anywhere to begin ]";
		renderbitmap(-100, -250, GLUT_BITMAP_HELVETICA_18, subtitle, 1, 1, 1);
	}
	/*
	char title1[] = "Shashank R   1RN17CS088";
	renderbitmap(-20, -400, GLUT_BITMAP_HELVETICA_12, title1, 1, 1, 1);
	char title2[] = "Shreyas B    1RN17CS093";
	renderbitmap(-20, -450, GLUT_BITMAP_HELVETICA_12, title2, 1, 1, 1);
	*/
	glFlush();
	blink = !blink;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	glutPostRedisplay();

}

//The screen containing map of India
void renderMap()
{

	char fn[] = "ind.jpg";
	texture = glInitTexture(fn);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glPointSize(5);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3f(-450, -450, 10);
	glVertex3f(-450, -220, 10);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-450, -450, 10);
	glVertex3f(-250, -450, 10);
	glEnd();
	char s1[] = "^";
	renderbitmap(-451.8, -224, GLUT_BITMAP_HELVETICA_10, s1, 1, 1, 1);
	char s2[] = ">";
	renderbitmap(-253, -453.5, GLUT_BITMAP_HELVETICA_10, s2, 1, 1, 1);
	int casesScale[20];								//0.22 and 0.65
	int loopCnt = 0;
	for (int i = 0; i <= finalcases + (finalcases / 9); i += finalcases / 9)	//initializing y axis=value		9145/9
		casesScale[loopCnt++] = i;
	int deathsScale[20];
	int loopCnt1 = 0;
	for (int i = 0; i <= finaldeath + (finaldeath / 9); i += finaldeath / 9)			//y axis for deaths			308/9
		deathsScale[loopCnt1++] = i;
	glPointSize(5);
	loopCnt = 0;
	for (int i = -450; i < -251; i += 20) {		//draw small horizontal lines+text which was initialized for cases graph
		glBegin(GL_LINES);
		glVertex3f(-450, i, 10);
		glVertex3f(-455, i, 10);
		glEnd();
		char st[100];
		_itoa(casesScale[loopCnt++], st, 10);
		glRasterPos3f(-480, i, 10);
		for (int k = 0; k < strlen(st); k++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
		}

	}
	glFlush();
	drawGraphCases(casesScale);						//dates in cases
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3f(275, -450, 10);
	glVertex3f(275, -220, 10);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(275, -450, 10);
	glVertex3f(475, -450, 10);

	glEnd();
	char s3[] = "^";
	renderbitmap(273.3, -223, GLUT_BITMAP_HELVETICA_10, s3, 1, 1, 1);
	char s4[] = ">";
	renderbitmap(473, -451.5, GLUT_BITMAP_HELVETICA_10, s4, 1, 1, 1);
	loopCnt1 = 0;
	for (int i = -450; i < -251; i += 20) {             //draw small horizontal lines+text which was initialized for deaths graph
		glBegin(GL_LINES);
		glVertex3f(275, i, 10);
		glVertex3f(270, i, 10);
		glEnd();
		char st[100];
		_itoa(deathsScale[loopCnt1++], st, 10);

		glRasterPos3f(255, i, 10);
		for (int k = 0; k < strlen(st); k++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
		}

	}
	drawGraphDeaths();									//dates in deaths


	drawMap();

	plotPoints();




}

//The screen containing state map
void renderstateMap()
{
	if (statecode != -1) {
		int imageno = statecode;
		int statecases = casesState[imageno][(casesState[imageno].size()) - 1];
		std::cout << "CasesScale " << casesState[imageno][(casesState[imageno].size()) - 1] << " " << statecases << "\n";
		auto sc = casesState[imageno].end();
		sc--;
		statecases = *sc;
		int statedeaths = deathsState[imageno][(deathsState[imageno].size()) - 1];
		std::cout << "DeathsScale " << statedeaths << "\n";
		string statename;
		if (statecode < 10)
			statename = "0" + to_string(statecode) + ".jpg";
		else
			statename = "" + to_string(statecode) + ".jpg";
		char filename[10];
		strcpy(filename, statename.c_str());
		texture = glInitTexture(filename);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glPointSize(5);
		glColor3f(1, 1, 1);
		glBegin(GL_LINES);
		glVertex3f(-450, -450, 10);
		glVertex3f(-450, -220, 10);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(-450, -450, 10);
		glVertex3f(-250, -450, 10);
		glEnd();
		char s1[] = "^";
		renderbitmap(-451.8, -224, GLUT_BITMAP_HELVETICA_10, s1, 1, 1, 1);
		char s2[] = ">";
		renderbitmap(-253, -453.5, GLUT_BITMAP_HELVETICA_10, s2, 1, 1, 1);
		glFlush();
		int casesScale[50];								//0.22 and 0.65
		int loopCnt = 0;
		float j = -1;
		if (statecases == 0)
			casesScale[loopCnt++] = 0;
		else {
			for (float i = 0; i <= (float)statecases + (float)(statecases / 9.0); i += statecases / 9.0) {
				if (i != j) {
					casesScale[loopCnt++] = i;
					j = i;
				}

			}			//y axis for deaths			308/9
		}
		std::cout << "loopcnt " << loopCnt << '\n';

		int deathsScale[50];
		int loopCnt1 = 0;
		j = -1;
		if (statedeaths == 0)
			deathsScale[loopCnt1++] = 0;
		else {
			for (float i = 0; i <= (float)statedeaths + (float)(statedeaths / 9.0); i += statedeaths / 9.0) {
				if (i != j) {
					deathsScale[loopCnt1++] = i;
					j = i;
				}

			}			//y axis for deaths			308/9
		}
		std::cout << "loopcnt1 " << loopCnt1 << '\n';
		glPointSize(5);
		loopCnt = 0;
		for (int i = -450; i < -251; i += 20) {		//draw small horizontal lines+text which was initialized for cases graph
			glBegin(GL_LINES);
			glVertex3f(-450, i, 10);
			glVertex3f(-455, i, 10);
			glEnd();
			char st[100];
			_itoa(casesScale[loopCnt++], st, 10);
			glRasterPos3f(-480, i, 10);
			for (int k = 0; k < strlen(st); k++) {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
			}

		}
		glFlush();
		drawGraphCases(casesScale);						//dates in cases
		glColor3f(1, 1, 1);
		glBegin(GL_LINES);
		glVertex3f(275, -450, 10);
		glVertex3f(275, -220, 10);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(275, -450, 10);
		glVertex3f(475, -450, 10);
		glEnd();
		char s3[] = "^";
		renderbitmap(273.3, -223, GLUT_BITMAP_HELVETICA_10, s3, 1, 1, 1);
		char s4[] = ">";
		renderbitmap(473, -451.5, GLUT_BITMAP_HELVETICA_10, s4, 1, 1, 1);
		int ploopCnt1 = loopCnt1;
		loopCnt1 = 0;
		int oldDeathVal = -1;
		for (int i = -450; i < -251; i += 20) {             //draw small horizontal lines+text which was initialized for deaths graph
			if (ploopCnt1 == 1) {
				glBegin(GL_LINES);
				glVertex3f(275, i, 10);
				glVertex3f(270, i, 10);
				glEnd();
				char st[100];
				_itoa(deathsScale[loopCnt1], st, 10);

				glRasterPos3f(255, i, 10);
				for (int k = 0; k < strlen(st); k++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
				}
				break;
			}
			else if (oldDeathVal != deathsScale[loopCnt1]) {
				glBegin(GL_LINES);
				glVertex3f(275, i, 10);
				glVertex3f(270, i, 10);
				glEnd();
				char st[100];
				_itoa(deathsScale[loopCnt1], st, 10);

				glRasterPos3f(260, i, 10);
				for (int k = 0; k < strlen(st); k++) {
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
				}
				oldDeathVal = deathsScale[loopCnt1];
			}
			loopCnt1++;


		}
		drawGraphDeaths();									//dates in deaths


		drawMap();

		plotPointsState(imageno);
		glFlush();

	}
}

//Keybboard function to close state window when ESC or 'c' is pressed
void KbeventState(unsigned char key, int x, int y) {
	if (key == 27 || key == 'c') {

		glutDestroyWindow(Statewin);
		glutCreateWindow("India");
		init();
		glutDisplayFunc(renderMap);
		glutMouseFunc(Mouseevent);
		glutDestroyWindow(oldWin);
		glutMainLoop();
	}
	else {
		std::cout << "Pinged  " << "\n";
	}
}


//Main function. Plays background music, loads the data from the datasets and initializes the OpenGL environment. 
int main()
{

	PlaySound("music.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	xRotated = yRotated = zRotated = 30.0;
	xRotated = 33;
	yRotated = 40;
	ifstream in1("cases.txt");
	ifstream in2("death.txt");
	ifstream in3("state-mid.txt");
	ifstream in4("zones.txt");
	if (!in1 || !in2 || !in3 || !in4) {
		std::cout << "Cannot open input file.\n";
		return 1;
	}
	char str[500];
	char str2[500];
	char str3[500];
	int mids[25][4];
	int zones[26][3];
	for (int i = 0; i < 26; i++) {
		deathsState[i].clear();
	}
	int row = 0;
	int row1 = 0;
	while (in1 || in3 || in4) {
		if (in3) {
			in3.getline(str3, 500);
			string inp = str3;
			int cpos = 0, dcnt = 0;
			cpos = inp.find(',');
			inp.erase(0, cpos + 1);
			cpos = inp.find(',');
			string token = inp.substr(0, cpos);
			stringstream obj(token);
			int value1 = 0;
			obj >> value1;
			//std::cout << "value x " << value1 << '\n';
			inp.erase(0, cpos + 1);
			cpos = inp.find(',');
			string token2 = inp.substr(0, cpos);
			stringstream obj1(token2);
			int value2 = 0;
			obj1 >> value2;
			inp.erase(0, cpos + 1);
			cpos = inp.find(',');
			string token3 = inp.substr(0, cpos);
			stringstream obj2(token3);
			int value3 = 0;
			obj2 >> value3;
			inp.erase(0, cpos + 1);
			cpos = inp.find(',');
			string token4 = inp.substr(0, cpos);
			stringstream obj3(token4);
			int value4 = 0;
			obj3 >> value4;
			if (value1 == 0 && value2 == 0)
				continue;
			//std::cout << "value y " << value2 << '\n';
			mids[row][0] = value1;
			mids[row][1] = value2;
			mids[row][2] = value3;
			mids[row][3] = value4;
			row++;
		}
		if (in4) {
			in4.getline(str3, 500);
			string inp = str3;
			int cpos = 0, dcnt = 0;
			cpos = inp.find(',');
			inp.erase(0, cpos + 1);
			cpos = inp.find(',');
			string token = inp.substr(0, cpos);
			stringstream obj(token);
			int value1 = 0;
			obj >> value1;
			//std::cout << "value x " << value1 << '\n';
			inp.erase(0, cpos + 1);
			cpos = inp.find(',');
			string token2 = inp.substr(0, cpos);
			stringstream obj1(token2);
			int value2 = 0;
			obj1 >> value2;
			inp.erase(0, cpos + 1);
			cpos = inp.find(',');
			string token3 = inp.substr(0, cpos);
			stringstream obj2(token3);
			int value3 = 0;
			obj2 >> value3;



			//std::cout << "value y " << value2 << '\n';
			zones[row1][0] = value1;
			zones[row1][1] = value2;
			zones[row1][2] = value3;

			row1++;
		}
		in1.getline(str, 500);
		in2.getline(str2, 500);
		string inputline = str;
		string inputline2 = str2;
		int cpos = 0, cpos2 = 0, dcnt = 0;
		while (cpos < strlen(str)) {	//reading the data between commas(text file to vector)

			cpos = inputline.find(',');
			cpos2 = inputline2.find(',');
			char tokenarr[100] = {};
			string token = inputline.substr(0, cpos);
			string token2 = inputline2.substr(0, cpos2);
			for (int z = 0; z < cpos; z++)
			{
				tokenarr[z] = str[z];
			}
			if (dcnt == 0) {
				char thedate[100] = {};
				int mc = 0, dc = 0, count = 0;
				char mon[100] = {}, day[100] = {};
				for (int i = 0; i < strlen(tokenarr); i++)
				{
					if (tokenarr[i] != '-' && count == 0)
					{
						continue;
					}
					else if (tokenarr[i] == '-')
					{
						count++;
						continue;
					}
					else if (tokenarr[i] != '-' && count == 1)
					{
						if (mc == 0) {
							mon[0] = tokenarr[i];
							mc++;
						}
						else if (mc == 1) {
							mon[1] = tokenarr[i];
							mc++;
						}
						continue;
					}
					else if (tokenarr[i] != '-' && count == 2)
					{
						if (dc == 0) {
							day[0] = tokenarr[i];
							dc++;
						}
						else if (dc == 1) {
							day[1] = tokenarr[i];
							dc++;
						}
						continue;
					}

				}
				thedate[0] = day[0];
				thedate[1] = day[1];
				thedate[2] = '/';
				thedate[3] = mon[0];
				thedate[4] = mon[1];
				for (int z = 0; z < strlen(thedate); z++)
				{
					dateschararray[datecnt][z] = thedate[z];
				}
				datecnt++;
				dates.push_back(token);
			}
			else {
				stringstream obj(token);
				int value = 0;
				obj >> value;
				casesState[dcnt - 1].push_back(value);
				stringstream obj2(token2);
				int value2 = 0;
				obj2 >> value2;
				deathsState[dcnt - 1].push_back(value2);
			}
			inputline.erase(0, cpos + 1);
			inputline2.erase(0, cpos2 + 1);
			dcnt++;
		}
		stringstream obj(inputline);
		int value = 0;
		obj >> value;
		cases.push_back(value);
		stringstream obj2(inputline2);
		int value2 = 0;
		obj2 >> value2;
		deaths.push_back(value2);
	}
	std::cout << "State data" << '\n';
	cases.pop_back();
	deaths.pop_back();
	in1.close();
	in2.close();
	in3.close();
	in4.close();
	for (int i = 0; i < 25; i++) {
		statemids[i].clear();
		statemids[i].push_back(mids[i][0]);
		statemids[i].push_back(mids[i][1]);
		statemids[i].push_back(mids[i][2]);
		statemids[i].push_back(mids[i][3]);
	}
	for (int i = 0; i < 25; i++) {
		statezones[i].clear();
		statezones[i].push_back(zones[i][0]);
		statezones[i].push_back(zones[i][1]);
		statezones[i].push_back(zones[i][2]);
	}
	auto j = cases.begin();
	auto k = deaths.begin();
	for (auto i = dates.begin(); i < dates.end(), j < cases.end(), k < deaths.end(); i++, j++, k++) {
		std::cout << *i << '\t' << *j << '\t' << *k << '\n';
		cnt++;
		finalcases = *j;
		finaldeath = *k;
	}
	for (int i = 0; i < 24; i++) {
		auto p = statemids[i].begin();
		for (; p < statemids[i].end(); p++)
			std::cout << *p << " ";
		std::cout << "\n";
	}
	for (int i = 0; i < 24; i++) {
		auto p = casesState[i].begin();
		for (; p < casesState[i].end(); p++)
			finalc[i] = *p;
		std::cout << finalc[i] << "\t";
		rankc[i] = 1;
	}
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 24; j++)
		{
			if (finalc[i] < finalc[j])
			{
				rankc[i]++;
			}
		}
	}
	for (int i = 0; i < 24; i++)
	{
		std::cout << rankc[i];
	}

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1560, 800);
	glutInitWindowPosition(0, 0);
	win = glutCreateWindow("Globe");
	init();
	char fn[] = "map.jpg";
	texture = glInitTexture(fn);
	glutDisplayFunc(render);
	glutMouseFunc(MouseeventFirst);
	glutMainLoop();

	return 0;
}