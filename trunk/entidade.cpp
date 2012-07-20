#include "entidade.h"

#include <stdlib.h>




//==============================================================================
// static variables
//==============================================================================
std::vector<Entidade*> Entidade::EntidadeList;

//==============================================================================
// constructors
//==============================================================================
Entidade::Entidade()
{
    flags = ENTIDADE_FLAG_NENHUM;
    entidadeColidida.clear();
    deltaTicks = 9999999;
    deltaTicks = 0;
    tamanho.x = tamanho.y = tamanho.z = 10;
    visible = true;
    dead = false;
    showWired = false;

    r = 1.0f;
    g = b = 0.0f;

    maxVelocidade.x = maxVelocidade.y = maxVelocidade.z = 50.f;
    entidadeColidida.clear();

}

void Entidade::init()
{
    deltaTicks = glutGet(GLUT_ELAPSED_TIME);
}
Entidade::~Entidade()
{
}
void Entidade::cleanup()
{
}
bool Entidade::isColisaoObjeto(Entidade* objeto)
{
    //Note: The point marks position 0 .... ex: position 0 beginning of the block end of the block in the x, y, z
    //Such that y lower = y ; y highest = y+tamanhoY
    int baixo1 = this->posicao.y;
    int cima1 = this->posicao.y + this->tamanho.y;
    int esquerda1 = this->posicao.x;
    int direita1 = this->posicao.x + this->tamanho.x;
    int frente1 = this->posicao.z;
    int traz1 = this->posicao.z + this->tamanho.z;

    int baixo2 = objeto->posicao.y;
    int esquerda2 = objeto->posicao.x;
    int frente2 = objeto->posicao.z;
    int direita2 = objeto->posicao.x + objeto->tamanho.x;
    int cima2 = objeto->posicao.y + objeto->tamanho.y;
    int traz2 = objeto->posicao.z + objeto->tamanho.z;

    if (
        !(baixo1 > cima2) &&
        !(cima1  < baixo2) &&
        !(esquerda1 > direita2) &&
        !(direita1 < esquerda2) &&
        !(frente1 > traz2) &&
        !(traz1 < frente2)
        )
        {
            return true;
        }

    return false;

}
//==============================================================================
// Returns true if colliding with the map
//==============================================================================
Tile* Entidade::isColisaoMapa(Vetor3D newPosicao, int type)
{
    //Calculates Id tile to be tested
    //Ex: X = 5 Such that startX = 0,41 = 0 endX = 1,3 = 1
    int startX = (newPosicao.x) / TAMANHO_BLOCO;
    int startZ = (newPosicao.z) / TAMANHO_BLOCO;
    int endX = (newPosicao.x + (tamanho.x)) / TAMANHO_BLOCO;
    int endZ = (newPosicao.z + (tamanho.z)) / TAMANHO_BLOCO;

    //Check collisions with tiles
    for(int iZ = startZ; iZ <= endZ; iZ++) {
        for(int iX = startX; iX <= endX; iX++) {
            Tile* bloco = Map::MapControl(iX, iZ);

            if(
               (bloco->typeId == type) &&
               (posicao.y < (bloco->posY+bloco->tamanho) ) &&
               ((posicao.y+tamanho.y) > bloco->posY)
               )
                return bloco;
            }
    }
    return 0;
}

void Entidade::removeFromEntidadeList()
{
    for(unsigned int i = 0; i < EntidadeList.size(); i++)
    {
        if (EntidadeList[i] == this)
            EntidadeList.erase(EntidadeList.begin()+i);
    }
}
void Entidade::addToEntidadeList()
{


    for(unsigned int i = 0; i < EntidadeList.size(); i++)
    {
        if (EntidadeList[i] == this)
            return; //Se ja estiver na lista, retorna
    }

    EntidadeList.push_back(this);
}

