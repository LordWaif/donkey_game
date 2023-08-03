/*
 * FreeGLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone 
 * and torus shapes in FreeGLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>

#include "poligon_create.h"
#include "textura.h"

#define QUANT_TEX 6

#include "menu.cpp"
#include "timer.cpp"
#include "retry.cpp"
Timer timer;
Menu menu;
Retry retry;
bool chamaMenu = true;
bool selecionado = true;


//Timer
char s[30]; 
int count_timer = 0;
float timer_global = 0.0;
double t = 10000;


// Boneco
float transx_character = -9.9;
float transy_character = -6.6;
float inicio_y = transy_character;
bool jumping = false;
bool uping = false;
float rotation_arms = 0;
float rotation_body = 0;
float rotation_leg = 0;
bool isanimated_arms = false;
unsigned int level_character = 1;
int edge1,edge2;


//Donkey
bool isDonkey_rot = false;
bool isDonkey_rot_arms = false;


//Colisão
float position_characterx = -9.75;
float position_charactery = -8;
float position_characterz = -6.0;

//Diamond
int rotation_diamond = 0;
bool isRotD = false;

//Morte
bool death = false;
bool isColision = false;
bool tente_novamente = false;
int id_death = 0;

//DESATIVAR plataforma
int level_limite = 5;
bool desativa_plataforma[4] = {false, false, false, false};

unsigned int id_texturas[QUANT_TEX];
float aspecto,angulo_observador,rot_x,rot_y,rot_z;
int mseg = 10;
static float zoom = 28;
float angulo[4] = {0,0,0,0};
int count = 0;
static double translation_x = 3;
static double translation_y = 6.0;

static double translation_x_ac = 0;
static double translation_y_ac = 0;

float count_transition[4] = {0.0,0.0,0.0,0.0};

float transx[4] = {-5,-5,-5,-5}, level[4] = {1,1,1,1}, transy[4] = {13.3,13.3,13.3,13.3}, transz[4] = {-6,-6,-6,-6};
float milk[3] = {-5,15, -6};

bool direita[4] = {true,true,true,true}, transition[4] = {false,false,false,false}, primeira_volta[4] = {false,false,false,false}; 
/* GLUT callback Handlers */

void chama_matriz_poligono(int translated_x, int translated_y,int translated_z, float angulacao);
void escada(int translated_x, int translated_y,int translated_z);
void cria_barril(float transx, float transy, float transz, float angulo);
void chama_escada();
void wallpaper();
void wallpaper_menu();

void rot_diamond(int value);

void iluminar();

void jump_up(int value);
void jump_down(int value);
void jump_hold(int value);

void animation_arms(int value);
void animation_back(int value);
void animation_upside(int value);

void moviment_character(int op);

void invoke_character(float x, float y, float z);
void invoke_donkey();

//Resetar
void reseta_globais();
float rotation_donkey = 0,rotation_donkey_arms = 0;
void rot_donkey(int value);
void rot_donkey_arms(int value);

void barris_empilhados();
void reseta_barril(int x);

//diamond
float colisionReset(int atual, int prox);
void detect_colision_milk();
void update(int value);
void chama_diamond();

void colision(){
    float d;
    for(int i = 0; i < 4; i++){
        d = pow((transx[i] - (position_characterx)),2) + pow((transy[i] - (position_charactery)),2) + pow((transz[i] - (position_characterz)),2);
        d = sqrt(d);
        if(d < 1.1){
            isColision = true;
            death = true;
            id_death = 0;
            }
    }
}

void observador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	iluminar();
	// Especifica posição do observador e do alvo
	glTranslatef(4,0,-rot_z);
	glRotatef(rot_x,1,0,0);
	glRotatef(rot_y,0,1,0);
	//printf("rotx: %4.f   roty:  %4.f",rot_x,rot_y);
}

void visual(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angulo_observador,aspecto,0.5,500);
	//printf("ang: %4.f",angulo_observador);
	gluLookAt (0.0,11, 19.0, translation_x, translation_y, 0.0, 0.0, 1.0, 0.0);
	//printf("trx: %4.f   try:  %4.f",translation_x,translation_x);
	observador();
}


static void 
resize(int w, int h)
{
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	aspecto = (GLfloat)w/(GLfloat)h;

	visual();	
}

