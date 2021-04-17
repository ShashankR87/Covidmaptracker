#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <GL/glut.h>
#include <thread>
#include <chrono>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;
vector <string> dates;
vector <int> cases, deaths;
int datecnt = 0;
string datesarray[100];
char dateschararray[100][100];
int cnt = 0;
GLuint texture;


void renderbitmap(float x, float y, void* font, char* string)
{
	char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}
void plotPoints() {

	//std::cout << "\nPlot Points\n";
	//plotCases();
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);

	//glLoadIdentity();
	gluOrtho2D(-41.8, 41.8, -80, 80);
	glMatrixMode(GL_PROJECTION);
	glPointSize(5);
	glColor3f(0, 1, 0);
	glBegin(GL_POINTS);
	glVertex2f(-66, -320);
	glVertex2f(-75, 270);
	glVertex2f(-65, 210);
	glVertex2f(-85, 180);
	glVertex2f(-40, 170);
	glVertex2f(-80, 140);
	glVertex2f(-63, 126);
	glVertex2f(-110, 80);
	glVertex2f(-25, 80);
	glVertex2f(35, 55);
	glVertex2f(120, 60);
	glVertex2f(60, -10);
	glVertex2f(-10, -50);
	glVertex2f(25, 0);
	glVertex2f(-50, -10);
	glVertex2f(-120, -10);
	glVertex2f(-80, -95);
	glVertex2f(20, -75);
	glVertex2f(-40, -125);
	glVertex2f(-80, -200);
	glVertex2f(-40, -200);
	glVertex2f(-50, -280);
	glVertex2f(-100, -190);
	glVertex2f(120, -280);
	glEnd();

	glPointSize(5);
	glColor3f(1, 0, 0);

	auto i = cases.begin();
	int j = 0;
	auto k = deaths.begin();
	int datecnt = 0;
	for (; i < cases.end(); i++, k++, j += 200 / (cnt), datecnt++) {	//draw the points cases
		glColor3f(1, 0, 0);
		glBegin(GL_POINTS);
		glVertex2f(j - 450, *i * 0.05 - 450);		//200/9145   
		glVertex2f(j + 275, *k * 2.6 - 450);		//200/308
		glEnd();
		/*

		*/

		glFlush();
		glColor3f(0, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(-470 - 40, 450 + 40);
		glVertex2f(-470 + 40, 450 + 40);
		glVertex2f(-470 + 40, 450 - 40);
		glVertex2f(-470 - 40, 450 - 40);
		glEnd();
		glClear(GL_DEPTH_BUFFER_BIT);
		glColor3f(1, 1, 1);
		char buf[100] = { 0 };
		sprintf_s(buf, dateschararray[datecnt]);
		//std::cout<<dateschararray[z]<<endl;
		renderbitmap(-470, 445, GLUT_BITMAP_HELVETICA_18, buf);
		glFlush();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));


		glFlush();
	}
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

void init() {
	glOrtho(-1000 / 2, 1000 / 2, -1000 / 2, 1000 / 2, -500, 500);
}
void drawImage(GLuint file, float x, float y, float w, float h)
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glPushMatrix();
	//glTranslatef(x, y, 0.0);
	//glRotatef(angle, 0.0, 0.0, 1.0);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, file);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-5.1, -5.6);
	glTexCoord2f(0.0, 1.0); glVertex2f(-5.1, 4.7);
	glTexCoord2f(1.0, 1.0); glVertex2f(4.8, 4.7);
	glTexCoord2f(1.0, 0.0); glVertex2f(4.8, -5.6);
	glEnd();

	glPopMatrix();
}
void drawGraphCases(int casesScale[]) {  //cases
	auto i = cases.begin();
	auto j = 0;
	glColor3f(1, 1, 1);
	char str[] = "Cases";
	glRasterPos2f(-490, -350);
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
		/*
		glBegin(GL_POINTS);
		glVertex2f(j - 450, *i*0.05 - 450);
		glEnd();
		*/

		if (z % 11 == 0) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex2f(j - 450, -450);
			glVertex2f(j - 450, -455);
			glEnd();
			char buf[100] = { 0 };
			sprintf_s(buf, dateschararray[z]);
			//std::cout<<dateschararray[z]<<endl;
			renderbitmap(j - 450, -465, GLUT_BITMAP_HELVETICA_10, buf);



			glColor3f(1, 0, 0);
		}


		glFlush();
		//std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
	/*
	glPointSize(5);
	glBegin(GL_LINE_STRIP);
	i = cases.begin();
	j = 0;
	for (; i < cases.end(); i++, j += 200 / (cnt)) {		//lines bw cases
		glVertex2f(j - 450, *i*0.05 - 450);
	}
	glEnd();
	*/
	glFlush();
}

