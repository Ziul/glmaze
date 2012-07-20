/*********************************************************************

Button class that inherits from Drawable,

It has a function pointer that points to the action of clicking on the
button.

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
        //Drows
        void render();

        //Loops
        void handleMouse(int button, int state, int mouseX, int mouseY);

        //Action Button
        void (*ClickAction)(void);
        //void (Drawable::*ClickActionBattle)(void);

        //Hold position, COORDINATE SDL
        void setXY(int x, int y);

        void setColor(float fr, float fg, float fb);

        //Sets the number of states and the size of the texture used for the buttons
        void setEstados(int num_estados, int imgWidth, int imgHeight, int indexTextura = 0);

        //if ativo is false, does not run click
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

