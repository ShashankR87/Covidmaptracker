#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <GL/glut.h>
#include <thread>
#include <chrono>

using namespace std;
vector <string> dates;
vector <int> cases, deaths;
int datecnt = 0;
string datesarray[100];
char dateschararray[100][100];
int cnt = 0;


void renderbitmap(float x, float y, void *font, char *string)
{
	char *c;
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


	for (int z=0; i < cases.end(); i++, j += 200 / (cnt),z++) {	//draw the points cases

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
			sprintf_s(buf,dateschararray[z]);
			//std::cout<<dateschararray[z]<<endl;
			renderbitmap(j-450, -465, GLUT_BITMAP_HELVETICA_10,buf );


		
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


	for (int z=0; i < deaths.end(); i++, j += 200 / (cnt),z++) {
		glBegin(GL_POINTS);
		glVertex2f(j + 275, *i * 49 - 450);
		glEnd();


		if (z % 4 == 0) {
			glColor3f(1, 1, 1);
			glBegin(GL_LINES);
			glVertex2f(j +275, -450);
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
	glClear(GL_COLOR_BUFFER_BIT);
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
				int mc = 0, dc = 0,count=0;
				char mon[100] = {}, day[100] = {};
				for (int i = 0; i < strlen(tokenarr); i++)
				{
					//std::cout << "the tok[i] is: " <<tokenarr[i] << "mc=" <<strlen(mon)<<endl;
					if (tokenarr[i] != '-'&&count == 0)
					{
						continue;
					}
					else if (tokenarr[i] == '-')
					{
						count++;
						//std::cout << "the count is: " << count <<endl;
						continue;
					}
					else if (tokenarr[i] != '-'&&count == 1)
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
					else if (tokenarr[i] != '-'&&count == 2)
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
	int l=0;
	for (auto i = dates.begin(); i < dates.end(), j < cases.end(), k < deaths.end(); i++, j++, k++) {
		std::cout << *i << '\t' << *j << '\t' << *k <<'\n';
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



