#include "eventos.h"

#include "gamemanager.h"

void teclasNormais(unsigned char key, int x, int y)
{

    int mod = glutGetModifiers();
    if (mod == GLUT_ACTIVE_SHIFT)
        Camera::CameraControl.setCorrer();
    else
        Camera::CameraControl.setAndar();

    switch(key)
    {
        case 27:  //ESC
            exit(0);
            break;
        case 'W':
        case 'w':
        {
            Camera::CameraControl.moveFrente(true);
            break;
        }
        case 'S':
        case 's':
        {

            Camera::CameraControl.moveTraz(true);
            break;
        }

        case 'A':
        case 'a':
            Camera::CameraControl.moveEsquerda(true);
            break;
        case 'D':
        case 'd':
            Camera::CameraControl.moveDireita(true);
            break;
        case 'Q':
        case 'q':
            Camera::CameraControl.giraEsquerda(true);
            break;
        case 'E':
        case 'e':
            Camera::CameraControl.giraDireita(true);
            break;
        case '2':
            Camera::CameraControl.giraCima(true);
            break;
        case '3':
            Camera::CameraControl.giraBaixo(true);
            break;
        case '1': // reseta angulo Y
            Camera::CameraControl.angleY = 0;
            Camera::CameraControl.calculaDirecao();
            break;
        case 'Z':
        case 'z':
            Camera::CameraControl.cameraY += 2;
            break;
        case 'X':
        case 'x':
            Camera::CameraControl.cameraY -= 2;
            break;
        case 'C':
        case 'c':
            Camera::CameraControl.cameraX = 6;
            break;
        case 'V':
        case 'v':
            Camera::CameraControl.cameraY = 3;
            break;
        case 'B':
        case 'b':
            Camera::CameraControl.cameraZ = 6;
            break;
        case 'F':
        case 'f':
        {
            GLboolean isFog = false;
            glGetBooleanv(GL_FOG, &isFog);
            if (isFog)
                glDisable(GL_FOG);
            else
                glEnable(GL_FOG);

            break;

        }
        case 'R':
        case 'r':
            if (FrameRate::FPSControl.isFPSCap())
                FrameRate::FPSControl.setFPSCap(false);
            else
                FrameRate::FPSControl.setFPSCap(true);
            break;
        default:break;
    }
}
void teclasNormaisUp(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'W':
        case 'w':
            Camera::CameraControl.moveFrente(false);
            break;
        case 'S':
        case 's':
            Camera::CameraControl.moveTraz(false);
            break;
        case 'A':
        case 'a':
            Camera::CameraControl.moveEsquerda(false);
            break;
        case 'D':
        case 'd':
            Camera::CameraControl.moveDireita(false);
            break;
        case 'Q': case 'q':
            Camera::CameraControl.giraEsquerda(false);
            break;
        case 'E': case 'e':
            Camera::CameraControl.giraDireita(false);
            break;
        case '2':
            Camera::CameraControl.giraCima(false);
            break;
        case '3':
            Camera::CameraControl.giraBaixo(false);
            break;
        default:break;

    }
}

void teclasEspeciais(int key, int x, int y )
{

    switch(key)
    {
        case GLUT_KEY_UP: Camera::CameraControl.moveFrente(true); break;
        case GLUT_KEY_DOWN: Camera::CameraControl.moveTraz(true); break;
        case GLUT_KEY_LEFT: Camera::CameraControl.giraEsquerda(true); break;
        case GLUT_KEY_RIGHT: Camera::CameraControl.giraDireita(true); break;
        default: break;
    }


}

void teclasEspeciaisSoltar(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP: Camera::CameraControl.moveFrente(false); break;
        case GLUT_KEY_DOWN: Camera::CameraControl.moveTraz(false); break;
        case GLUT_KEY_LEFT: Camera::CameraControl.giraEsquerda(false); break;
        case GLUT_KEY_RIGHT: Camera::CameraControl.giraDireita(false); break;
        default: break;
    }
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP) //Reseta posicoes e ajusta deslocamento
        {
            Camera::CameraControl.setMouse(-1,-1);
        }
        else
        {
            Camera::CameraControl.setMouse(x,y);
        }
    }
}

void moveMouse(int x, int y)
{
    Camera::CameraControl.moveMouse(x,y);
}
