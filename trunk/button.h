/*********************************************************************

Classe Button que herda de Drawable,

Possui um ponteiro de função que aponta para a ação do clique sobre o
botão.

*********************************************************************/


#ifndef _BUTTON_H__
#define _BUTTON_H__

#include "defines.h"
#include "text.h"
#include <vector>

enum STATE {
    BUTTON_STATE_OUTSIDE = 0,
    BUTTON_STATE_OVER = 1,
    BUTTON_STATE_PRESSED = 2
};

class Clip_Rect
{
public:
    Clip_Rect(){x = y = w = h = 0;}
    float x, y, w, h;
};

class Button
{
    public:

        static std::vector<Button*> ButtonList;

        bool isHolding;

        Button()
        {
            posX = posY = frames = 0;
            ativo = true;
            isHolding = false;
            textureIndex = 0;
            r = g = b = 1.0f;
            ClickAction = 0;
        }
        //Desenha
        void render();

        //Executa loop
        void handleMouse(int button, int state, int mouseX, int mouseY);

        //Ação do botão
        void (*ClickAction)(void);
        //void (Drawable::*ClickActionBattle)(void);

        //-1 mantem posição, COORDENADAS SDL
        void setXY(int x, int y);

        void setColor(float fr, float fg, float fb);

        //Seta o numero de estados e o tamanho da textura usada para os botões
        void setEstados(int num_estados, int imgWidth, int imgHeight, int indexTextura = 0);

        //se ativo falso, não executa click
        bool ativo;

    private:

        float r,g,b;
        int posX;
        int posY;
        int frames;
        STATE status;
        Clip_Rect clip;

        int textureIndex;

};


#endif

