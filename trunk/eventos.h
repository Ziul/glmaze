#ifndef EVENTOS_H_
#define EVENTOS_H_


extern void teclasNormais(unsigned char key, int x, int y);
extern void teclasNormaisUp(unsigned char key, int x, int y);
extern void teclasEspeciais(int key, int x, int y );
extern void teclasEspeciaisSoltar(int key, int x, int y);
extern void mouseButton(int button, int state, int x, int y);
extern void moveMouse(int x, int y);

#endif
