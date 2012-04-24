//==============================================================================
/*
    Classe que representa uma entidade fisica, isto é, desenhada na tela.

    Utilizada para representar objetos e possivelmente inimigos, tiros.

    Notas sobre flags:

    Utilizar flags = ENTIDADE_TIPO_FISICA;
    para adiciona flags |= ENTIDADE_TIPO_GHOST;

    testar com if (flags & ENTIDADE_TIPO_GHOST)
    if (flags ^ ENTIDADE_TIPO_GHOST) checa se NÃO tem a flag



*/
//==============================================================================
#ifndef __ENTIDADE_H_
#define __ENTIDADE_H_

#include <vector>
#include "vetor3d.h"
#include "defines.h"
#include "map.h"

//Lista de flags
enum
{
    ENTIDADE_FLAG_NENHUM =      0,
    ENTIDADE_FLAG_GRAVIDADE =   0x00000001,
    ENTIDADE_FLAG_GHOST =       0x00000002,
    ENTIDADE_FLAG_GHOST_MAP =   0x00000004,
    ENTIDADE_FLAG_TIRO =        0x00000008,
    ENTIDADE_FLAG_PORTA =       0x00000016
};


class Entidade
{
    public:
        static std::vector<Entidade*> EntidadeList;
        Entidade();
        virtual ~Entidade();
    protected:
        bool isColisaoObjeto(Entidade* objeto);
        bool isColisaoTile(Tile* bloco, float posY);
        bool isColidido();
        bool visible;
        bool dead;
        std::vector<Entidade*> entidadeColidida;

    public:
        bool isColisaoMapa(Vetor3D newPosicao);
        void setColisao(Entidade* ent);
        void setPosicao(float x, float y, float z);
        //Ex: int delta = getTicks() - deltaTicks;
        //Ex: posicao = posicao + (velocidade * (delta/1000.f ) );
        int deltaTicks; //ticks da ultima vez que calculou o movimento
        Vetor3D posicao;
        Vetor3D velocidade;
        Vetor3D aceleracao;
        Vetor3D maxVelocidade;
        Vetor3D tamanho;
        int flags;
        bool showWired;
    public:
        bool isVisible();
        void setTamanho(float newTamanho);
    public:
        void reset();
        void removeFromEntidadeList();
        void addToEntidadeList();

        virtual bool carregaModelo(char* file);
        virtual void loop();
        virtual void render();
        virtual void cleanup();
        virtual void executaColisao();
        virtual void testaColisao();


};


#endif
