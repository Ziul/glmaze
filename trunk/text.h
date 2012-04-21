#ifndef __TEXT__H_
#define __TEXT__H_

#include "defines.h"
#include <stdio.h>


void renderBitmapString(
		float x,
		float y,
		int spacing,
		void *font,
		char *string) {

  char *c;
  int x1 = x; //Guarda posição rasterizada para computar espaço

  for (c=string; *c != '\0'; c++) {
    glRasterPos2d(x1,y);
    glutBitmapCharacter(font, *c);
    x1 = x1 + glutBitmapWidth(font, *c) + spacing;
  }
}

void* font_glut = GLUT_BITMAP_8_BY_13;

///ARRUMA PROJECOES
void setProjecaoOrto()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); //não fecha
	glLoadIdentity();

	// coloca projecao ortografica 2d
	gluOrtho2D(0, wScreen, hScreen, 0);
	glMatrixMode(GL_MODELVIEW);
}
void restauraProjecaoPerspectiva()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix(); // fecha o pushMatrix do projecaoOrtho
    glMatrixMode(GL_MODELVIEW);
}

void renderText2dOrtho(float x, float y, int spacing, const char*pStr, ...)
{
    char string[128];
    va_list valist; //info das variaveis
    va_start(valist, pStr); //inicia lista de argumentos das variaveis
    vsprintf(string, pStr, valist); // joga string formatado para string
    va_end(valist); // realiza operacoes de fato

    glDisable(GL_LIGHTING);
    setProjecaoOrto();
        glPushMatrix();
        glLoadIdentity();
        renderBitmapString(x,y, spacing, font_glut, string);
        glPopMatrix();
    restauraProjecaoPerspectiva();
    glEnable(GL_LIGHTING);

}




#endif


