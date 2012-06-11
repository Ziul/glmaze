#include "eventos.h"

#include "gamemanager.h"

#include "player.h"

void teclasNormais(unsigned char key, int x, int y)
{
    if (menuPrincipal)
        return; /// IGNORA ABAIXO

    int mod = glutGetModifiers();
    if (mod == GLUT_ACTIVE_SHIFT)
        Player::PlayerControl->setCorrer();
    else
        Player::PlayerControl->setAndar();

    switch(key)
    {
        case 27:  //ESC
            exit(0);
            break;
        case 'W':
        case 'w':
        {
            Player::PlayerControl->moveFrente(true);
            break;
        }
        case 'S':
        case 's':
        {

            Player::PlayerControl->moveTraz(true);
            break;
        }

        case 'A':
        case 'a':
            Player::PlayerControl->moveEsquerda(true);
            break;
        case 'D':
        case 'd':
            Player::PlayerControl->moveDireita(true);
            break;
        case 'Q':
        case 'q':
            Player::PlayerControl->giraEsquerda(true);
            break;
        case 'E':
        case 'e':
            Player::PlayerControl->giraDireita(true);
            break;
        case '2':
            Player::PlayerControl->giraCima(true);
            break;
        case '3':
            Player::PlayerControl->giraBaixo(true);
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
    if (menuPrincipal)
        return; /// IGNORA ABAIXO

    switch(key)
    {
        case 'W':
        case 'w':
            Player::PlayerControl->moveFrente(false);
            break;
        case 'S':
        case 's':
            Player::PlayerControl->moveTraz(false);
            break;
        case 'A':
        case 'a':
            Player::PlayerControl->moveEsquerda(false);
            break;
        case 'D':
        case 'd':
            Player::PlayerControl->moveDireita(false);
            break;
        case 'Q': case 'q':
            Player::PlayerControl->giraEsquerda(false);
            break;
        case 'E': case 'e':
            Player::PlayerControl->giraDireita(false);
            break;
        case '2':
            Player::PlayerControl->giraCima(false);
            break;
        case '3':
            Player::PlayerControl->giraBaixo(false);
            break;
        default:break;

    }
}

void teclasEspeciais(int key, int x, int y )
{
    if (menuPrincipal)
        return; /// IGNORA ABAIXO

    switch(key)
    {
        case GLUT_KEY_UP: Player::PlayerControl->moveFrente(true); break;
        case GLUT_KEY_DOWN: Player::PlayerControl->moveTraz(true); break;
        case GLUT_KEY_LEFT: Player::PlayerControl->giraEsquerda(true); break;
        case GLUT_KEY_RIGHT: Player::PlayerControl->giraDireita(true); break;
        default: break;
    }


}

void teclasEspeciaisSoltar(int key, int x, int y)
{
    if (menuPrincipal)
        return; /// IGNORA ABAIXO

    switch(key)
    {
        case GLUT_KEY_UP: Player::PlayerControl->moveFrente(false); break;
        case GLUT_KEY_DOWN: Player::PlayerControl->moveTraz(false); break;
        case GLUT_KEY_LEFT: Player::PlayerControl->giraEsquerda(false); break;
        case GLUT_KEY_RIGHT: Player::PlayerControl->giraDireita(false); break;
        default: break;
    }
}

void mouseButton(int button, int state, int x, int y)
{
    if (menuPrincipal)
    {
        for(unsigned int i = 0; i < Button::ButtonList.size();i++)
            Button::ButtonList[i]->handleMouse(button, state, x, y);
        return; /// IGNORA ABAIXO
    }

    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP) //Reseta posicoes e ajusta deslocamento
        {
            Player::PlayerControl->setMouse(-1,-1);
        }
        else
        {
            Player::PlayerControl->setMouse(x,y);
        }
    }
}

void moveMouse(int x, int y)
{
    if (menuPrincipal)
        return; /// IGNORA ABAIXO

    Player::PlayerControl->moveMouse(x,y);
}