// static void
// transform(){
// 	glTranslated(translation_x,translation_y,0);
//    
// }
void reseta_barril(int x){
    transy[x] = 13.3;
    transx[x] = -5;
    level[x] = 1;
    direita[x] = true;
    primeira_volta[x] = true;
    transition[x] = false;
}

void movimento_barril(int x){
    if (angulo[x]< -360.0){
        angulo[x] = 0.0;
    }

    //troca giro
    direita[x] == true ? angulo[x]-- : angulo[x]++;

     if(!transition[x]){
        if(transx[x]> 12){
            direita[x] = false;
            level[x]++;
            transition[x] = true;
        }else if(transx[x]< -12){
            level[x]++;
            direita[x] = true;
            transition[x] = true;
        } 


        //printf("%f\n",level[0]);


        //troca direção do giro
        if(direita[x]){
            transx[x]+=0.05;
            if(level[x] != 1){
                transy[x]-= 0.00275;
            }
        }else{
            transx[x]-=0.05;
            if(level[x] != 1){
                transy[x]-= 0.00275;
            }
        }

        if(level[x] == level_limite - count_timer){
            reseta_barril(x);
        }


    }else{
        if(level[x] >= level_limite - count_timer){
            reseta_barril(x);
        }else{
            transy[x] -= 0.1;
            count_transition[x] += 0.1;
            if(level[x] == 2){
                if(count_transition[x] >= 6.3){
                    transition[x] = false;
                    count_transition[x] = 0.0;
                }

            }else if(level[x] >= 2 && level[x] < 5){
                if(count_transition[x] >= 5.6){
                    transition[x] = false;
                    count_transition[x] = 0.0;
                }
            }
        }
    }
}

void update(int value){
    t = t-1;
    if(t == -1 && count_timer < 3){
        t = 10;
        count_timer++;
        mciSendString("stop data/cdmusic.wav", NULL, 0, NULL);
    }
    if(t <= 9 && count_timer < 3){
        mciSendString("play data/cdmusic.wav", NULL, 0, NULL);
    }
    int time = (int)t;
    //printf("TIME : %2d Sec", time);
    glutTimerFunc(1000, update, 0);
    glutPostRedisplay();
}

void detect_colision_milk(){
    float d;
    d = pow((milk[0] - (position_characterx)),2) + pow((milk[1] - (position_charactery)),2) + pow((milk[2] - (position_characterz)),2);
    d = sqrt(d);

    if(d < 0.75){
        mciSendString("play sounds/win_sound.wav", NULL, 0, NULL);
        death = true;
        id_death = 3;
    }
}

float colisionReset(int atual, int prox){
    float d;
    d = pow((transx[atual] - transx[prox]),2) + pow((transy[atual] - transy[prox]),2) + pow((transz[atual] - transz[prox]),2);
    d = sqrt(d);
    return d;
}

