/*********************************************************************

Classe Button,

Possui um ponteiro de função que aponta para a ação do clique sobre o
botão.

*********************************************************************/

#include "button.h"


std::vector<Button*> Button::ButtonList;

//Desenha na tela
void Button::render()
{
    switch(status)
    {
        case BUTTON_STATE_OUTSIDE:
            clip.x = 0;
            break;
        case BUTTON_STATE_OVER:
            clip.x = clip.w;
            break;
        case BUTTON_STATE_PRESSED:
            clip.x = clip.w*2;
            break;
    }

    ///Desenha textura na tela
    if(textureIndex) // se diferente de 0
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureIndex);
    }



    txt::setProjecaoOrto();
    glPushMatrix();
        glColor3f(r,g,b);
        glTranslatef(posX, posY, 0.0f);
        glBegin(GL_QUADS);
                glTexCoord2f(clip.x, clip.y);
            glVertex2f(0.0f, 0.0f);

                glTexCoord2f(clip.x, clip.y+clip.h);
            glVertex2f(0.0f, clip.h);

                glTexCoord2f(clip.x+clip.h, clip.y+clip.h);
            glVertex2f(clip.w, clip.h);

                glTexCoord2f(0.0f, 0.0f);
            glVertex2f(clip.w, 0.0f);
        glEnd();

    glPopMatrix();
    txt::restauraProjecaoPerspectiva();

    glDisable(GL_TEXTURE_2D);

}

//Executa loop
void Button::handleMouse(int button, int state, int mouseX, int mouseY)
{
    //solta botão esquerdo
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        isHolding = false;

    if (mouseX > posX && mouseY > posY
        && mouseX < posX + clip.w
        && mouseY < posY + clip.h)
    {/// Dentro do botão
        //botão esquerdo pressionado e segurando
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            isHolding = true;


        /// Segurado
            if(isHolding && frames > 2) // Se botão esquerdo pressionado
            {
                status = BUTTON_STATE_PRESSED;
            }
            else
            {
                if (frames > 1)
                    status = BUTTON_STATE_OVER; //não está segurando ou só tem 2 estados
                else
                    status =  BUTTON_STATE_OUTSIDE; //só tem 1 estado
            }
            /// Clicked
            if (state == GLUT_DOWN)
            {
                if (ativo)
                {
                    if (ClickAction != 0)
                        (*ClickAction)();
                }

            }

    }
    else
    {
        status = BUTTON_STATE_OUTSIDE;
    }

}

//Carrega imagem do botão, e numero de estados e textura
void Button::setEstados(int num_estados, int imgWidth, int imgHeight, int indexTextura)
{
    if (indexTextura >= 0)
        textureIndex = indexTextura;

    if ( num_estados < 1 || num_estados > 3)
    {
        frames = 1;
        return;
    }
    frames = num_estados;


    clip.w = imgWidth/frames;
    clip.h = imgHeight;
    clip.y = 0;
    clip.x = 0;


}

//-1 mantem posição
void Button::setXY(int x, int y)
{
    if ( x >= 0 )
    {
        this->posX = x;
    }

    if ( y >= 0 )
    {
        this->posY = y;
    }
}

void Button::setColor(float fr, float fg, float fb)
{
    r = fr;
    g = fg;
    b = fb;
}