//Plots points of both graphs together


void plotCases() {
	
	glPointSize(5);
	glColor3f(0, 1, 0);

	glBegin(GL_POINTS);
	glVertex2f(-66, -320);
	glVertex2f(-75, 270);
	glVertex2f(-65, 210);
	glVertex2f(-85, 180);
	glVertex2f(-40, 170);
	glVertex2f(-80, 140);
	glVertex2f(-63, 126);
	glVertex2f(-110, 80);
	glVertex2f(-25, 80);
	glVertex2f(35, 55);
	glVertex2f(120, 60);
	glVertex2f(60, -10);
	glVertex2f(-10, -50);
	glVertex2f(25, 0);
	glVertex2f(-50, -10);
	glVertex2f(-120, -10);
	glVertex2f(-80, -95);
	glVertex2f(20, -75);
	glVertex2f(-40, -125);
	glVertex2f(-80, -200);
	glVertex2f(-40, -200);
	glVertex2f(-50, -280);
	glVertex2f(-100, -190);
	glVertex2f(120, -280);
	glEnd();
	glFlush();

}

void drawGraphDeaths() 
	
{
	plotCases();
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
		/*
		glBegin(GL_POINTS);
		glVertex2f(j + 275, *i * 2.5 - 450);
		glEnd();
		*/

		if (z % 11 == 0) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex2f(j + 275, -450);
			glVertex2f(j + 275, -455);
			glEnd();
			char buf[100] = { 0 };
			sprintf_s(buf, dateschararray[z]);
			renderbitmap(j + 275, -465, GLUT_BITMAP_HELVETICA_10, buf);



			glColor3f(1, 0, 0);
		}



		glFlush();
		//std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
	/*
	glPointSize(5);
	glBegin(GL_LINE_STRIP);
	i = deaths.begin();
	j = 0;
	for (; i < deaths.end(); i++, j += 200 / (cnt)) {
		glVertex2f(j + 275, *i * 2.5 - 450);
	}
	glEnd();

	*/
	glFlush();
}