static void 
display(void)
{
	if(position_characterx < -12.5 || position_characterx > 12.5){
		death = true;
		id_death = 1;
	}
	if(isDonkey_rot == false){
		glutTimerFunc(7,rot_donkey, 0);
	}
	if(isDonkey_rot_arms == false){
		glutTimerFunc(7,rot_donkey_arms, 0);
	}
    /* Apaga o video e o depth buffer, e reinicia a matriz */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    if(chamaMenu){
    	glClearColor(1,1,1,1);
		glClear(GL_COLOR_BUFFER_BIT);
        if(!tente_novamente){
            menu.menuPrincipal(selecionado);
            mciSendString("stop sounds/dkmusic.wav", NULL, 0, NULL);
        }else{
        	retry.retryOrExit(selecionado, id_death);
            mciSendString("stop sounds/dkmusic.wav", NULL, 0, NULL);
        }
    }else if(chamaMenu == false){
    	if(count_timer < 3){
            timer.contador(t);
        }
        glColor3d(1,1,1);	
    	colision();
    	mciSendString("play sounds/dkmusic.wav", NULL, 0, NULL);
        if(death){
        	if(id_death != 3){
                mciSendString("play sounds/death_sound.wav", NULL, 0, NULL);
            }
            tente_novamente = true;
            chamaMenu = true;
            selecionado = true;
            reseta_globais();
        }
    	
        if(!primeira_volta[0]){
            movimento_barril(0);
        }else if(colisionReset(0, 3) > 2){
            movimento_barril(0);
        }
        for(int i = 1; i < 4; i++){
            if((level[i-1]>1 || primeira_volta[i-1]) && colisionReset(i, i-1) > 2){
                movimento_barril(i);
            }
        }
        detect_colision_milk();
        
    
        glRotated(rot_x,1.2,0,0);
        glRotated(rot_y,0,1.2,0);
        
        barris_empilhados();
        
        
    	invoke_character(position_characterx, position_charactery , position_characterz);
    	
    	for(int i = 0; i < count_timer; i++){
              desativa_plataforma[i] = true;
                //printf("%d",desativa_plataforma[i]);
		}
    	
        if(!desativa_plataforma[1]){
            glPushMatrix();
            glTranslated(-9.9,1.5,-6.4);
            glScalef(1.3,3.2,-0.5);
            //transform();
            chama_escada();
            glPopMatrix();
            
        }else{if(level_character == 2){death = true;id_death = 2;}}
        if(!desativa_plataforma[2]){
            glPushMatrix();
            glTranslated(9.9,8.7,-6.4);
            glScalef(1.2,3.75,-0.5);
            //transform();
            chama_escada();
            glPopMatrix();
            
            
        }else{if(level_character == 3){death = true;id_death = 2;}}
        if(!desativa_plataforma[0]){
            glPushMatrix();
            glTranslated(9.9,-5.4,-6.4);
            glScalef(1.3,3.2,-0.5);
            //transform();
            chama_escada();
            glPopMatrix();
            
        }else{if(level_character == 1){death = true;id_death = 2;}}
        
        //Diamante
        glPushMatrix();
            glTranslated(-5,16,-6);
            glScalef(0.7,0.7,0.7);
            if(isRotD == false){
                   glutTimerFunc(60,rot_diamond,0);
            }
            glRotatef(rotation_diamond,0,1,0);
            chama_diamond();
        glPopMatrix();
        
		glPushMatrix();
		glTranslated(-14,1.5,-15.4);
		glRotatef(5,0,1,0);
		glScalef(80,70,-6.4);
		wallpaper();
		glPopMatrix();
        
        glPushMatrix();
        glTranslatef(-7,14.75,-6);
        glRotatef(rotation_donkey,0,1,0);
		invoke_donkey();
  		glPopMatrix();
  		
  		glPushMatrix();
  		glTranslatef(-4.5,13.75,-6);
  		glTranslatef(-2,0,0);
  		glRotatef(rotation_donkey,0,1,0);
  		glTranslatef(2,0,0);
  		glTranslatef(0,1.2,0);
		glRotatef(rotation_donkey_arms,0,0,1);
		glTranslatef(0,-1.2,0);
  		cria_barril(0,0,0, 0);
  		glPopMatrix();
        
        if(!desativa_plataforma[0]){
            chama_matriz_poligono(0, -9, -6, 10);
        }
        if(!desativa_plataforma[1]){
            chama_matriz_poligono(0, -2, -6, -10);
        }
        if(!desativa_plataforma[2]){
            chama_matriz_poligono(0, 5, -6, 10);
        }
        chama_matriz_poligono(0, 12, -6, 0);
        
        
        cria_barril(transx[0], transy[0], transz[0], angulo[0]);
        
        if(!primeira_volta[0]){
			for(int i = 1;i < 4; i++){
	            if(level[i-1]>1){
	                //printf("entrou %d",level[i-1]);
	                cria_barril(transx[i], transy[i], transz[i], angulo[i]);
	            }
	        }	
		}else{
			for(int i = 1;i < 4; i++){
	            if(primeira_volta[0]){
	                //printf("entrou %d",level[i-1]);
	                cria_barril(transx[i], transy[i], transz[i], angulo[i]);
	            }
	        }	
		}  
    }
    
    //printf("x = %f, y = %f, z = %f\n", transx[0], transy[0], transz[0]);
    //printf("x2 = %f, y2 = %f, z2 = %f\n", position_characterx, position_charactery, transz[0]);
    glutSwapBuffers();
}


