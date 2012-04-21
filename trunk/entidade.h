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
#include "vetor.h"

enum
{
    ENTIDADE_TIPO_FISICA = 0,
    ENTIDADE_TIPO_GHOST = 0x00000001,
    ENTIDADE_TIPO_INIMIGO = 0x00000002,
    ENTIDADE_TIPO_TIRO = 0x00000004,
    ENTIDADE_TIPO_PORTA = 0x00000008
};


class Entidade
{
    public:
        static std::vector<Entidade*> EntidadeList;
        Entidade();
        virtual ~Entidade();
    protected:
          void calculaColisao(Entidade* objeto);
          void calculaColisaoMapa();
          bool colidiu;
          Entidade* entidadeColidida;

    public:
        //Ex: int delta = getTicks() - deltaTicks;
        //Ex: posicao = posicao + (velocidade * (delta/1000.f ) );
        int deltaTicks; //ticks da ultima vez que calculou o movimento
        Vetor posicao;
        Vetor velocidade;
        float width, heigh, depth;
        int flags;
        bool visible;
    public:
        void removeFromEntidadeList();

        virtual bool carregaModelo(char* file);
        virtual void loop();
        virtual void render();
        virtual void cleanup();
        virtual void executaColisao();
        virtual void testaColisao();


};


#endif