//Displays map on screen
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

	drawImage(texture, 0, 0, 3, 4);


	glutSwapBuffers();
	glEnd();
	glFlush();
	plotPoints();
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

	int casesScale[20];
	int loopCnt = 0;
	for (int i = 0; i < 3500; i += 380)	//initializing y axis=value
		casesScale[loopCnt++] = i;
	int deathsScale[20];
	int loopCnt1 = 0;
	for (int i = 0; i < 81; i+=8)			//y axis for deaths
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
		glRasterPos3f(-470, i, 10);
		for (int k = 0; k < strlen(st); k++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
		}

	}

	glFlush();
	//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	drawGraphCases(casesScale);


	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3f(275, -450, 10);
	glVertex3f(275, -250, 10);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(275, -450, 10);
	glVertex3f(475, -450, 10);

	glEnd();
	loopCnt1 = 0;
	for (int i = -450; i < -249; i += 20) {             //draw small horizontal lines+text which was initialized for deaths graph
		glBegin(GL_LINES);
		glVertex3f(275, i, 10);
		glVertex3f(270, i, 10);
		glEnd();
		char st[100];
		_itoa(deathsScale[loopCnt1++], st, 10);

		glRasterPos3f(260, i, 10);
		for (int k = 0; k < strlen(st); k++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
		}

	}
	drawGraphDeaths();

	plotPoints();
	drawMap();

	
	glFlush();



	/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(45.0, w / h, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -15);

	drawImage(texture, 0, 0, 3, 4);

	
	glutSwapBuffers();
	glEnd();
	*/
	glFlush();
	
}
int main(int argc, char* argv[])
{

	ifstream in1("cases.txt");
	ifstream in2("death.txt");

	if (!in1 || !in2) {
		std::cout << "Cannot open input file.\n";
		return 1;
	}
	char str[500];
	char str2[500];

	while (in1) {
		
		in1.getline(str, 500);
		in2.getline(str2, 500);
		string inputline = str;
		string inputline2 = str2;
		
		int cpos = 0,cpos2=0, dcnt = 0;
		while (cpos < strlen(str)) {	//reading the data between commas(text file to vector)
			
			cpos = inputline.find(',');
			cpos2 = inputline2.find(',');
			char tokenarr[100] = {};
			string token = inputline.substr(0, cpos);
			for (int z = 0; z < cpos; z++)
			{
				tokenarr[z] = str[z];
			}


			if (dcnt == 0) {
				//std::cout << "yaay" << tokenarr << endl;
				char thedate[100] = {};
				int mc = 0, dc = 0, count = 0;
				char mon[100] = {}, day[100] = {};
				for (int i = 0; i < strlen(tokenarr); i++)
				{
					//std::cout << "the tok[i] is: " <<tokenarr[i] << "mc=" <<strlen(mon)<<endl;
					if (tokenarr[i] != '-' && count == 0)
					{
						continue;
					}
					else if (tokenarr[i] == '-')
					{
						count++;
						//std::cout << "the count is: " << count <<endl;
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
						//std::cout << "monis" << mon;
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
						//std::cout << "dayis" << day;
						continue;
					}

				}
				thedate[0] = day[0];
				thedate[1] = day[1];
				thedate[2] = '/';
				thedate[3] = mon[0];
				thedate[4] = mon[1];
				//thedate[5] = '\0';


				for (int z = 0; z < strlen(thedate); z++)
				{
					dateschararray[datecnt][z] = thedate[z];
					//cout << dateschararray[datecnt] << endl;
				}
				datecnt++;


				//datesarray[datecnt++] = token;
				dates.push_back(token);
			}
			/*
			if (dcnt == 7) {
				
				stringstream obj(token);	//string to integer(check later lines)
				int value = 0;
				obj >> value;
				deaths.push_back(value);
				

			}
			*/

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
		std::cout << "valvsl " << value<<'\n';


	}
	cases.pop_back();
	deaths.pop_back();

	in1.close();
	in2.close();
	std::cout << "Date:\t Cases: \t Deaths: \n";
	auto j = cases.begin();
	auto k = deaths.begin();
	int l = 0;
	for (auto i = dates.begin(); i < dates.end(), j < cases.end(), k < deaths.end(); i++, j++, k++) {
		std::cout << *i << '\t' << *j << '\t' << *k << '\n';
		cnt++;
	}
	for (int i = 0; i <= 28; i++) {
		std::cout << dateschararray[i];

	}


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1560,810);
	glutCreateWindow("Applying Textures");
	init();
	char fn[] = "ind.jpg";
	texture = glInitTexture(fn);
	glutDisplayFunc(render);
	glutMainLoop();

	return 0;
}





