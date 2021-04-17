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
void renderMap();

int win;
using namespace std;
vector <string> dates;
vector <int> cases, deaths, statemids[25];
vector <int> casesState[26];
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
void init() {
	glOrtho(-1000 / 2, 1000 / 2, -1000 / 2, 1000 / 2, -500, 500);
}

void renderbitmap(float x, float y, void* font, char* string)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);
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



void drawImage(GLuint file, float x, float y, float w, float h, float travalue)
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

void drawImageofMap(GLuint file, float x, float y, float w, float h)
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
	glFlush();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);



}
//Plots points of both graphs together


//Displays map on screen
void drawEarth() {

		std::cout << "\nDraw earth\n";

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
		std::this_thread::sleep_for(std::chrono::milliseconds(900));
		
		glutDestroyWindow(win);
		glutCreateWindow("Maps");
		init();
		glutDisplayFunc(renderMap);
		glutMainLoop();



}
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

void plotPoints() {

	//std::cout << "\nPlot Points\n";
	//plotCases();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);

	//glLoadIdentity();
	gluOrtho2D(-41.8, 41.8, -80, 80);
	glMatrixMode(GL_PROJECTION);

	glPointSize(5);
	glColor3f(1, 0, 0);

	auto i = cases.begin();
	int j = 0;
	auto k = deaths.begin();
	int datecnt = 0;
	for (; i < cases.end(); i++, k++, j += 200 / (cnt), datecnt++) {	//draw the points cases
		glPointSize(5);
		glColor3f(1, 0, 0);
		glBegin(GL_POINTS);
		glVertex2f(j - 450.0000, *i * (200.0000 / finalcases) - 450);		//200/9145   
		glVertex2f(j + 275.0000, *k * (200.0000 / finaldeath) - 450);		//200/308
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

		int state = 0;
		for (; state < 24; state++) {
			int numofcases = casesState[state][datecnt];

			int x = statemids[state][0];

			int y = statemids[state][1];
			
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glPointSize(3 + 50 * numofcases / 3323);
			glColor4f(0, 0, 1, 0.5);
			glBegin(GL_POINTS);
			glVertex2f(x, y);
			glEnd();
			glDisable(GL_BLEND);
			glPointSize(5);
			glColor3f(0, 1, 0);
			glBegin(GL_POINTS);
			for (int s = 0; s < 24; s++) {
				glVertex2f(statemids[s][0], statemids[s][1]);
			}
			glEnd();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));


		glFlush();
	}
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
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
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


void render()

{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	drawEarth();

	glFlush();



}
void renderMap()

{

	char fn[] = "ind.jpg";
	texture = glInitTexture(fn);
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
		glRasterPos3f(-470, i, 10);
		for (int k = 0; k < strlen(st); k++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, st[k]);
		}

	}

	glFlush();
	//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	drawGraphCases(casesScale);						//dates in cases


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
	for (int i = -450; i < -251; i += 20) {             //draw small horizontal lines+text which was initialized for deaths graph
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
	drawGraphDeaths();									//dates in deaths


	drawMap();

	plotPoints();
	glFlush();



}

void Kbevent(unsigned char key, int x, int y) {
	if (key == 's') {
		start = 0;
		glutDestroyWindow(win);
		glutCreateWindow("Maps");
		init();
		glutDisplayFunc(renderMap);
		glutMainLoop();
	}

}

int main()
{
	xRotated = yRotated = zRotated = 30.0;
	xRotated = 33;
	yRotated = 40;
	ifstream in1("cases.txt");
	ifstream in2("death.txt");
	ifstream in3("state-mid.txt");
	if (!in1 || !in2 || !in3) {
		std::cout << "Cannot open input file.\n";
		return 1;
	}
	char str[500];
	char str2[500];
	char str3[500];




	int row = 0;
	while (in1 || in3) {


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
			stringstream obj1(inp);
			int value2 = 0;
			obj1 >> value2;
			if (value1 == 0 && value2 == 0)
				continue;
			//std::cout << "value y " << value2 << '\n';
			statemids[row].push_back(value1);
			statemids[row].push_back(value2);
			row++;
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
			else {
				stringstream obj(token);
				int value = 0;
				obj >> value;
				//std::cout << value << " caseState\n";
				casesState[dcnt - 1].push_back(value);

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



	}
	std::cout << "State data" << '\n';
	cases.pop_back();
	deaths.pop_back();




	in1.close();
	in2.close();
	in3.close();
	auto j = cases.begin();
	auto k = deaths.begin();
	for (auto i = dates.begin(); i < dates.end(), j < cases.end(), k < deaths.end(); i++, j++, k++) {
		std::cout << *i << '\t' << *j << '\t' << *k << '\n';
		cnt++;
		finalcases = *j;
		finaldeath = *k;
	}
	


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1560, 810);
	win = glutCreateWindow("Maps");
	init();
	char fn[] = "map.jpg";
	texture = glInitTexture(fn);
	
	glutDisplayFunc(render);
	//glutReshapeFunc(reshapeFunc);
	//glutIdleFunc(idleFunc);
	glutKeyboardFunc(Kbevent);
	glutMainLoop();




	return 0;
}