static void 
key(unsigned char key, int x, int y)
{
    switch (key) 
    {
        case 27 : 
            exit(0);
            break;
        case 'a':
        	moviment_character(1);
        	break;
        case 'w':
        	if(chamaMenu){
                mciSendString("play sounds/menu_select.wav", NULL, 0, NULL);
            }
            selecionado = !selecionado;
        	if(!jumping && !uping){
	        	if(level_character%2 == 0){
					edge1 = -8;
					edge2 = -11;
				}else{
					edge1 = 11;
					edge2 = 8;
				}
	        	if(position_characterx <edge1 && position_characterx > edge2){
	        		level_character ++;
	        		inicio_y = transy_character;
	        		glutTimerFunc(5,animation_upside,1);
				}
			}
        	break;
        case 's':
        	if(chamaMenu){
                mciSendString("play sounds/menu_select.wav", NULL, 0, NULL);
            }
            selecionado = !selecionado;
            break;
        case 'd':
        	moviment_character(0);
        	break;
        case 32:
            if(!jumping && !uping){
                inicio_y = transy_character;
                mciSendString("play sounds/jump_sound.wav", NULL, 0, NULL);
                glutTimerFunc(10,jump_up, 1);
            }
            break;
        case 13:
            t = 11;
            if(selecionado && chamaMenu){
                chamaMenu = false;
            }else if(!selecionado){
                exit(0);
            }else if(selecionado && tente_novamente){
                chamaMenu = false;
            }
            break;
    }
    visual();
    glutPostRedisplay();
}
void 
moviment_character(int op){
	float x,y;
	if(op == 1){
		if(level_character%2 == 0){x = -0.3;y = 0.0188;}else{x = -0.3;y = -0.0188;}
	}else{
		if(level_character%2 == 0){x = 0.3;y = -0.0188;}else{x = 0.3;y = 0.0188;}
	}	
	if(level_character == 4){
		y = 0;
	}

	transx_character += x;
	transy_character += y;
	position_characterx += x;
	position_charactery += y;
	if(isanimated_arms == false){
	glutTimerFunc(7,animation_arms, 0);
	}
	glutTimerFunc(5,animation_back, op);	

}

void
jump_up(int value){
	float x,y;
	y = 0.2;
	if(level_character%2 == 0){x = -0.084375;}else{x = 0.084375;}
		if(level_character !=4){
	if(rotation_body == 0){
	x = +0.084375;
	if(level_character%2 == 0){
		inicio_y -= 0.0061875;
	}else{
		inicio_y += 0.0061875;
	}
	}
	if(rotation_body == 180){
	x = -0.084375;
	if(level_character%2 == 0){
	inicio_y += 0.0061875;
	}else{
	inicio_y -= 0.0061875;
	}
	}
	}
	if(value == 1){
		jumping = true;
	}
	transy_character += y;
	position_charactery += y;
	rotation_leg += 10;
	transx_character += x;
	position_characterx += x;
  	//printf("fff %f",transy_character);
	glutPostRedisplay();
	if(transy_character <= inicio_y+ 2.8){
    	glutTimerFunc(15,jump_up, 0);
	}else{
		glutTimerFunc(25,jump_hold, 0);
	}
}
void
jump_down(int value){
	float x,y;
	y = 0.2;
	if(level_character%2 == 0){x = -0.084375;}else{x = 0.084375;}
		if(level_character !=4){
	if(rotation_body == 0){
	x = +0.084375;
	if(level_character%2 == 0){
		inicio_y -= 0.0061875;
	}else{
		inicio_y += 0.0061875;
	}
	}
	if(rotation_body == 180){
	x = -0.084375;
	if(level_character%2 == 0){
	inicio_y += 0.0061875;
	}else{
	inicio_y -= 0.0061875;
	}
	}
	}
	transy_character -= y;
	position_charactery -= y;
	rotation_leg -= 10;
	transx_character += x;
	position_characterx += x;
	glutPostRedisplay();
	if(transy_character > inicio_y){
    	glutTimerFunc(20,jump_down, 0);
	}else{
		rotation_leg = 0 ;
		transy_character = inicio_y;
		glutPostRedisplay();
		jumping = false;
		return;
	}
}
void
jump_hold(int value){
	float x;
	if(level_character%2 == 0){x = -0.084375;}else{x = 0.084375;}
		if(level_character !=4){
	if(rotation_body == 0){
	x = +0.084375;
	if(level_character%2 == 0){
	 inicio_y -= 0.0061875;
	}else{
		inicio_y += 0.0061875;
	}
	}
	if(rotation_body == 180){
	x = -0.084375;
	if(level_character%2 == 0){
		inicio_y += 0.0061875;
	}else{
		inicio_y -= 0.0061875;
	}
	}
	}
	int j = value + 1;
	if(j > 5){glutTimerFunc(25,jump_down, 0);return;}
	transx_character += x;
	position_characterx += x;
	glutTimerFunc(25,jump_hold, j);
}

