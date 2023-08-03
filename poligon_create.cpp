#include "poligon_create.h"

void drawPlataform(float x,float y,float z,int choose)
{
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;
  GLint j;

  v = {
	{-x,-y,-z},
	{-x,-y,z},
	{-x,y,z},
	{-x,y,-z},
	{x,-y,-z},
	{x,-y,z},
	{x,y,z},
	{x,y,-z}
  };
  
  glBegin(GL_QUADS);
  for (i = 0; i< N_FACES; i++) {
    for(j = 0;j<N_VERTICES;j++){
    	switch(choose){
			case 1:
				glTexCoord2fv(tex_coords[i][j]);
				break;
			case 2:
				glTexCoord2fv(tex_coords_barril[i][j]);
				break;
			case 3:
				glTexCoord2fv(tex_cab[i][j]);
				break;
			case 4:
				glTexCoord2fv(tex_corp[i][j]);
				break;
			case 5:
				glTexCoord2fv(tex_br_d[i][j]);
				break;
			case 6:
				glTexCoord2fv(tex_br_e[i][j]);
				break;
			case 7:
				glTexCoord2fv(tex_pe[i][j]);
				break;
			case 8:
				glTexCoord2fv(tex_donkey_corp[i][j]);
				break;
			case 9:
				glTexCoord2fv(tex_donkey_cab[i][j]);
				break;
			case 10:
				glTexCoord2fv(tex_donkey_pernas[i][j]);
				break;
			case 11:
				glTexCoord2fv(tex_donkey_br[i][j]);
				break;
			case 12:
				glTexCoord2fv(text_coords_diamond[i][j]);
				break;
		}	
		glVertex3fv(v[faces[i][j]]);
		glNormal3fv(n[faces[i][j]]);
	}
  }
  glEnd();
}
void draw_aux(GLfloat v[4][3],GLfloat n[1][3],const GLfloat tex[4][2]){
	glTexCoord2fv(tex[0]);
	glVertex3fv(v[0]);
	glTexCoord2fv(tex[1]);
	glVertex3fv(v[1]);
	glTexCoord2fv(tex[2]);
	glVertex3fv(v[2]);
	glTexCoord2fv(tex[3]);
	glVertex3fv(v[3]);
	glNormal3fv(n[0]);
}
void drawEscada(int op){
	GLfloat v[4][3] = {
		{-1,1,1},
		{-1,-1,1}, //infdir
		{1,-1,1},
		{1,1,1},
	};
	GLfloat n[1][3] = {
		{0.0,0.0,1.0},
	};
	glBegin(GL_QUADS);
			switch(op){
				case 0:
				    draw_aux(v,n,text_coords_escada);
					break;
				case 1:
					draw_aux(v,n,text_coords_wallp);
					break;
				case 3:
					draw_aux(v,n,text_coords_wallm);
					break;
			}
	glEnd();
	if(op == 3){
	glPushMatrix();
	glTranslatef(0,0,1.2);
	glRotatef(180,0,1,0);
	glBegin(GL_QUADS);
			glTexCoord2fv(text_coords_escada[0]);
		    glVertex3fv(v[0]);
		    glTexCoord2fv(text_coords_escada[1]);
		    glVertex3fv(v[1]);
		    glTexCoord2fv(text_coords_escada[2]);
		    glVertex3fv(v[2]);
		    glTexCoord2fv(text_coords_escada[3]);
		    glVertex3fv(v[3]);
		    glNormal3fv(n[0]);
	glEnd();
	}
	glPopMatrix();
}