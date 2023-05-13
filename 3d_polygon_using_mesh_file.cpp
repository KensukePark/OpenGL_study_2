#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <GL/glut.h>
#include <random>
using namespace std;

void Display() {
	string line;
	int LineNum = 0;
	int VertNum = 0; //Vertex �迭�� ���� ����
	int FaceNum = 0; //Face �迭�� ���� ����
	int totV; //ù��° �� Vertex �� ���� ����
	int totF; //ù��° �� Face �� ���� ����
	float VerX[10443];
	float VerY[10443];
	float VerZ[10443];
	int FV1[20882];
	int FV2[20882];
	int FV3[20882];

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> dis(0, 1); 
	//0���� 1������ �Ǽ� ������ ����	
	
	ifstream myfile("sharp_sphere.off");
	while (!myfile.eof())
	{

		getline(myfile, line, '\n');
		if (line[0] == '\0') //�������� ������ Ż��
		{
			break;
		}
		if (LineNum == 1) //1��° line ���� ��
		{
			istringstream ss(line);
			string stringBuffer;
			vector<string> x;
			x.clear();
			while (getline(ss, stringBuffer, ' ')) //����� ����
			{
				x.push_back(stringBuffer);
			}
			totV = stoi(x[0]);
			totF = stoi(x[1]);
		}
		if (line[0] == '3' && line[1] == ' ')
		{
			istringstream ss(line);
			string stringBuffer;
			vector<string> face;
			face.clear();
			while (getline(ss, stringBuffer, ' '))
			{
				face.push_back(stringBuffer);
			}
			int temp1 = stoi(face[1]);
			int temp2 = stoi(face[2]);
			int temp3 = stoi(face[3]);
			FV1[FaceNum] = temp1;
			FV2[FaceNum] = temp2;
			FV3[FaceNum] = temp3;
			FaceNum++;
		}
		else if (line[1] == '.')
		{

			istringstream ss(line);
			string stringBuffer;
			vector<string> ver_p;
			ver_p.clear();
			while (getline(ss, stringBuffer, ' '))
			{
				ver_p.push_back(stringBuffer);
			}
			float temp1 = stof(ver_p[0]);
			float temp2 = stof(ver_p[1]);
			float temp3 = stof(ver_p[2]);

			VerX[VertNum] = temp1;
			VerY[VertNum] = temp2;
			VerZ[VertNum] = temp3; \
				VertNum++;
		}
		else if (line[2] == '.')
		{

			istringstream ss(line);
			string stringBuffer;
			vector<string> ver_n;
			ver_n.clear();
			while (getline(ss, stringBuffer, ' '))
			{
				ver_n.push_back(stringBuffer);
			}
			float temp1 = stof(ver_n[0]);
			float temp2 = stof(ver_n[1]);
			float temp3 = stof(ver_n[2]);

			VerX[VertNum] = temp1;
			VerY[VertNum] = temp2;
			VerZ[VertNum] = temp3;
			VertNum++;
		}
		LineNum++;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	gluLookAt(20, 20, 20, 0, 0, 0, 0, 1, 0);
	for (int i = 0; i<20882; i++)
	{
		glBegin(GL_POLYGON);
		glColor3f(dis(gen), dis(gen), dis(gen)); //Polygon�� ���� ����������
		glVertex3f(VerX[FV1[i]], VerY[FV1[i]], VerZ[FV1[i]]);
		glVertex3f(VerX[FV2[i]], VerY[FV2[i]], VerZ[FV2[i]]);
		glVertex3f(VerX[FV3[i]], VerY[FV3[i]], VerZ[FV3[i]]);	
	}
	glEnd();
	glFlush();

}
int main(int argc, char** argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutCreateWindow("hw4_2");
	glutDisplayFunc(Display);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1, 50.0);

	glutMainLoop();
	return 0;
}