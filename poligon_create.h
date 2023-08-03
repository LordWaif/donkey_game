#include <GL/glut.h>

#define N_FACES 6
#define N_VERTICES 4
const GLfloat tex_coords[N_FACES][N_VERTICES][2] = {
    //inf dir           inf esq           sup esq             sup dir
    {{0.52371,0.650969},{0.03174,0.650969},{0.03174,0.564696},{0.52371,0.564696}},//Pontas da plataforma
    {{0.98397,0.54901},{0.4761,0.54901},{0.4761,0.0117645},{0.98397,0.0117645}},//Frente
    {{0.52371,0.650969},{0.03174,0.650969},{0.03174,0.564696},{0.52371,0.564696}},//Pontas da plataforma
    {{0.98397,0.54901},{0.4761,0.54901},{0.4761,0.0117645},{0.98397,0.0117645}},//Frente
    {{0.39675,0.54901},{0.03174,0.54901},{0.03174,0.0117645},{0.39675,0.0117645}},//Lateral
    {{0.39675,0.54901},{0.03174,0.54901},{0.03174,0.0117645},{0.39675,0.0117645}},//Lateral
};

const GLfloat tex_coords_barril[N_FACES][N_VERTICES][2] = {
    //inf dir           inf esq           sup esq             sup dir
    {{0.8125,0.8828125},{0.609375,0.8828125},{0.609375,0.6796875},{0.8125,0.6796875}},//lateral
    {{0.8125,0.6484375},{0.609375,0.6484375},{0.609375,0},{0.8125,0}},//lados
    {{0.8125,0.8828125},{0.609375,0.8828125},{0.609375,0.6796875},{0.8125,0.6796875}},//lateral
    {{0.609375,0.6484375},{0.40625,0.6484375},{0.40625,0},{0.609375,0}},//lados
    {{0.40625,0.6484375},{0.203125,0.6484375},{0.203125,0},{0.40625,0}},//lados
    {{0.203125,0.6484375},{0,0.6484375},{0,0},{0.203125,0}},//lados
};

const GLfloat text_coords_escada[4][2] = {
    {0,0},{0,1},{1,1},{1,0}
};

const GLfloat text_coords_wallp[4][2] = {
	{0,0},{0,1},{1,1},{1,0}
};

const GLfloat text_coords_diamond[6][4][2] = {
{{0,0},{0,1},{1,1},{1,0}},
{{0,0},{0,1},{1,1},{1,0}},
{{0,0},{0,1},{1,1},{1,0}},
{{0,0},{0,1},{1,1},{1,0}},
{{0,0},{0,1},{1,1},{1,0}},
{{0,0},{0,1},{1,1},{1,0}}
};

const GLfloat text_coords_wallm[4][2] = {
{0,0},{0,1},{1,1},{1,0}
};


const GLfloat tex_coords_white[6][4][2] = {
{{0,0},{0,1},{1,1},{1,0}},
{{0,0},{0,1},{1,1},{1,0}},
{{0,0},{0,1},{1,1},{1,0}},
{{0,0},{0,1},{1,1},{1,0}}};

//inf dir           inf esq           sup esq             sup dir
const GLfloat tex_cab[6][4][2] = {
{{0.55859375,0.80273438},{0.55859375,0.69921875},{0.75360625,0.69921875},{0.75360625,0.80273438}},//cab t ok
{{0.8828125, 0.10546875},{0.67578125, 0.10546875},{0.67578125, 0.015625},{0.8828125, 0.015625}},//cima
{{0.214843,0.03125},{0.421875,0.03125},{0.421875,0.10546875},{0.214843,0.10546875}},//cab f ok
{{0.421875,0.10546875},{0.214843,0.10546875},{0.214843,0.03125},{0.421875,0.03125}},//baixo
{{0.66015625,0.10546875},{0.66015625,0.017578125},{0.453125,0.017578125},{0.453125,0.10546875}},//lados
{{0.66015625,0.017578125},{0.66015625,0.10546875},{0.45703125,0.10546875},{0.45703125,0.017578125}}//lados
};

const GLfloat tex_corp[6][4][2] = {
{{0.015625, 0.677734375},{0.015625, 0.833984375},{0.56640625, 0.833984375},{0.56640625, 0.677734375}},
{{0.484375, 0.3828125},{0.1484375, 0.3828125},{0.1484375, 0.111328125},{0.484375, 0.111328125}},
{{0.484375, 0.111328125},{0.1484375, 0.111328125},{0.1484375, 0.3828125},{0.484375, 0.3828125}},
{{0.8828125, 0.10546875},{0.67578125, 0.10546875},{0.67578125, 0.015625},{0.8828125, 0.015625}},
{{0.1484375, 0.3828125},{0.1484375, 0.111328125},{0.484375, 0.111328125},{0.484375, 0.3828125}}
};

