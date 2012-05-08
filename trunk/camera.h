#ifndef _CAMERAS_H_
#define _CAMERAS_H_

#include "defines.h"
#include "entidade.h"

class Camera
{
    private:
        Entidade entidadeCamera;
    public:
        float lookX, lookY, lookZ;
        float cameraX, cameraY, cameraZ;

        float angleX, angleY;
        float angleOffsetX, angleOffsetY;

        float deltaAngleX, deltaAngleY;
        float deltaMouseX, deltaMouseY;
        float deltaMove, deltaMoveLado;

        float velocidadeMove;
        float velocidadeVira;
        float velocidadeViraMouse;

        int xOrigem, yOrigem;
        unsigned int ticks;
    public:
        Camera();
        static Camera CameraControl;

        void ajustaCamera(); //seta posição e direção da camera
        void reset();

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
    private:

        void calculaMovimento(float delta);
        void calculaMovimentoLateral(float delta);

};
#endif
