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
        #include <GL/gl.h>
        #include <GL/glut.h>
        #include <GL/glu.h>
    #endif
#endif

#define SCREEN_WIDTH            640
#define SCREEN_HEIGHT           480

//Tamanho da tela atual
extern float wScreen;
extern float hScreen;



#endif