const GLfloat tex_br_d[6][4][2] = {
{{0.125, 0.400390625},{0.0234375, 0.400390625},{0.0234375, 0.138671875},{0.125, 0.138671875}},
{{0.125, 0.400390625},{0.0234375, 0.400390625},{0.0234375, 0.138671875},{0.125, 0.138671875}},
{{0.125, 0.138671875},{0.0234375, 0.138671875},{0.0234375, 0.400390625},{0.125, 0.400390625}},
{{0.125, 0.400390625},{0.0234375, 0.400390625},{0.0234375, 0.138671875},{0.125, 0.138671875}},
{{0.6484375, 0.65234375},{0.6484375, 0.38671875},{0.75, 0.38671875},{0.75, 0.65234375}},
{{0.6484375, 0.65234375},{0.6484375, 0.38671875},{0.75, 0.38671875},{0.75, 0.65234375}}
};

const GLfloat tex_br_e[6][4][2] = {
{{0.0234375, 0.400390625},{0.125, 0.400390625},{0.125, 0.138671875},{0.0234375, 0.138671875}},
{{0.125, 0.400390625},{0.0234375, 0.400390625},{0.0234375, 0.138671875},{0.125, 0.138671875}},
{{0.0234375, 0.138671875},{0.125, 0.138671875},{0.125, 0.400390625},{0.0234375, 0.400390625}},
{{0.125, 0.400390625},{0.0234375, 0.400390625},{0.0234375, 0.138671875},{0.125, 0.138671875}},
{{0.75, 0.38671875},{0.75, 0.65234375},{0.6484375, 0.65234375},{0.6484375, 0.38671875}},
{{0.75, 0.38671875},{0.75, 0.65234375},{0.6484375, 0.65234375},{0.6484375, 0.38671875}}
};

const GLfloat tex_pe[6][4][2] = {
{{0.26953125, 0.6484375},{0.15625, 0.6484375},{0.15625, 0.416015625},{0.26953125, 0.416015625}},
{{0.8828125, 0.10546875},{0.67578125, 0.10546875},{0.67578125, 0.015625},{0.8828125, 0.015625}},
{{0.26953125, 0.416015625},{0.15625, 0.416015625},{0.15625, 0.6484375},{0.26953125, 0.6484375}},
{{0.8828125, 0.10546875},{0.67578125, 0.10546875},{0.67578125, 0.015625},{0.8828125, 0.015625}},
{{0.26953125, 0.6484375},{0.26953125, 0.416015625},{0.15625, 0.416015625},{0.15625, 0.6484375}},
{{0.15625, 0.416015625},{0.15625, 0.6484375},{0.26953125, 0.6484375},{0.26953125, 0.416015625}}
};

//sup esq  sup dir  inf dir  inf esq 
const GLfloat tex_donkey_corp[6][4][2] = {
{{1,1},{1,1},{1,1},{1,1}},
{{1,1},{1,1},{1,1},{1,1}},
{{0,0},{0.5,0},{0.5,0.5},{0,0.5}},
{{1,1},{1,1},{1,1},{1,1}},
{{1,1},{1,1},{1,1},{1,1}},
{{1,1},{1,1},{1,1},{1,1}},
};

//sup esq  sup dir  inf dir  inf esq 
const GLfloat tex_donkey_cab[6][4][2] = {
{{1,1},{1,1},{1,1},{1,1}},
{{1,1},{1,1},{1,1},{1,1}},
{{0.5,0},{0.75,0},{0.75,0.25},{0.5,0.25}},
{{1,1},{1,1},{1,1},{1,1}},
{{1,1},{1,1},{1,1},{1,1}},
{{1,1},{1,1},{1,1},{1,1}},
};

const GLfloat tex_donkey_br[6][4][2] = {
{{0.625,0.5},{0.625,0.75},{0,0.75},{0,0.5}},
{{1,1},{1,1},{1,1},{1,1}},
{{0,0.75},{0,0.5},{0.625,0.5},{0.625,0.75}},
{{0.55,0.8},{0.55,0.8},{0.55,0.8},{0.55,0.8}},
{{0.625,0.75},{0,0.75},{0,0.5},{0.625,0.5}},
{{0.625,0.75},{0,0.75},{0,0.5},{0.625,0.5}},
};

//sup esq  sup dir  inf dir  inf esq 
const GLfloat tex_donkey_pernas[6][4][2] = {
{{0.375,0.75},{0.375,1},{0,1},{0,0.75}},
{{1,1},{1,1},{1,1},{1,1}},
{{0,1},{0,0.75},{0.375,0.75},{0.375,1}},
{{0.55,0.8},{0.55,0.8},{0.55,0.8},{0.55,0.8}},
{{0.375,1},{0,1},{0,0.75},{0.375,0.75}},
{{0.375,1},{0,1},{0,0.75},{0.375,0.75}},
};


void drawPlataform(float x,float y,float z,int choose);

void drawEscada(int op);