void 
animation_arms(int value){
	if(value == 0){
		isanimated_arms = true;
		rotation_leg += 4;
		rotation_arms += 2;
		if(rotation_arms < 40){glutTimerFunc(10,animation_arms, 0);}else{glutTimerFunc(10,animation_arms, 1);}
	}else{
		if(value == 1){
			rotation_arms -= 2;	
			rotation_leg -= 4;
			if(rotation_arms > -40){
				//printf("rot a: %f",rotation_arms);
				glutTimerFunc(7,animation_arms, 1);
			}else{
				glutTimerFunc(7,animation_arms, 2);
			}
		}else{
			rotation_arms += 2;
			rotation_leg += 4;
			if(rotation_arms < 0){
				glutTimerFunc(7,animation_arms, 2);	
			}else{
				rotation_arms = 0;
				rotation_leg = 0;
				isanimated_arms = false;
				return;
			}
		}
	} 
}
void
animation_back(int value){
	float giro = 180;
	if(value == 0){
		if(rotation_body == 0){
			return;
		}else{
			rotation_body -= 6;
			glutTimerFunc(5,animation_back, 0);
		}
	}else{
		if(rotation_body == giro){
			return;
		}else{
			rotation_body += 6;
			glutTimerFunc(5,animation_back, 1);
		}
	}
	
}

void
rot_donkey(int value){
	isDonkey_rot = true;
	if(value == 0){
		if(rotation_donkey == -180){
			glutTimerFunc(7,rot_donkey, 1);
		}		
		rotation_donkey -= 3;
		glutTimerFunc(7,rot_donkey, 0);
	}else{
		if(rotation_donkey == 0){
			isDonkey_rot = false;
			return;
		}else{
			rotation_donkey += 3;
			glutTimerFunc(7,rot_donkey, 1);
		}
	}	
}

void
rot_diamond(int value){
	isRotD = true;
	if(value == 1){
		isRotD == false;
	}
	if(rotation_diamond > -360){
		rotation_diamond -= 3;
		glutTimerFunc(60,rot_diamond, 0);
    }else{
		rotation_diamond = 0;
		glutTimerFunc(60,rot_diamond, 1);
	}			
}

void
rot_donkey_arms(int value){
	isDonkey_rot_arms = true;
	if(value == 0){
		if(rotation_donkey_arms == 90){
			glutTimerFunc(7,rot_donkey_arms, 1);
		}		
		rotation_donkey_arms += 3;
		glutTimerFunc(7,rot_donkey_arms, 0);
	}else{
		if(rotation_donkey_arms == 0){
			isDonkey_rot_arms = false;
			return;
		}else{
			rotation_donkey_arms -= 3;
			glutTimerFunc(7,rot_donkey_arms, 1);
		}
	}	
}



void
animation_upside(int value){
	uping =true;
	float h;
	float px = position_characterx;
	if(position_characterx < 0){px = -px;}
	h = inicio_y + 5.7;
	if(level_character == 4){
		h = 15;
	}
	if(transy_character >= h){
		if(level_character%2 == 0){rotation_body = 180;}else{rotation_body = 0;}
		uping = false;
		return;
	}
	if(position_characterx <edge1 && position_characterx > edge2){
		transy_character += 0.2;
		position_charactery += 0.2;
		rotation_body += 6;
		glutTimerFunc(5,animation_upside, 1);
	}
}
void timer_callback(int value){
    glutTimerFunc(value, timer_callback, value);
    glutPostRedisplay(); // Manda redesenhar o display em cada frame
}


void iluminar(){

    GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 1.0, -0.8, -1.0, 0.0 };
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

