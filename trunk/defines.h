#ifndef __DEFINESS__H_
#define __DEFINESS__H_

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #endif

#include <gl/glut.h>
#include <gl/gl.h>


#define SCREEN_WIDTH            640
#define SCREEN_HEIGHT           480

//Tamanho da tela atual
extern float wScreen;
extern float hScreen;



#endif
