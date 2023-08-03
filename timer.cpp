#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using std::stringstream;
#include <string>
	using std::string;
	
class Timer{
	
public:
	
void contador(float tempo){
	char texto1[30] = "A plataforma vai cair em: ";
	int time = (int)tempo;
	//printf("tempo %2d:\n", time);
	
	stringstream ss;
	ss << time;
	string str = ss.str();	
	
	int i =0;
	glPushMatrix();
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(0.0,15);
	for(i = 0; i<=strlen(texto1);i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,texto1[i]);
	}
	//glDisable(GL_LIGHTING);
	
	for(i = 0; i<=3;i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
	}
	glPopMatrix();
}		
};