int 
main(int argc, char *argv[])
{
	printf("Comandos\nW - Sobe escada \nA - Volta para trás \nD - Segue para frente \nEspaco - Pula do barril");

    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("FreeGLUT Shapes");
    
	glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(key);
    glutTimerFunc(mseg, timer_callback,mseg);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	
	glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    // ang obs: 60
    angulo_observador = 60;
    // x 15 y  -40
    // x 0  y -15
    rot_x = 0;
    rot_y = -25;
    rot_z = 10;
    
    glutTimerFunc(25, update, 0);
	
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    /* Prepara a textura */
    glGenTextures(QUANT_TEX, id_texturas); //gera nomes identificadores de texturas	
    glutMainLoop();
    return EXIT_SUCCESS;
}
void reseta_globais(){
    count_timer = 0;
    timer_global = 0.0;
    t = 10000;
    // Boneco
     transx_character = -9.9;
    transy_character = -6.6;
    inicio_y = transy_character;
    jumping = false;
    uping = false;
    rotation_arms = 0;
    rotation_body = 0;
    rotation_leg = 0;
    isanimated_arms = false;
    level_character = 1;
    //Donkey
     isDonkey_rot = false;
     isDonkey_rot_arms = false;
    //Colisão
     position_characterx = -9.75;
     position_charactery = -8;
     position_characterz = -6.0;

    isColision = false;

    //DESATIVAR plataforma
    level_limite = 5;
    desativa_plataforma = {false, false, false, false};
    mseg = 10;
    zoom = 28;
    angulo = {0,0,0,0};
    count = 0;
    translation_x = 3;
    translation_y = 6.0;

    count_transition = {0.0,0.0,0.0,0.0};

    transx = {-5,-5,-5,-5};
     level = {1,1,1,1};
      transy = {13.3,13.3,13.3,13.3};
       transz = {-6,-6,-6,-6};

    direita = {true,true,true,true};
    transition = {false,false,false,false}; 
    primeira_volta = {false,false,false,false}; 

    death = false;

    chamaMenu = true;
    tente_novamente = true;
    selecionado = true;
}
void chama_matriz_poligono(int translated_x, int translated_y,int translated_z, float angulacao){
	glPushMatrix();
		glTranslated(translated_x,translated_y,translated_z);
		glScalef(9,3,4);
        //transform();
        glRotated(angulacao,0,0,1);
        glBindTexture(GL_TEXTURE_2D, id_texturas[0]); //Ativa a textura atual
    
	    //Cria a textura
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH, TEXTURE_HEIGHT,
	                 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glEnable(GL_TEXTURE_2D);
		drawPlataform(1.45,0.12,0.3,1);
	glPopMatrix();
}

void cria_barril(float transx, float transy, float transz, float angulo)
{
glPushMatrix();
        
        //transform();
        glTranslatef(transx, transy, transz);
        glScalef(0.7,0.7,0.7);
        glRotatef(angulo,0,0,1);
        glRotatef(90,0,1,0);	
        
        glBindTexture(GL_TEXTURE_2D, id_texturas[1]); //Ativa a textura atual
	    
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH_BARREL, TEXTURE_HEIGHT_BARREL,
	                 0, GL_RGB, GL_UNSIGNED_BYTE, texture_barrel);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glEnable(GL_TEXTURE_2D);
        drawPlataform(1,1,1,2);
    glPopMatrix();
}

void chama_escada(){
	glBindTexture(GL_TEXTURE_2D, id_texturas[2]); //Ativa a textura atual
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH_ESCADA, TEXTURE_HEIGHT_ESCADA,
                 0, GL_RGB, GL_UNSIGNED_BYTE, texture_escada);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glEnable(GL_TEXTURE_2D);
	drawEscada(0);
}

void chama_diamond(){
	glBindTexture(GL_TEXTURE_2D, id_texturas[7]); //Ativa a textura atual
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH_D, TEXTURE_HEIGHT_D,
                 0, GL_RGB, GL_UNSIGNED_BYTE, diamond);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glEnable(GL_TEXTURE_2D);
	drawPlataform(1,1,1,12);
}


void wallpaper(){
	glBindTexture(GL_TEXTURE_2D, id_texturas[6]); //Ativa a textura atual
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH_WALLP, TEXTURE_HEIGHT_WALLP,
                 0, GL_RGB, GL_UNSIGNED_BYTE, wallpapergamer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glEnable(GL_TEXTURE_2D);
	drawEscada(1);
}

void wallpaper_menu(){
	glBindTexture(GL_TEXTURE_2D, id_texturas[8]); //Ativa a textura atual
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH_WALLM, TEXTURE_HEIGHT_WALLM,
                 0, GL_RGB, GL_UNSIGNED_BYTE, dk_menu_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glEnable(GL_TEXTURE_2D);
	drawEscada(3);
}