/*
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <GL/glut.h>
#include <thread>
#include <chrono>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;
vector <string> dates;
vector <int> cases, deaths;
int datecnt = 0;
string datesarray[100];
char dateschararray[100][100];
int cnt = 0;
GLuint texture;


void renderbitmap(float x, float y, void* font, char* string)
{
	char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}
GLuint glInitTexture(char* filename)
{
	GLuint t = 0;
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

	glGenTextures(1, &t);
	glBindTexture(GL_TEXTURE_2D, t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//unsigned char data[] = { 255, 0, 0, 255 };
	if (data)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else
		std::cout << "fail";
	return t;
}

void init() {
	glOrtho(-1000 / 2, 1000 / 2, -1000 / 2, 1000 / 2, -500, 500);
}
void drawImage(GLuint file, float x, float y, float w, float h)
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glPushMatrix();
	//glTranslatef(x, y, 0.0);
	//glRotatef(angle, 0.0, 0.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, file);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-6, 6, 0.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(-6, -6, 0.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(2, -6, 0.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(2, 6, 0.0f);
	glEnd();

	glPopMatrix();
}
void drawGraphCases(int casesScale[]) {  //cases
	auto i = cases.begin();
	auto j = 0;
	glColor3f(1, 1, 1);
	char str[] = "Cases";
	glRasterPos2f(-490, -350);
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

		glBegin(GL_POINTS);
		glVertex2f(j - 450, *i - 450);
		glEnd();


		if (z % 4 == 0) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex2f(j - 450, -450);
			glVertex2f(j - 450, -455);
			glEnd();
			char buf[100] = { 0 };
			sprintf_s(buf, dateschararray[z]);
			//std::cout<<dateschararray[z]<<endl;
			renderbitmap(j - 450, -465, GLUT_BITMAP_HELVETICA_10, buf);



			glColor3f(1, 0, 0);
		}


		glFlush();
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}

	glPointSize(5);
	glBegin(GL_LINE_STRIP);
	i = cases.begin();
	j = 0;
	for (; i < cases.end(); i++, j += 200 / (cnt)) {		//lines bw cases
		glVertex2f(j - 450, *i - 450);
	}
	glEnd();

	glFlush();
}

void drawGraphDeaths() {
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
		glBegin(GL_POINTS);
		glVertex2f(j + 275, *i * 49 - 450);
		glEnd();


		if (z % 4 == 0) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex2f(j + 275, -450);
			glVertex2f(j + 275, -455);
			glEnd();
			char buf[100] = { 0 };
			sprintf_s(buf, dateschararray[z]);
			renderbitmap(j + 275, -465, GLUT_BITMAP_HELVETICA_10, buf);



			glColor3f(1, 0, 0);
		}



		glFlush();
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}

	glPointSize(5);
	glBegin(GL_LINE_STRIP);
	i = deaths.begin();
	j = 0;
	for (; i < deaths.end(); i++, j += 200 / (cnt)) {
		glVertex2f(j + 275, *i * 49 - 450);
	}
	glEnd();


	glFlush();
}

void render()

{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnable(GL_DEPTH_TEST);




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
	int casesScale[20];
	int loopCnt = 0;
	for (int i = 0; i < 200; i += 20)	//initializing y axis=value
		casesScale[loopCnt++] = i;
	int deathsScale[5];
	int loopCnt1 = 0;
	for (int i = 0; i < 5; i++)			//y axis for deaths
		deathsScale[i] = i;
	glPointSize(5);
	loopCnt = 0;
	for (int i = -450; i < -251; i += 20) {		//draw small horizontal lines+text which was initialized
		glBegin(GL_LINES);
		glVertex3f(-450, i, 10);
		glVertex3f(-455, i, 10);
		glEnd();
		char st[10];
		_itoa(casesScale[loopCnt++], st, 10);
		glRasterPos3f(-465, i, 10);
		for (int k = 0; k < strlen(st); k++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
		}

	}

	glFlush();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	drawGraphCases(casesScale);


	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3f(275, -450, 10);
	glVertex3f(275, -250, 10);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(275, -450, 10);
	glVertex3f(475, -450, 10);

	glEnd();
	loopCnt1 = 0;
	for (int i = -450; i < -249; i += 50) {
		glBegin(GL_LINES);
		glVertex3f(275, i, 10);
		glVertex3f(270, i, 10);
		glEnd();
		char st[10];
		_itoa(deathsScale[loopCnt1++], st, 10);

		glRasterPos3f(260, i, 10);
		for (int k = 0; k < strlen(st); k++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
		}

	}
	drawGraphDeaths();

	glFlush();




	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(45.0, w / h, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -15);

	drawImage(texture, 0, 0, 3, 4);


	glutSwapBuffers();
	glEnd();

	glFlush();
}
int main(int argc, char* argv[])
{

	ifstream in("k.txt");

	if (!in) {
		std::cout << "Cannot open input file.\n";
		return 1;
	}
	char str[255];

	while (in) {

		in.getline(str, 255);
		string inputline = str;

		int cpos = 0, dcnt = 0;
		while (cpos < strlen(str)) {	//reading the data between commas(text file to vector)

			cpos = inputline.find(',');
			char tokenarr[100] = {};
			string token = inputline.substr(0, cpos);
			for (int z = 0; z < cpos; z++)
			{
				tokenarr[z] = str[z];
			}


			if (dcnt == 0) {
				//std::cout << "yaay" << tokenarr << endl;
				char thedate[100] = {};
				int mc = 0, dc = 0, count = 0;
				char mon[100] = {}, day[100] = {};
				for (int i = 0; i < strlen(tokenarr); i++)
				{
					//std::cout << "the tok[i] is: " <<tokenarr[i] << "mc=" <<strlen(mon)<<endl;
					if (tokenarr[i] != '-' && count == 0)
					{
						continue;
					}
					else if (tokenarr[i] == '-')
					{
						count++;
						//std::cout << "the count is: " << count <<endl;
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
						//std::cout << "monis" << mon;
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
						//std::cout << "dayis" << day;
						continue;
					}

				}
				thedate[0] = day[0];
				thedate[1] = day[1];
				thedate[2] = '/';
				thedate[3] = mon[0];
				thedate[4] = mon[1];
				//thedate[5] = '\0';


				for (int z = 0; z < strlen(thedate); z++)
				{
					dateschararray[datecnt][z] = thedate[z];
					//cout << dateschararray[datecnt] << endl;
				}
				datecnt++;


				//datesarray[datecnt++] = token;
				dates.push_back(token);
			}
			if (dcnt == 7) {
				stringstream obj(token);	//string to integer(check later lines)
				int value = 0;
				obj >> value;
				deaths.push_back(value);
			}


			inputline.erase(0, cpos + 1);
			dcnt++;
		}
		stringstream obj(inputline);
		int value = 0;
		obj >> value;
		cases.push_back(value);


	}
	cases.pop_back();

	in.close();
	std::cout << "Date:\t Cases: \t Deaths: \n";
	auto j = cases.begin();
	auto k = deaths.begin();
	int l = 0;
	for (auto i = dates.begin(); i < dates.end(), j < cases.end(), k < deaths.end(); i++, j++, k++) {
		std::cout << *i << '\t' << *j << '\t' << *k << '\n';
		cnt++;
	}
	for (int i = 0; i <= 28; i++) {
		std::cout << dateschararray[i];

	}


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1560, 810);
	glutCreateWindow("Applying Textures");
	init();
	char fn[] = "Cat03.jpg";
	texture = glInitTexture(fn);
	glutDisplayFunc(render);
	glutMainLoop();

	return 0;
}








/*
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <GL/glut.h>
#include <thread>
#include <chrono>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
vector <string> dates;
vector <int> cases, deaths;
int datecnt = 0;
string datesarray[100];
char dateschararray[100][100];
int cnt = 0;

GLuint texture;
void renderbitmap(float x, float y, void* font, char* string)
{
	char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

GLuint glInitTexture(char* filename)
{
	GLuint t = 0;
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

	glGenTextures(1, &t);
	glBindTexture(GL_TEXTURE_2D, t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//unsigned char data[] = { 255, 0, 0, 255 };
	if (data)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else
		std::cout << "fail";
	return t;
}
void init() {
	glOrtho(-1000/2, 1000/2, -1000/2, 1000/2, -500, 500);
}
void drawImage(GLuint file,
	float x,
	float y,
	float w,
	float h
	)
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glPushMatrix();
	//glTranslatef(x, y, 0.0);
	//glRotatef(angle, 0.0, 0.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, file);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-6, -6, 0.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(-6, 6, 0.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(2, 6, 0.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(2,-6, 0.0f);
	glEnd();

	glPopMatrix();
}




void drawGraphCases(int casesScale[]) {  //cases
	auto i = cases.begin();
	auto j = 0;
	glColor3f(1, 1, 1);
	char str[] = "Cases";
	glRasterPos3f(-490, -350,10);
	for (int k = 0; k < strlen(str); k++) {	//cases string
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[k]);
	}

	char st[] = "Dates";
	glRasterPos3f(-365, -485,10);
	for (int k = 0; k < strlen(st); k++) {		//string dates
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
	}
	glColor3f(1, 0, 0);
	glPointSize(10);


	for (int z = 0; i < cases.end(); i++, j += 200 / (cnt), z++) {	//draw the points cases

		glBegin(GL_POINTS);
		glVertex3f(j - 450, *i - 450,10);
		glEnd();


		if (z % 4 == 0) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex3f(j - 450, -450,10);
			glVertex3f(j - 450, -455,10);
			glEnd();
			char buf[100] = { 0 };
			sprintf_s(buf, dateschararray[z]);
			//std::cout<<dateschararray[z]<<endl;
			renderbitmap(j - 450, -465, GLUT_BITMAP_HELVETICA_10, buf);



			glColor3f(1, 0, 0);
		}


		glFlush();
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}

	glPointSize(5);
	glBegin(GL_LINE_STRIP);
	i = cases.begin();
	j = 0;
	for (; i < cases.end(); i++, j += 200 / (cnt)) {		//lines bw cases
		glVertex3f(j - 450, *i - 450,10);
	}
	glEnd();

	glFlush();
}

void drawGraphDeaths() {
	auto i = deaths.begin();
	auto j = 0;
	glColor3f(1, 1, 1);
	char str[] = "Deaths";
	glRasterPos3f(230, -350,10);
	for (int k = 0; k < strlen(str); k++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[k]);
	}
	char st[] = "Dates";
	glRasterPos3f(360, -485,10);
	for (int k = 0; k < strlen(st); k++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
	}
	glColor3f(1, 0, 0);
	glPointSize(10);


	for (int z = 0; i < deaths.end(); i++, j += 200 / (cnt), z++) {
		glBegin(GL_POINTS);
		glVertex3f(j + 275, *i * 49 - 450,10);
		glEnd();


		if (z % 4 == 0) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex3f(j + 275, -450,10);
			glVertex3f(j + 275, -455,10);
			glEnd();
			char buf[100] = { 0 };
			sprintf_s(buf, dateschararray[z]);
			renderbitmap(j + 275, -465, GLUT_BITMAP_HELVETICA_10, buf);



			glColor3f(1, 0, 0);
		}



		glFlush();
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}

	glPointSize(5);
	glBegin(GL_LINE_STRIP);
	i = deaths.begin();
	j = 0;
	for (; i < deaths.end(); i++, j += 200 / (cnt)) {
		glVertex3f(j + 275, *i * 49 - 450,10);
	}
	glEnd();


	glFlush();
}





void render()

{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	glEnable(GL_DEPTH_TEST);
	



	glPointSize(5);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3f(-450, -450,10);
	glVertex3f(-450, -250,10);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-450, -450,10);
	glVertex3f(-250, -450,10);

	glEnd();
	int casesScale[20];
	int loopCnt = 0;
	for (int i = 0; i < 200; i += 20)	//initializing y axis=value
		casesScale[loopCnt++] = i;
	int deathsScale[5];
	int loopCnt1 = 0;
	for (int i = 0; i < 5; i++)			//y axis for deaths
		deathsScale[i] = i;
	glPointSize(5);
	loopCnt = 0;
	for (int i = -450; i < -251; i += 20) {		//draw small horizontal lines+text which was initialized
		glBegin(GL_LINES);
		glVertex3f(-450, i,10);
		glVertex3f(-455, i,10);
		glEnd();
		char st[10];
		_itoa(casesScale[loopCnt++], st, 10);
		glRasterPos3f(-465, i,10);
		for (int k = 0; k < strlen(st); k++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
		}

	}

	glFlush();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	drawGraphCases(casesScale);


	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3f(275, -450,10);
	glVertex3f(275, -250,10);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(275, -450,10);
	glVertex3f(475, -450,10);

	glEnd();
	loopCnt1 = 0;
	for (int i = -450; i < -249; i += 50) {
		glBegin(GL_LINES);
		glVertex3f(275, i,10);
		glVertex3f(270, i,10);
		glEnd();
		char st[10];
		_itoa(deathsScale[loopCnt1++], st, 10);

		glRasterPos3f(260, i,10);
		for (int k = 0; k < strlen(st); k++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
		}

	}
	drawGraphDeaths();

	glFlush();




	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(45.0, w / h, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -15);

	drawImage(texture, 0, 0, 3,4 );
	
	
	glutSwapBuffers();
	glEnd();
	
	glFlush();
}

int main(int argc, char* argv[])
{
	ifstream in("k.txt");

	if (!in) {
		std::cout << "Cannot open input file.\n";
		return 1;
	}
	char str[255];

	while (in) {

		in.getline(str, 255);
		string inputline = str;

		int cpos = 0, dcnt = 0;
		while (cpos < strlen(str)) {	//reading the data between commas(text file to vector)

			cpos = inputline.find(',');
			char tokenarr[100] = {};
			string token = inputline.substr(0, cpos);
			for (int z = 0; z < cpos; z++)
			{
				tokenarr[z] = str[z];
			}


			if (dcnt == 0) {
				//std::cout << "yaay" << tokenarr << endl;
				char thedate[100] = {};
				int mc = 0, dc = 0, count = 0;
				char mon[100] = {}, day[100] = {};
				for (int i = 0; i < strlen(tokenarr); i++)
				{
					//std::cout << "the tok[i] is: " <<tokenarr[i] << "mc=" <<strlen(mon)<<endl;
					if (tokenarr[i] != '-' && count == 0)
					{
						continue;
					}
					else if (tokenarr[i] == '-')
					{
						count++;
						//std::cout << "the count is: " << count <<endl;
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
						//std::cout << "monis" << mon;
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
						//std::cout << "dayis" << day;
						continue;
					}

				}
				thedate[0] = day[0];
				thedate[1] = day[1];
				thedate[2] = '/';
				thedate[3] = mon[0];
				thedate[4] = mon[1];
				//thedate[5] = '\0';


				for (int z = 0; z < strlen(thedate); z++)
				{
					dateschararray[datecnt][z] = thedate[z];
					//cout << dateschararray[datecnt] << endl;
				}
				datecnt++;


				//datesarray[datecnt++] = token;
				dates.push_back(token);
			}
			if (dcnt == 7) {
				stringstream obj(token);	//string to integer(check later lines)
				int value = 0;
				obj >> value;
				deaths.push_back(value);
			}


			inputline.erase(0, cpos + 1);
			dcnt++;
		}
		stringstream obj(inputline);
		int value = 0;
		obj >> value;
		cases.push_back(value);


	}
	cases.pop_back();

	in.close();
	std::cout << "Date:\t Cases: \t Deaths: \n";
	auto j = cases.begin();
	auto k = deaths.begin();
	int l = 0;
	for (auto i = dates.begin(); i < dates.end(), j < cases.end(), k < deaths.end(); i++, j++, k++) {
		std::cout << *i << '\t' << *j << '\t' << *k << '\n';
		cnt++;
	}
	for (int i = 0; i <= 28; i++) {
		std::cout << dateschararray[i];

	}


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Applying Textures");
	init();
	char fn[] = "Cat03.jpg";
	texture = glInitTexture(fn);
	glutDisplayFunc(render);

	

	glutMainLoop();
	return 0;
}
*/

