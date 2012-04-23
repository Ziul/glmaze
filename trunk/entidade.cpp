#include "entidade.h"
#include <gl/gl.h>
#include <gl/glut.h>


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
    colidiu = false;
    entidadeColidida = NULL;
    deltaTicks = glutGet(GLUT_ELAPSED_TIME);
    tamanho.x = tamanho.y = tamanho.z = 10;
    visible = true;
    dead = false;

    maxVelocidade.x = maxVelocidade.y = maxVelocidade.z = 50.f;

    EntidadeList.push_back(this);

}
Entidade::~Entidade()
{
    cleanup();
}
void Entidade::cleanup()
{
    removeFromEntidadeList();
}
bool Entidade::isColisaoObjeto(Entidade* objeto){return false;}
//==============================================================================
// Retorna true se estiver colidindo com o mapa
//==============================================================================
bool Entidade::isColisaoMapa(float newX, float newY, float newZ)
{
    //Calcula o Id do tile que deve ser testado
    //Ex: X = 5 tal que startX = 0,41 = 0 endX = 1,3 = 1
    int startX = (newX) / TAMANHO_BLOCO;
    int startY = (newY) / TAMANHO_BLOCO;
    int endX = (newX + (tamanho.x-1)) / TAMANHO_BLOCO;
    int endY = (newY + (tamanho.y-1)) / TAMANHO_BLOCO;

    //Checa colisões com os tiles
    for(int iY = startY; iY <= endY; iY++) {
        for(int iX = startX; iX <= endX; iX++) {
            Tile* bloco = Map::MapControl(iX, iY);

            if(isColisaoTile(bloco) == false)
                return false;
            }
    }
    return true;
}
bool Entidade::isColisaoTile(Tile* bloco){return true;}

void Entidade::removeFromEntidadeList(){}

bool Entidade::carregaModelo(char* file){return true;}
void Entidade::loop()
{
    if(dead) return;
    //deltaTicks reseta após o teste de colisão
    delta = glutGet(GLUT_ELAPSED_TIME) - deltaTicks;

    if (flags & ENTIDADE_FLAG_GRAVIDADE)
        aceleracao.y = 15.f;

    posicao = posicao + (velocidade * (delta/1000.f ) );
}
void Entidade::render()
{
    int tamanhoCubo = tamanho.x; //Temp, enquanto utilizar glutCube
    glLoadIdentity();
    //Centraliza devido ao GLUT
    glTranslated(posicao.x+tamanho.x/2,
                 posicao.y+tamanho.y/2,
                 posicao.z+tamanho.z/2);
    glutSolidCube(tamanhoCubo);

}
void Entidade::testaColisao()
{
    if(dead) return;

    if (isColisaoMapa(posicao.x, posicao.y, posicao.z))
        posicao = posicao - (velocidade * (delta/1000.f ) );

    for (unsigned int i = 0; i < EntidadeList.size(); i++)
    {
        if (EntidadeList[i] != this && !EntidadeList[i]->dead)
        {
            if(isColisaoObjeto(EntidadeList[i]) )
            {
                posicao = posicao - (velocidade * (delta/1000.f ) );
            }
        }
    }
}
void Entidade::executaColisao()
{
    deltaTicks = glutGet(GLUT_ELAPSED_TIME);
}