void invoke_character(float x, float y, float z){
	glPushMatrix();
		glTranslatef(transx_character,transy_character,-5.8);
		glRotatef(rotation_body,0,1,0);
		glScalef(0.4,0.4,0.4);
		glBindTexture(GL_TEXTURE_2D, id_texturas[3]); //Ativa a textura atual
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH_BONE, TEXTURE_HEIGHT_BONE,
		         0, GL_RGB, GL_UNSIGNED_BYTE,bones);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glEnable(GL_TEXTURE_2D);
		//cabeça
		glPushMatrix();
		drawPlataform(0.7,0.7,0.7,3);
		glPopMatrix();
		//abdomem
		glPushMatrix();
        glTranslatef(0,-2.2,0);
		drawPlataform(0.8,1.5,1.0,4);
		glPopMatrix();
		
		//braçoes
		glPushMatrix();
			glPushMatrix();
			if(rotation_body == 0){glRotatef(rotation_arms,0,0,1);}
				//printf("rot a %f",rotation_arms);
			if(rotation_body == 180){glRotatef(-rotation_arms,0,0,1);}
			glTranslatef(0,-2.2,1.35);
			drawPlataform(0.3,1.5,0.3,5);
			glPopMatrix();
			
			glPushMatrix();
			if(rotation_body == 0){glRotatef(-rotation_arms,0,0,1);}
			if(rotation_body == 180){glRotatef(rotation_arms,0,0,1);}
			glTranslatef(0,-2.2,-1.35);
			drawPlataform(0.3,1.5,0.3,6);
			glPopMatrix();
		glPopMatrix();
		//pernas
		glPushMatrix();
			glPushMatrix();
			glTranslatef(0,-5.2,0.6);
			
			glTranslatef(0,1.8,0);
			if(rotation_body == 0){glRotatef(rotation_leg/2,0,0,1);}
			if(rotation_body == 180){glRotatef(-rotation_leg/2,0,0,1);}
			glTranslatef(0,-1.8,0);
			
			drawPlataform(0.5,1.5,0.4,7);
			glPopMatrix();
			
			glPushMatrix();
			glTranslatef(0,-5.2,-0.6);
			
			glTranslatef(0,1.8,0);
			if(rotation_body == 0){glRotatef(-rotation_leg/2,0,0,1);}
			if(rotation_body == 180){glRotatef(rotation_leg/2,0,0,1);}
			glTranslatef(0,-1.8,0);
			
			drawPlataform(0.5,1.5,0.4,7);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void invoke_donkey(){
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, id_texturas[4]); //Ativa a textura atual
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH_DONKEY, TEXTURE_HEIGHT_DONKEY,
		         0, GL_RGB, GL_UNSIGNED_BYTE,donkey);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glEnable(GL_TEXTURE_2D);
		//cabeça
		glPushMatrix();
		glTranslatef(0,1.48,0);
		drawPlataform(0.48,0.48,0.48,9);
		glPopMatrix();
		//abdomem
		glPushMatrix();
		drawPlataform(0.6,1,1,8);
		glPopMatrix();
		
		//braçoes
		glPushMatrix();
			glPushMatrix();
			glTranslatef(0,-0.3,1.3);
			glTranslatef(0,1,0);
			glRotatef(rotation_donkey_arms,0,0,1);
			glRotatef(12,1,0,0);
			glTranslatef(0,-1,0);
			drawPlataform(0.3,1.3,0.3,11);
			glPopMatrix();
			
			glPushMatrix();
			glTranslatef(0,-0.3,-1.3);
			glTranslatef(0,1,0);
			glRotatef(rotation_donkey_arms,0,0,1);
			glRotatef(-12,1,0,0);
			glTranslatef(0,-1,0);
			drawPlataform(0.3,1.3,0.3,11);
			glPopMatrix();
			
		glPopMatrix();
		//pernas
		glPushMatrix();
			glPushMatrix();	
			glTranslatef(0,-1.7,0.5);
			drawPlataform(0.4,0.7,0.4,10);
			glPopMatrix();
			
			glPushMatrix();
			glTranslatef(0,-1.7,-0.5);
			drawPlataform(0.4,0.7,0.4,10);
			glPopMatrix();
			
		glPopMatrix();
	glPopMatrix();
}

void barris_empilhados(){
    int x = -12.0;
    int y = 13.3;
    int z = -6;
    int diametro_do_barril = 1.4;

    cria_barril(x, y, z, 0);
    cria_barril(x, y+ 1.4, z, 0);
    cria_barril(x, y+ 2.8, z, 0);

    cria_barril(0.7 + x + (diametro_do_barril), y, z, 0);
    cria_barril(0.7+ x + (diametro_do_barril), y+ 1.4, z, 0);
}
