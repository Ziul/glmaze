#include "camera.h"

#include <math.h>

Camera::Camera()
{
    angleX = 90.0f;
    angleY = 0.0f;
    angleOffsetX = angleOffsetY = 0;

    lookX = 0.5f;
    lookY = 0.0f;
    lookZ = -1.0f;

    cameraX = TAMANHO_BLOCO/2;
    cameraY = 5.0f;
    cameraZ = TAMANHO_BLOCO/2;

    deltaAngleX = deltaAngleY = 0.0f; //Angulo de rotação da direção horizontal e vertical

    deltaMouseX = deltaMouseY = 0.0f;

    deltaMove = deltaMoveLado = 0.0f;

    velocidadeMove = 1.0f;
    velocidadeVira = 0.5f;
    velocidadeViraMouse = 0.1f;
    xOrigem = -1;
    yOrigem = -1;
}

void Camera::loop()
{
    if (deltaMove)
        calculaMovimento(deltaMove);
    if (deltaMoveLado)
        calculaMovimentoLateral(deltaMoveLado);
    if (deltaAngleX || deltaAngleY)
        calculaDirecao();

    gluLookAt(  cameraX      , cameraY      , cameraZ,
                cameraX+lookX, cameraY+lookY, cameraZ+lookZ,
                0.0f   , 1.0f,    0.0f);
}

void Camera::calculaDirecao(void)
{
    angleX += deltaAngleX;
    angleY += deltaAngleY;

    //corrige angulo
    if ( angleX+angleOffsetX >= 360 )
        angleX -= 360;
    if ( angleX+angleOffsetX < 0)
        angleX += 360;

    //Só permite rotacionar 180 graus em Y
    if ( angleY+angleOffsetY >= 90 )
        angleY = 90-angleOffsetY;
    if ( angleY+angleOffsetY <= -90)
        angleY = -(90+angleOffsetY);


    lookX = sin( (angleX+angleOffsetX)*M_PI/180);
    lookZ = -cos( (angleX+angleOffsetX)*M_PI/180);

    lookY = sin( (angleY+angleOffsetY)*M_PI/180);
}
void Camera::calculaMovimento(float delta)
{
    //Adiciona ao movimento
    //Fator delta vezes direção. 0.1f para ajustar velocidade.
    cameraX += delta * lookX * 0.1f;
    cameraZ += delta * lookZ * 0.1f;
}
void Camera::calculaMovimentoLateral(float delta)
{
    float lateralX = sin( (angleX-90)*M_PI/180);
    float lateralZ = -cos( (angleX-90)*M_PI/180);
    //Adiciona ao movimento
    //Fator delta vezes direção. 0.1f para ajustar velocidade.
    cameraX += delta * (lateralX) * 0.1f;
    cameraZ += delta * (lateralZ) * 0.1f;
}


void Camera::moveFrente(bool mover)
{
    if(mover)
        deltaMove = velocidadeMove;
    else
        deltaMove = 0.0f;
}
void Camera::moveTraz(bool mover)
{
    if(mover)
        deltaMove = -velocidadeMove;
    else
        deltaMove = 0.0f;

}
void Camera::moveEsquerda(bool mover)
{
    if(mover)
        deltaMoveLado = velocidadeMove;
    else
        deltaMoveLado = 0.0f;
}
void Camera::moveDireita(bool mover)
{
    if(mover)
        deltaMoveLado = -velocidadeMove;
    else
        deltaMoveLado = 0.0f;
}

void Camera::giraEsquerda(bool mover)
{
    if(mover)
        deltaAngleX = velocidadeVira;
    else
        deltaAngleX = 0.0f;
}
void Camera::giraDireita(bool mover)
{
    if(mover)
        deltaAngleX = -velocidadeVira;
    else
        deltaAngleX = 0.0f;
}
void Camera::giraCima(bool mover)
{
    if(mover)
        deltaAngleY = velocidadeVira;
    else
        deltaAngleY = 0.0f;
}
void Camera::giraBaixo(bool mover)
{
    if(mover)
        deltaAngleY = -velocidadeVira;
    else
        deltaAngleY = 0.0f;
}

void Camera::setMouse(int x, int y)
{
    xOrigem = x;
    yOrigem = y;

    if (xOrigem == -1) // Ambos serão -1 necessariamente
    {
        angleX +=angleOffsetX;
        angleY +=angleOffsetY;
        angleOffsetX = 0;
        angleOffsetY = 0;
    }
}
void Camera::giraMouse(int x, int y)
{
    deltaMouseX = deltaMouseY = 0;
    //Se houve deslocamento
    if (xOrigem>0)
    {
        angleOffsetX = (xOrigem-x) * 0.1f;
    }
    if (yOrigem>0)
    {
        angleOffsetY = (yOrigem-y) * 0.1f;
    }
    calculaDirecao();
}
