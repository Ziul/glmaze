#ifndef __DEFINESS__H_
#define __DEFINESS__H_


#if defined (__APPLE__) || defined (MACOSX) /*MAC OS*/
    #include <GLUT/glut.h>
#else
    #ifdef _WIN32                           /* Windows */
    	#define WIN32_LEAN_AND_MEAN
        #include <glee.h>
        #include <gl/glut.h>
        #include <windows.h>
    #else                                   /*Linux*/
    	#include <cstdarg>
        #include <GL/gl.h>
        #include <GL/glut.h>
        #include <GL/glu.h>
    #endif
#endif

#define SCREEN_WIDTH            640
#define SCREEN_HEIGHT           480

#define TAMANHO_BLOCO           12
#define COR_PAREDE              0.1f, 0.9f, 0.2f
#define COR_CHAO                0.0f, 0.5f, 0.5f

//Tamanho da tela atual
extern float wScreen;
extern float hScreen;



#endif
