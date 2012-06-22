#include "entidade.h"

#include <stdlib.h>




//==============================================================================
// Variaveis estaticas
//==============================================================================
std::vector<Entidade*> Entidade::EntidadeList;

//==============================================================================
// Construtores
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
    //Nota, o ponto posicao marca 0.... ex: posicao 0 comeco do bloco final do bloco em x,y,z
    //Tal que y mais abaixo = y e y mais alto = y+tamanhoY
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
// Retorna true se estiver colidindo com o mapa
//==============================================================================
Tile* Entidade::isColisaoMapa(Vetor3D newPosicao, int type)
{
    //Calcula o Id do tile que deve ser testado
    //Ex: X = 5 tal que startX = 0,41 = 0 endX = 1,3 = 1
    int startX = (newPosicao.x) / TAMANHO_BLOCO;
    int startZ = (newPosicao.z) / TAMANHO_BLOCO;
    int endX = (newPosicao.x + (tamanho.x)) / TAMANHO_BLOCO;
    int endZ = (newPosicao.z + (tamanho.z)) / TAMANHO_BLOCO;

    //Checa colisoes com os tiles
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
// Executa acoes do loop, aceleracao, velocidade.
//==============================================================================
void Entidade::loop()
{
    //passou 3 segundos do respawn
    if ( (flags == ENTIDADE_FLAG_RESPAWN) && ( (glutGet(GLUT_ELAPSED_TIME) - respawnTicks) > 3000) )
    {
        dead = false;
        visible = true;
        setRandomPosition();
        flags = ENTIDADE_FLAG_NENHUM;
    }

    if(dead) return;
    //deltaTicks reseta o render
    delta = glutGet(GLUT_ELAPSED_TIME) - deltaTicks;
    float fator = delta/1000.f;

    //Calcula aceleracoes
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

    int tamanhoCubo = tamanho.x; //Temp, enquanto utilizar glutCube
    glPushMatrix();
    //Centraliza devido ao GLUT
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
    //Testa com todas as entidades desta para frente.
    //Ex:    lista: 1 2 3 4
    // thisID =1,  testa com 2, 3 , 4
    // thisID = 2  testa com 3, 4      desta, forma, thisID = 2 nao testa colisoes com 1 pois ja foi testado anteriormente.
    for (unsigned int i = thisID+1; i < EntidadeList.size(); i++)
    {
        if (EntidadeList[i] != this && !EntidadeList[i]->dead)
        {
            if(isColisaoObjeto(EntidadeList[i]) )
            {   //adiciona colisoes tanto neste elemento quanto no testado
                setColisao(EntidadeList[i]);
                EntidadeList[i]->setColisao(this);
            }
        }
    }
}
//Seta colisao atraves de metodo publico
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
        return; // sem colisoes



    //Volta o que tinha movido.
    float fator = delta/1000.f;
    posicao = posicao - (velocidade * fator );
    //Para, e vai na direcao oposta
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

            //Se a posicao for diferente de parede, entao chao.... coloca cubo
            if (Map::MapControl.getTile(posX, posZ)->typeId != TILE_TIPO_PAREDE) {
                //nota (TAMANHO_BLOCO/2 - tamanho.x/2)  serve para achar o meio do chao
                posicao.x = (TAMANHO_BLOCO/2 - tamanho.x/2) + TAMANHO_BLOCO*posX;
                posicao.y = 0;
                posicao.z = (TAMANHO_BLOCO/2 - tamanho.z/2) + TAMANHO_BLOCO*posZ;
                //1 a 10
                aceleracao.x = 1 + rand() % 10;
                aceleracao.z = 1 + rand() % 10;
                init();
                isOK = true;
                ///Possivel adicionar verificacao se a entidade nao ficou no mesmo lugar usando isColisao e clear() da lista de colisoes
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
