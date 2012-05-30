#ifndef __PLAYER__H_
#define __PLAYER__H_

#include "entidade.h"

class Player : public Entidade{

    public:
        void ajustaCamera();
    public:

        Player();

        void moveFrente(bool mover);
        void moveTraz(bool mover);
        void moveEsquerda(bool mover);
        void moveDireita(bool mover);

        void giraEsquerda(bool mover);
        void giraDireita(bool mover);
        void giraCima(bool mover);
        void giraBaixo(bool mover);

        void setMouse(int x, int y);
        void moveMouse(int x, int y);
        //temp como public
        void calculaDirecao(void);

        //Liga ou desliga correr
        void setCorrer(void);
        void setAndar(void);

    public:
        static Player PlayerControl;

};


#endif
