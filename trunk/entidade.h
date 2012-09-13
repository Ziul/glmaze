
#ifndef __ENTIDADE_H_
#define __ENTIDADE_H_

#include <vector>
#include "vetor3d.h"
#include "defines.h"
#include "map.h"
#include "camera.h"
#include "soundAL.h"
#include "model_obj.h"

enum
{
    ENTIDADE_FLAG_NENHUM            =   0,
    ENTIDADE_FLAG_ESPECIAL          =   0x00000001,
    ENTIDADE_FLAG_PLAYER_NORMAL     =   0x00000002,
    ENTIDADE_FLAG_PLAYER_ESPECIAL   =   0x00000004,
    ENTIDADE_FLAG_RESPAWN           =   0x00000008,
        //not used
    ENTIDADE_FLAG_PORTA             =   0x00000016
};


class Entidade
{
    public:
        static std::vector<Entidade*> EntidadeList;
        Entidade();
        virtual ~Entidade();
    protected:
        bool isColisaoObjeto(Entidade* objeto);
        bool isColidido();
        bool visible;
        bool dead;

        float r,g,b;

        int delta;
        std::vector<Entidade*> entidadeColidida;






    public:
        Model_OBJ obj;
        void createModel(char* filename){obj.Load(filename);}
        void addToEntidadeList();
        void setRandomPosition();
        void setColor3f(float fr, float fg, float fb);
        float getColor(int rgb_i);
        Tile* isColisaoMapa(Vetor3D newPosicao, int type = TILE_TIPO_PAREDE);
        void setColisao(Entidade* ent);
        void setPosicao(float x, float y, float z);
        //Ex: int delta = getTicks() - deltaTicks;
        //Ex: posicao = posicao + (velocidade * (delta/1000.f ) );
        unsigned int deltaTicks; //quantos ms desde a ultima vez
        unsigned int respawnTicks;// o tempo em q ele morreu
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
        void init();
        void removeFromEntidadeList();


        virtual bool carregaModelo(char* file);
        virtual void loop();
        virtual void render();
        virtual void cleanup();
        virtual void executaColisao();
        virtual void testaColisao();


};


#endif
