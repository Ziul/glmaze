#include "camera.h"

#include <math.h>
Camera Camera::CameraControl;
Camera::Camera()
{
    angleX = 90.0f;
    angleY = 0.0f;
    angleOffsetX = angleOffsetY = 0;

    lookX = 0.5f;
    lookY = 0.0f;
    lookZ = -1.0f;

    cameraX = (TAMANHO_BLOCO*1) + TAMANHO_BLOCO/2;
    cameraY = 5.0f;
    cameraZ = (TAMANHO_BLOCO*1) + TAMANHO_BLOCO/2;
    //tests

    //tests
    deltaAngleX = deltaAngleY = 0.0f; //Angle of rotation of the horizontal and vertical direction

    deltaMouseX = deltaMouseY = 0.0f;

    deltaMove = deltaMoveLado = 0.0f;


    velocidadeMoveAndar = CAMERA_ANDA;
    velocidadeMoveCorre = CAMERA_CORRE;
    velocidadeMove = velocidadeMoveAndar;
    velocidadeVira = 45.f;
    velocidadeViraMouse = 0.1f;

    xOrigem = -1;
    yOrigem = -1;
    ticks = 0;

    calculaDirecao();
}

void Camera::reset()
{
    angleX = 90.0f;
    angleY = 0.0f;
    angleOffsetX = angleOffsetY = 0;

    lookX = 0.5f;
    lookY = 0.0f;
    lookZ = -1.0f;

    cameraX = (TAMANHO_BLOCO*1) + TAMANHO_BLOCO/2;
    cameraY = 5.0f;
    cameraZ = (TAMANHO_BLOCO*1) + TAMANHO_BLOCO/2;
    //tests

    //tests
    deltaAngleX = deltaAngleY = 0.0f; //Angle of rotation of the horizontal and vertical direction

    deltaMouseX = deltaMouseY = 0.0f;

    deltaMove = deltaMoveLado = 0.0f;


    velocidadeMoveAndar = CAMERA_ANDA;
    velocidadeMoveCorre = CAMERA_CORRE;
    velocidadeMove = velocidadeMoveAndar;
    velocidadeVira = 45.f;
    velocidadeViraMouse = 0.1f;

    xOrigem = -1;
    yOrigem = -1;
    ticks = 0;

    calculaDirecao();
    ticks = glutGet(GLUT_ELAPSED_TIME);
}


//Called internally by Player.
void Camera::ajustaCamera()
{

    if (deltaAngleX || deltaAngleY)
        calculaDirecao();

    gluLookAt(  cameraX      , cameraY      , cameraZ,
                cameraX+lookX, cameraY+lookY, cameraZ+lookZ,
                0.0f   , 1.0f,    0.0f);

    ticks = glutGet(GLUT_ELAPSED_TIME);
}

void Camera::loop()
{
    deltaTicks = glutGet(GLUT_ELAPSED_TIME) - ticks;
}

void Camera::calculaDirecao(void)
{
    float fator = deltaTicks/1000.f;
    angleX += deltaAngleX*fator;
    angleY += deltaAngleY*fator;

    //correct angle
    if ( angleX+angleOffsetX >= 360 )
        angleX -= 360;
    if ( angleX+angleOffsetX < 0)
        angleX += 360;

    //Only allows to rotate 180 degrees Y
    if ( angleY+angleOffsetY >= 90 )
        angleY = 90-angleOffsetY;
    if ( angleY+angleOffsetY <= -90)
        angleY = -(90+angleOffsetY);


    lookX = sin( (angleX+angleOffsetX)*M_PI/180);
    lookZ = cos( (angleX+angleOffsetX)*M_PI/180);

    lookY = sin( (angleY+angleOffsetY)*M_PI/180);
}
void Camera::calculaMovimento(float delta)
{
    //Add the movement
    float fator = deltaTicks/1000.f;

    //Factor delta times direction. 0.1f to adjust speed.
    cameraX += (delta*fator) * lookX;
    cameraZ += (delta*fator) * lookZ;
}
void Camera::calculaMovimentoLateral(float delta)
{
    float fator = deltaTicks/1000.f;

    float lateralX = sin( (angleX-90)*M_PI/180);
    float lateralZ = cos( (angleX-90)*M_PI/180);
    //Add the movement
    //Factor delta times direction. 0.1f to adjust speed.
    cameraX += (delta*fator) * (lateralX);
    cameraZ += (delta*fator) * (lateralZ);
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
        deltaMoveLado = -velocidadeMove;
    else
        deltaMoveLado = 0.0f;
}
void Camera::moveDireita(bool mover)
{
    if(mover)
        deltaMoveLado = velocidadeMove;
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

    if (xOrigem == -1) //Both will be necessarily -1
    {
        angleX +=angleOffsetX;
        angleY +=angleOffsetY;
        angleOffsetX = 0;
        angleOffsetY = 0;
    }
}
void Camera::moveMouse(int x, int y)
{
    deltaMouseX = deltaMouseY = 0;
    //If there was displacement
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

void Camera::setCorrer(void)
{
    velocidadeMove = velocidadeMoveCorre;
}
void Camera::setAndar(void)
{
    velocidadeMove = velocidadeMoveAndar;
}