/*
using namespace std;
vector <string> dates;
vector <int> cases, deaths;
int datecnt = 0;
string datesarray[100];
char dateschararray[100][100];
int cnt = 0;

GLuint glInitTexture(char* filename)
{
	GLuint t = 0;
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

	glGenTextures(1, &t);
	glBindTexture(GL_TEXTURE_2D, t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//unsigned char data[] = { 255, 0, 0, 255 };
	if (data)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else
		std::cout << "fail";
	return t;
}

void drawImage(GLuint file,
	float x,
	float y,
	float w,
	float h,
	float angle)
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glPushMatrix();
	//glTranslatef(x, y, 0.0);
	//glRotatef(angle, 0.0, 0.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, file);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(x, y, 0.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(x, y + h, 0.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(x + w, y + h, 0.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(x + w, y, 0.0f);
	glEnd();

	glPopMatrix();
}


void renderbitmap(float x, float y, void* font, char* string)
{
	char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}


void init() {
	gluOrtho2D(-500, 500, -500, 500);
	glClearColor(0, 0, 0.1, 0);
}

void drawGraphCases(int casesScale[]) {  //cases
	auto i = cases.begin();
	auto j = 0;
	glColor3f(1, 1, 1);
	char str[] = "Cases";
	glRasterPos2f(-490, -350);
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

		glBegin(GL_POINTS);
		glVertex2f(j - 450, *i - 450);
		glEnd();


		if (z % 4 == 0) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex2f(j - 450, -450);
			glVertex2f(j - 450, -455);
			glEnd();
			char buf[100] = { 0 };
			sprintf_s(buf, dateschararray[z]);
			//std::cout<<dateschararray[z]<<endl;
			renderbitmap(j - 450, -465, GLUT_BITMAP_HELVETICA_10, buf);



			glColor3f(1, 0, 0);
		}


		glFlush();
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}

	glPointSize(5);
	glBegin(GL_LINE_STRIP);
	i = cases.begin();
	j = 0;
	for (; i < cases.end(); i++, j += 200 / (cnt)) {		//lines bw cases
		glVertex2f(j - 450, *i - 450);
	}
	glEnd();

	glFlush();
}

void drawGraphDeaths() {
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
		glBegin(GL_POINTS);
		glVertex2f(j + 275, *i * 49 - 450);
		glEnd();


		if (z % 4 == 0) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex2f(j + 275, -450);
			glVertex2f(j + 275, -455);
			glEnd();
			char buf[100] = { 0 };
			sprintf_s(buf, dateschararray[z]);
			renderbitmap(j + 275, -465, GLUT_BITMAP_HELVETICA_10, buf);



			glColor3f(1, 0, 0);
		}



		glFlush();
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}

	glPointSize(5);
	glBegin(GL_LINE_STRIP);
	i = deaths.begin();
	j = 0;
	for (; i < deaths.end(); i++, j += 200 / (cnt)) {
		glVertex2f(j + 275, *i * 49 - 450);
	}
	glEnd();


	glFlush();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(45.0, w / h, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -15);

	drawImage(texture, 0.0f, 0.0f, 4.0f, 4.0f, 0.0);

	glutSwapBuffers();
	glEnd();
	glFlush();





	//glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(-450, -450);
	glVertex2f(-450, -250);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-450, -450);
	glVertex2f(-250, -450);

	glEnd();
	int casesScale[20];
	int loopCnt = 0;
	for (int i = 0; i < 200; i += 20)	//initializing y axis=value
		casesScale[loopCnt++] = i;
	int deathsScale[5];
	int loopCnt1 = 0;
	for (int i = 0; i < 5; i++)			//y axis for deaths
		deathsScale[i] = i;
	glPointSize(5);
	loopCnt = 0;
	for (int i = -450; i < -251; i += 20) {		//draw small horizontal lines+text which was initialized
		glBegin(GL_LINES);
		glVertex2f(-450, i);
		glVertex2f(-455, i);
		glEnd();
		char st[10];
		_itoa(casesScale[loopCnt++], st, 10);
		glRasterPos2f(-465, i);
		for (int k = 0; k < strlen(st); k++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
		}

	}

	glFlush();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	drawGraphCases(casesScale);


	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(275, -450);
	glVertex2f(275, -250);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(275, -450);
	glVertex2f(475, -450);

	glEnd();
	loopCnt1 = 0;
	for (int i = -450; i < -249; i += 50) {
		glBegin(GL_LINES);
		glVertex2f(275, i);
		glVertex2f(270, i);
		glEnd();
		char st[10];
		_itoa(deathsScale[loopCnt1++], st, 10);

		glRasterPos2f(260, i);
		for (int k = 0; k < strlen(st); k++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
		}





	}
	drawGraphDeaths();




	






	glFlush();
}
int main()
{

	ifstream in("k.txt");

	if (!in) {
		std::cout << "Cannot open input file.\n";
		return 1;
	}
	char str[255];

	while (in) {

		in.getline(str, 255);
		string inputline = str;

		int cpos = 0, dcnt = 0;
		while (cpos < strlen(str)) {	//reading the data between commas(text file to vector)

			cpos = inputline.find(',');
			char tokenarr[100] = {};
			string token = inputline.substr(0, cpos);
			for (int z = 0; z < cpos; z++)
			{
				tokenarr[z] = str[z];
			}


			if (dcnt == 0) {
				//std::cout << "yaay" << tokenarr << endl;
				char thedate[100] = {};
				int mc = 0, dc = 0, count = 0;
				char mon[100] = {}, day[100] = {};
				for (int i = 0; i < strlen(tokenarr); i++)
				{
					//std::cout << "the tok[i] is: " <<tokenarr[i] << "mc=" <<strlen(mon)<<endl;
					if (tokenarr[i] != '-' && count == 0)
					{
						continue;
					}
					else if (tokenarr[i] == '-')
					{
						count++;
						//std::cout << "the count is: " << count <<endl;
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
						//std::cout << "monis" << mon;
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
						//std::cout << "dayis" << day;
						continue;
					}

				}
				thedate[0] = day[0];
				thedate[1] = day[1];
				thedate[2] = '/';
				thedate[3] = mon[0];
				thedate[4] = mon[1];
				//thedate[5] = '\0';


				for (int z = 0; z < strlen(thedate); z++)
				{
					dateschararray[datecnt][z] = thedate[z];
					//cout << dateschararray[datecnt] << endl;
				}
				datecnt++;


				//datesarray[datecnt++] = token;
				dates.push_back(token);
			}
			if (dcnt == 7) {
				stringstream obj(token);	//string to integer(check later lines)
				int value = 0;
				obj >> value;
				deaths.push_back(value);
			}


			inputline.erase(0, cpos + 1);
			dcnt++;
		}
		stringstream obj(inputline);
		int value = 0;
		obj >> value;
		cases.push_back(value);


	}
	cases.pop_back();

	in.close();
	std::cout << "Date:\t Cases: \t Deaths: \n";
	auto j = cases.begin();
	auto k = deaths.begin();
	int l = 0;
	for (auto i = dates.begin(); i < dates.end(), j < cases.end(), k < deaths.end(); i++, j++, k++) {
		std::cout << *i << '\t' << *j << '\t' << *k << '\n';
		cnt++;
	}
	for (int i = 0; i <= 28; i++) {
		std::cout << dateschararray[i];

	}


	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(1500, 800);
	glutCreateWindow("Graph");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
*/