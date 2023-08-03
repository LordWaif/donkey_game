#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
	
class Retry{
	
public:
	
void retryOrExit(bool selecionado,int id_tratamento){
	

	char losebarril[64] = "Voce Perdeu! Um barril te acertou em cheio !";
    char losemap[64] = "Voce Perdeu! Caiu fora do mapa!";
    char loseplat[64] = "Voce Perdeu! Que pena a plataforma caiu";
    char win[64] = "Mission Passed! respect+";

    char retrygame[30] = "Tentar Novamente";

    char exit[30] = "Sair";


    int i =0;


    glRasterPos2f(-7.2,8.2);
    for(i = 0; i<=strlen(losebarril);i++){
        glPushMatrix();
            if(id_tratamento == 0){
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,losebarril[i]);
            }else if(id_tratamento == 1){
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,losemap[i]);
            }else if(id_tratamento == 2){
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,loseplat[i]);
            }else if(id_tratamento == 3){
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,win[i]);
            }

        glPopMatrix();
    }
	
	if(selecionado){
		glPushMatrix();
    		glBegin(GL_TRIANGLES);
				glColor3f(0.1, 0.2, 0.3);
				glVertex3f(0.2, 5.9, 4);
				glVertex3f(1, 6.3, 4);
				glVertex3f(0.2, 6.7, 4);
			glEnd();
		glPopMatrix();
		glRasterPos2f(2,4.5);
		for(i = 0; i<=strlen(retrygame);i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,retrygame[i]);
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
		for(i = 0; i<=strlen(retrygame);i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,retrygame[i]);
		}
	}
	glutPostRedisplay();
	
	
	
}		
};