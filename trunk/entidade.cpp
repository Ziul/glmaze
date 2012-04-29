#include "entidade.h"
#include "defines.h"




//==============================================================================
// Variaveis estáticas
//==============================================================================
std::vector<Entidade*> Entidade::EntidadeList;

//==============================================================================
// Construtores
//==============================================================================
Entidade::Entidade()
{
    flags = ENTIDADE_FLAG_NENHUM;
    entidadeColidida.clear();
    deltaTicks = glutGet(GLUT_ELAPSED_TIME);
    tamanho.x = tamanho.y = tamanho.z = 10;
    visible = true;
    dead = false;
    showWired = false;

    maxVelocidade.x = maxVelocidade.y = maxVelocidade.z = 50.f;

    addToEntidadeList(); // Por algum motivo não está funcionando quando chamado no construtor
}

void Entidade::reset()
{
//    Entidade::Entidade();
	Entidade();
}
Entidade::~Entidade()
{
    cleanup();
}
void Entidade::cleanup()
{
    removeFromEntidadeList();
}
bool Entidade::isColisaoObjeto(Entidade* objeto)
{
    //Nota, o ponto posição marca 0.... ex: posição 0 começo do bloco final do bloco em x,y,z
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
bool Entidade::isColisaoMapa(Vetor3D newPosicao)
{
    //Calcula o Id do tile que deve ser testado
    //Ex: X = 5 tal que startX = 0,41 = 0 endX = 1,3 = 1
    int startX = (newPosicao.x) / TAMANHO_BLOCO;
    int startZ = (newPosicao.z) / TAMANHO_BLOCO;
    int endX = (newPosicao.x + (tamanho.x)) / TAMANHO_BLOCO;
    int endZ = (newPosicao.z + (tamanho.z)) / TAMANHO_BLOCO;

    //Checa colisões com os tiles
    for(int iZ = startZ; iZ <= endZ; iZ++) {
        for(int iX = startX; iX <= endX; iX++) {
            Tile* bloco = Map::MapControl(iX, iZ);

            if(isColisaoTile(bloco, newPosicao.y))
                return true;
            }
    }
    return false;
}
bool Entidade::isColisaoTile(Tile* bloco, float posY)
{
    if ( //Se o bloco for uma parede e se posY for menor que a altura máxima Y do bloco, ou seja, está abaixo do bloco
        (bloco->typeId & TILE_TIPO_PAREDE) &&
        (posY < (bloco->posY+bloco->tamanho) ) &&
        ((posY+tamanho.y) > bloco->posY)
        )
        return true;
    else
        return false;
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
            return; //Se já estiver na lista, retorna
    }

    EntidadeList.push_back(this);
}

bool Entidade::carregaModelo(char* file){return true;}
//==============================================================================
// Executa ações do loop, aceleração, velocidade.
//==============================================================================
void Entidade::loop()
{
    if(dead) return;
    //deltaTicks reseta o render
    int delta = glutGet(GLUT_ELAPSED_TIME) - deltaTicks;
    float fator = delta/1000.f;

    if (flags & ENTIDADE_FLAG_GRAVIDADE)
        aceleracao.y = -15.f;// sistemas de coordenadas do openGL -y baixo

    //Calcula acelerações
    if ( velocidade.x + aceleracao.x <= maxVelocidade.x)
        velocidade.x += (aceleracao.x * fator);
    if ( velocidade.y + aceleracao.y <= maxVelocidade.y)
        velocidade.y += (aceleracao.y * fator);
    if ( velocidade.z + aceleracao.z <= maxVelocidade.z)
        velocidade.z += (aceleracao.z * fator);

    Vetor3D newPosicao = posicao + (velocidade * fator );

    if (isColisaoMapa(newPosicao) == false)
        posicao = newPosicao;

    deltaTicks = glutGet(GLUT_ELAPSED_TIME);
}
void Entidade::render()
{
    int tamanhoCubo = tamanho.x; //Temp, enquanto utilizar glutCube
    glPushMatrix();
    //Centraliza devido ao GLUT
    glColor3f(1.0f, 0.0f, 0.0f);
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
    // thisID = 2  testa com 3, 4      desta, forma, thisID = 2 não testa colisões com 1 pois já foi testado anteriormente.
    for (unsigned int i = thisID+1; i < EntidadeList.size(); i++)
    {
        if (EntidadeList[i] != this && !EntidadeList[i]->dead)
        {
            if(isColisaoObjeto(EntidadeList[i]) )
            {   //adiciona colisões tanto neste elemento quanto no testado
                setColisao(EntidadeList[i]);
                EntidadeList[i]->setColisao(this);
            }
        }
    }
}
//Seta colisão através de método publico
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
        return; // sem colisões
    entidadeColidida.clear();
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
