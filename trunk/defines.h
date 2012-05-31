#ifndef __DEFINESS__H_
#define __DEFINESS__H_


#if defined (__APPLE__) || defined (MACOSX) /*MAC OS*/
    #include <GLUT/glut.h>
#else
    #ifdef _WIN32                           /* Windows */
    	#define WIN32_LEAN_AND_MEAN
        #include <glee.h>
        #include <gl/gl.h>
		#include <gl/glut.h>
        #include <windows.h>
        #define sleep(x) Sleep(x)
    #else                                   /*Linux*/
    	#include <cstdarg>
    	#include <unistd.h>
        #include <GL/gl.h>
        #include <GL/glut.h>
        #include <GL/glu.h>
        #define Sleep(x) usleep(x<1000000?10000+300*x:x)
    #endif
#endif

#define SCREEN_WIDTH            800
#define SCREEN_HEIGHT           600

#define FRAMES_PER_SECOND       60.0f

#define TAMANHO_BLOCO           12
#define COR_PAREDE              1.0f, 1.0f, 1.0f
#define COR_CHAO                1.0f, 1.0f, 1.0f
#define GAME_FOV                28

#define PONTOS_BOLA             10
#define PONTOS_BOLA_ESPECIAL    50

#define TAMANHO_INIMIGO         5



//Tamanho da tela atual
extern float wScreen;
extern float hScreen;
//Texturas
extern GLuint wallTexture;
extern GLuint floorTexture;
//Menu
extern bool menuPrincipal;



#endif
