#include "minimap.h"


namespace MiniMap
{
    void renderMiniMap()
    {
    glEnable(GL_BLEND);
    txt::setProjecaoOrto();

    int tileMiniSize = 10;
    int posXInit = wScreen-300;
    int posYInit = 20;
    for(int y = 0; y < Map::MapControl.MAP_HEIGHT;y++) {
        for(int x = 0; x < Map::MapControl.MAP_WIDTH;x++) {
            glPushMatrix();

                Tile* bloco = Map::MapControl.getTile(x,y);

                if (bloco->typeId == TILE_TIPO_PAREDE)
                    glColor4f(1.0f,1.0f,1.0f,0.5f);
                else
                    glColor4f(0.0f,0.0f,5.0f,0.5f);


                    glTranslatef(posXInit + x*tileMiniSize, posYInit + y*tileMiniSize, 0.0f);
                glBegin(GL_QUADS);
                    glVertex2f(0.0f, 0.0f);
                    glVertex2f(0.0f, tileMiniSize);
                    glVertex2f(tileMiniSize, tileMiniSize);
                    glVertex2f(tileMiniSize, 0.0f);
                glEnd();

                if (bloco->typeId == TILE_TIPO_CHAO_COM_BOLA) {
                    glTranslatef(tileMiniSize/2, tileMiniSize/2, 0.0f);
                    glColor4f(0.0f,1.0f, 0.0f, 0.5f);
                    float raio = 2;
                    glBegin(GL_TRIANGLE_FAN);
                        glVertex2f(0, 0);
                        for (int angle = 0; angle < 360; angle+=5)
                            glVertex2f(sin(M_PI*angle/180) * raio, cos(M_PI*angle/180) * raio);
                    glEnd();
                }
                if (bloco->typeId == TILE_TIPO_CHAO_COM_BOLA_ESPECIAL) {
                    glTranslatef(tileMiniSize/2, tileMiniSize/2, 0.0f);
                    glColor4f(0.0f,1.0f, 5.0f, 0.5f);
                    float raio = 3.5;
                    glBegin(GL_TRIANGLE_FAN);
                        glVertex2f(0, 0);
                        for (int angle = 0; angle < 360; angle+=35)
                            glVertex2f(sin(M_PI*angle/180) * raio, cos(M_PI*angle/180) * raio);
                    glEnd();
                }


            glPopMatrix();
        }
    }
    ///Desenha entidades do mapa, inimigos, jogador.
    //Fator para adequar as posições do real para o mini-mapa
    float fator = float(tileMiniSize)/float(TAMANHO_BLOCO);
    float tamanhoEntidadeX = float(TAMANHO_INIMIGO)*fator;
    float tamanhoEntidadeY = float(TAMANHO_INIMIGO)*fator;
    //Desenha inimigos e jogador
    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++) {

        //se entidade nao visivel... ignora
        if (Entidade::EntidadeList[i]->isVisible() == false)
            continue;

        tamanhoEntidadeX = Entidade::EntidadeList[i]->tamanho.x * fator;
        tamanhoEntidadeY = Entidade::EntidadeList[i]->tamanho.z * fator;

        glPushMatrix();
            glColor4f(Entidade::EntidadeList[i]->getColor(1),
                      Entidade::EntidadeList[i]->getColor(2),
                      Entidade::EntidadeList[i]->getColor(3), 1.0f);
                        //Inicio do mapa, posicao fatorada no mapa da entidade
            glTranslatef(posXInit + Entidade::EntidadeList[i]->posicao.x*fator,
                         posYInit + Entidade::EntidadeList[i]->posicao.z*fator, 0.0f);

            //Se for o jogador
            if(Entidade::EntidadeList[i] == Player::PlayerControl){
                glColor4f(1.0f,1.0f,1.0f,1.0f);
                glBegin(GL_QUADS);
                    glVertex2f(-1.0f, -1.0f);
                    glVertex2f(-1.0f, tamanhoEntidadeY+1);
                    glVertex2f(tamanhoEntidadeX+1, tamanhoEntidadeY+1);
                    glVertex2f(tamanhoEntidadeX+1, -1.0f);
                glEnd();

            }
            else //Se inimigos
            {
                glBegin(GL_QUADS);
                    glVertex2f(0.0f, 0.0f);
                    glVertex2f(0.0f, tamanhoEntidadeY);
                    glVertex2f(tamanhoEntidadeX, tamanhoEntidadeY);
                    glVertex2f(tamanhoEntidadeX, 0.0f);
                glEnd();
            }

        glPopMatrix();
    }


    txt::restauraProjecaoPerspectiva();
    glDisable(GL_BLEND);
    }

}
