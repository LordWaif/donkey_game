#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

class Menu{
	
public:
	
void menuPrincipal(bool selecionado){
	char titulo[30] = "Donkey Kong";
	char newgame[30] = "Novo Jogo";
	char exit[30] = "Sair";
	
	int i =0;
	
	
	glRasterPos2f(-4.2,8.2);
	for(i = 0; i<=strlen(titulo);i++){
		glPushMatrix();
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,titulo[i]);
		glPopMatrix();
	}
	
	if(selecionado){
		glPushMatrix();
    		glBegin(GL_TRIANGLES);
				glColor3f(1.0, 1.0, 1.0);
				glVertex3f(0.2, 5.9, 4);
				glVertex3f(1, 6.3, 4);
				glVertex3f(0.2, 6.7, 4);
			glEnd();
		glPopMatrix();
		glRasterPos2f(2,4.5);
		for(i = 0; i<=strlen(newgame);i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,newgame[i]);
		}
		glRasterPos2f(2,3.0);
		for(i = 0; i<=strlen(exit);i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,exit[i]);
		}
	}else if(!selecionado){
		glPushMatrix();
    		glBegin(GL_TRIANGLES);
				glColor3f(0.1, 0.2, 0.3);
				glVertex3f(0.2, 4.7, 4);
				glVertex3f(1, 5.1, 4);
				glVertex3f(0.2, 5.5, 4);
			glEnd();
		glPopMatrix();
		glRasterPos2f(2,3.0);
		for(i = 0; i<=strlen(exit);i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,exit[i]);
		}
		glRasterPos2f(2,4.5);
		for(i = 0; i<=strlen(newgame);i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,newgame[i]);
		}
	}
	glutPostRedisplay();
}			
};