bool Entidade::carregaModelo(char* file){return true;}
//==============================================================================
// Performs actions of the loop, acceleration, speed.
//==============================================================================
void Entidade::loop()
{
    //3 seconds has the spawn
    if ( (flags == ENTIDADE_FLAG_RESPAWN) && ( (glutGet(GLUT_ELAPSED_TIME) - respawnTicks) > 3000) )
    {
        dead = false;
        visible = true;
        setRandomPosition();
        flags = ENTIDADE_FLAG_NENHUM;
    }

    if(dead) return;
    //deltaTicks reset the surrender
    delta = glutGet(GLUT_ELAPSED_TIME) - deltaTicks;
    float fator = delta/1000.f;

    //calculates accelerations
    if ( velocidade.x + aceleracao.x <= maxVelocidade.x)
        velocidade.x += (aceleracao.x * fator);
    if ( velocidade.y + aceleracao.y <= maxVelocidade.y)
        velocidade.y += (aceleracao.y * fator);
    if ( velocidade.z + aceleracao.z <= maxVelocidade.z)
        velocidade.z += (aceleracao.z * fator);

    Vetor3D newPosicao = posicao + (velocidade * fator );

    if (isColisaoMapa(newPosicao) == false)
        posicao = newPosicao;
    else
    {
        velocidade.x = 0;
        velocidade.z = 0;
        aceleracao.x = 0;
        aceleracao.z = 0;
        int pos = (int)(rand() % 4);
        switch(pos)
        {
            case 0:
                aceleracao.x = 20;break;
            case 1:
                aceleracao.x = -20;break;
            case 2:
                aceleracao.z = 20;break;
            case 3:
                aceleracao.z = -20;break;
            default:;
        }

    }

    deltaTicks = glutGet(GLUT_ELAPSED_TIME);
}
void Entidade::render()
{
    if (!isVisible())
        return;

    int tamanhoCubo = tamanho.x; //Temp while using glutCube
    glPushMatrix();
    //Centers due to GLUT
    if (flags == ENTIDADE_FLAG_ESPECIAL)
        glColor3f( getColor(1), getColor(2), getColor(3) );
    else
        glColor3f(r,g,b);
    glTranslated(posicao.x+tamanho.x/2,
                 posicao.y+tamanho.y/2,
                 posicao.z+tamanho.z/2);
    if (showWired)
        glutWireCube(tamanhoCubo);
    else
        glutSolidCube(tamanhoCubo);
    glPopMatrix();


}
void Entidade::testaColisao()
{
    if(dead) return;

    unsigned int thisID = -1;
    for (unsigned int i = 0; i < EntidadeList.size(); i++)
        if (EntidadeList[i] == this)
        {
            thisID = i;
            break;
        }
    //Tests with all the entities of this forward.
    //Ex:    lista: 1 2 3 4
    // thisID =1,  tests with 2, 3 , 4
    // thisID = 2  tests with 3, 4      this way, thisID = 2 no collisions with 1 as has already been tested previously.
    for (unsigned int i = thisID+1; i < EntidadeList.size(); i++)
    {
        if (EntidadeList[i] != this && !EntidadeList[i]->dead)
        {
            if(isColisaoObjeto(EntidadeList[i]) )
            {   //adds this element collisions so as tested in
                setColisao(EntidadeList[i]);
                EntidadeList[i]->setColisao(this);
            }
        }
    }
}
//Set collision through the public method
void Entidade::setColisao(Entidade* ent)
{
    entidadeColidida.push_back(ent);
}
bool Entidade::isColidido()
{
    if (entidadeColidida.size() == 0)
        return false;
    else
        return true;
}
void Entidade::executaColisao()
{
    if ( !isColidido() )
        return; // no collisions



    //Back what had moved.
    float fator = delta/1000.f;
    posicao = posicao - (velocidade * fator );
    //For, and go in the opposite direction
    velocidade.x = 0;
    velocidade.z = 0;
    aceleracao.x = -aceleracao.x;
    aceleracao.z = -aceleracao.z;

    if ( (flags == ENTIDADE_FLAG_ESPECIAL) && (entidadeColidida[0]->flags == ENTIDADE_FLAG_PLAYER_ESPECIAL) )
    {
        flags = ENTIDADE_FLAG_RESPAWN;
        respawnTicks = glutGet(GLUT_ELAPSED_TIME);
        dead = true;
        visible = false;
        SoundAL sc;
        sc.play(SFX_eat2);
    }

    entidadeColidida.clear();
}

void Entidade::setRandomPosition()
{
    bool isOK = false;
        while(!isOK) {
            int posX = rand() % Map::MapControl.MAP_WIDTH;
            int posZ = rand() % Map::MapControl.MAP_HEIGHT;

            //If the position is different from the wall, then ground .... put cube
            if (Map::MapControl.getTile(posX, posZ)->typeId != TILE_TIPO_PAREDE) {
                //Note: (TAMANHO_BLOCO/2 - tamanho.x/2)  is used to find the center of the floor
                posicao.x = (TAMANHO_BLOCO/2 - tamanho.x/2) + TAMANHO_BLOCO*posX;
                posicao.y = 0;
                posicao.z = (TAMANHO_BLOCO/2 - tamanho.z/2) + TAMANHO_BLOCO*posZ;
                //1 to 10
                aceleracao.x = 1 + rand() % 10;
                aceleracao.z = 1 + rand() % 10;
                init();
                isOK = true;
                ///Possible to add verification that the entity was not in the same place using isColisao and clear() from list of collisions
            }
        }
}

bool Entidade::isVisible()
{
    return visible;
}
void Entidade::setTamanho(float newTamanho)
{
    tamanho.x = tamanho.y = tamanho.z = newTamanho;
}
void Entidade::setPosicao(float x, float y, float z)
{
    posicao.x = x;
    posicao.y = y;
    posicao.z = z;
}
void Entidade::setColor3f(float fr, float fg, float fb)
{
    r = fr;
    g = fg;
    b = fb;
}
float Entidade::getColor(int rgb_i)
{
    float color = 0.0f;
    switch(rgb_i)
    {
        case 1:
            color = r;
            if (flags == ENTIDADE_FLAG_ESPECIAL)
                color -= 0.55f;
            break;
        case 2:
            color = g;
            if (flags == ENTIDADE_FLAG_ESPECIAL)
                color += 1;
            break;
        case 3:
            color = b;
            if (flags == ENTIDADE_FLAG_ESPECIAL)
                color += 0.95f;
            break;
    }
    return color;
}
