#include "defines.h"
#include <math.h>

#include "map.h"
#include "text.h"
#include "framerate.h"

float angleX = 90.0f;
float angleY = 0.0f;
float angleOffsetX = 0;
float angleOffsetY = 0;

float lookX = 0.5f;
float lookY = 0.0f;
float lookZ = -1.0f;

float cameraX = TAMANHO_BLOCO/2;
float cameraY = 5.0f;
float cameraZ = TAMANHO_BLOCO/2;

float deltaAngleX = 0.0f; //Angulo de rotação da direção horizontal
float deltaAngleY = 0.0f; //Vertical

float deltaMouseX = 0.0f;
float deltaMouseY = 0.0f;

float deltaMove = 0.0f;
float deltaMoveLado = 0.0f;

float velocidadeMove = 1.0f;
float velocidadeVira = 0.5f;
int xOrigem = -1;
int yOrigem = -1;

FrameRate fps;


void changeSize(int w, int h)
{
    //Previne divisão por zero
    if ( h == 0)
        h = 1;

    float ratio = w*1.0 / h;

    //Usa matriz de projeção
    glMatrixMode(GL_PROJECTION);
    //Reseta matriz
    glLoadIdentity();

    //Arruma viewport para janela inteira
    glViewport(0,0,w,h);

    //Arruma a perspectiva correta
    gluPerspective(45.0f, ratio, 1, 1000);

    //Volta para o modelView
    glMatrixMode(GL_MODELVIEW);

    wScreen = w;
    hScreen = h;
}

void calculaDirecao()
{

    angleX += deltaAngleX;

    lookX = sin( (angleX+angleOffsetX)*M_PI/180);
    lookZ = -cos( (angleX+angleOffsetX)*M_PI/180);

    lookY = sin( (angleY+angleOffsetY)*M_PI/180);
}

void calculaMovimento(float delta)
{
    //Adiciona ao movimento
    //Fator delta vezes direção. 0.1f para ajustar velocidade.
    cameraX += delta * lookX * 0.1f;
    cameraZ += delta * lookZ * 0.1f;
}
void calculaMovimentoLateral(float delta)
{
    float lateralX = sin( (angleX-90)*M_PI/180);
    float lateralZ = -cos( (angleX-90)*M_PI/180);
    //Adiciona ao movimento
    //Fator delta vezes direção. 0.1f para ajustar velocidade.
    cameraX += delta * (lateralX) * 0.1f;
    cameraZ += delta * (lateralZ) * 0.1f;

}

void teclasNormais(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:  //ESC
            exit(0);
            break;
        case 'W':
        case 'w':
            deltaMove = velocidadeMove;
            break;
        case 'S':
        case 's':
            deltaMove = -velocidadeMove;
            break;
        case 'A':
        case 'a':
            deltaAngleX = -velocidadeVira;
            break;
        case 'D':
        case 'd':
            deltaAngleX = velocidadeVira;
            break;
        case 'Q':
        case 'q':
            deltaMoveLado = velocidadeMove;
            break;
        case 'E':
        case 'e':
            deltaMoveLado = -velocidadeMove;
            break;
        case '1': // reseta angulo Y
            angleY = 0;
            calculaDirecao();
            break;
        case 'Z':
        case 'z':
            cameraY += 2;
            break;
        case 'X':
        case 'x':
            cameraY -= 2;
            break;
        case 'C':
        case 'c':
            cameraX = 6;
            break;
        case 'V':
        case 'v':
            cameraY = 1;
            break;
        case 'B':
        case 'b':
            cameraZ = 6;
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
            if (fps.fpsControl)
                fps.fpsControl = false;
            else
                fps.fpsControl = true;
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
        case 'S':
        case 's':
            deltaMove = 0.0f;
            break;
        case 'A':
        case 'a':
        case 'D':
        case 'd':
            deltaAngleX = 0.0f;
            break;
        case 'Q': case 'q':
        case 'E': case 'e':
            deltaMoveLado = 0.0f;
            break;
        default:break;

    }
}

void teclasEspeciais(int key, int x, int y )
{
    switch(key)
    {
        case GLUT_KEY_UP: deltaMove = velocidadeMove; break;
        case GLUT_KEY_DOWN: deltaMove = -velocidadeMove; break;
        case GLUT_KEY_LEFT: deltaAngleX = -velocidadeVira; break;
        case GLUT_KEY_RIGHT: deltaAngleX = velocidadeVira; break;
        default: break;
    }
}

void teclasEspeciaisSoltar(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT: deltaAngleX = 0.0f; break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN: deltaMove = 0.0f; break;
        default: break;
    }
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP) //Reseta posições e ajusta deslocamento
        {
            xOrigem = -1;
            yOrigem = -1;


            angleX +=angleOffsetX;
            angleY +=angleOffsetY;
            angleOffsetX = 0;
            angleOffsetY = 0;
        }
        else
        {
            xOrigem = x;
            yOrigem = y;
        }
    }
}

void moveMouse(int x, int y)
{
    deltaMouseX = deltaMouseY = 0;
    //Se houve deslocamento
    if (xOrigem>0)
    {
        angleOffsetX = -(xOrigem-x) * 0.1f;
    }
    if (yOrigem>0)
    {
        angleOffsetY = (yOrigem-y) * 0.1f;
    }
    calculaDirecao();

}



void desenhaTela(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat posicaoLuz[4] = {-200.0, 100.0, 0.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    if (deltaMove)
        calculaMovimento(deltaMove);
    if (deltaMoveLado)
        calculaMovimentoLateral(deltaMoveLado);
    if (deltaAngleX)
        calculaDirecao();

    gluLookAt(  cameraX      , cameraY      , cameraZ,
                cameraX+lookX, cameraY+lookY, cameraZ+lookZ,
                0.0f   , 1.0f,    0.0f);

    //MazeHARDCORE();



    Map::MapControl.render();


    glColor3f(0.9f, 0.9f, 0.0f);
    glBegin(GL_QUADS);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.0f, 1.0f, TAMANHO_BLOCO);
            glVertex3f(TAMANHO_BLOCO, 1.0f, TAMANHO_BLOCO);
            glVertex3f(TAMANHO_BLOCO, 1.0f, 0.0f);
    glEnd();


    fps.execute();

    renderText2dOrtho(10,10,0,"FPS: %.2f",fps.getFPS());

    glutSwapBuffers();
}

void inicializa(void)
{
    //Propriedades de luz
    GLfloat luzAmbiente[4] = {0.1, 0.1, 0.1, 1.0 };
    GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0 };   // cor
    GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0 }; // brilho
    GLfloat posicaoLuz[4] = {-30.0, 10.0, 0.0, 0.0 };

    //Capacidade de brilho do material
    GLfloat especularidade[4] = { 1.0, 1.0, 1.0, 1.0};
    GLint especMaterial = 20;

    //Define a refletancia do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    //COncentração do brilho
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

    //Ativa uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    //Luz de numero 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    //Definição da cor do material
    glEnable(GL_COLOR_MATERIAL);
    //uso de iluminação
    glEnable(GL_LIGHTING);
    //habilita luz 0
    glEnable(GL_LIGHT0);
//---------------------------
    //Especifica a cor de fundo
    glClearColor(0.0f,0.0f,0.0f,1.0f);

    //Habilita modelo de colorização de gouraud
    glShadeModel(GL_SMOOTH);

    //Habilita depth-buffering
    glEnable(GL_DEPTH_TEST);
    //Reduz quantidade de triangulos desenhados.
    glEnable(GL_CULL_FACE);

    GLfloat fog_color[4] = {0.1,0.1,0.1,1.0};
    glFogfv(GL_FOG_COLOR, fog_color);
    glFogf(GL_FOG_START, 0.0f );
    glFogf(GL_FOG_END, 30.0f );
    glFogi(GL_FOG_MODE, GL_LINEAR);

    glEnable(GL_FOG);

    Map::MapControl.load((char*) "test.txt");

    calculaDirecao();
}

int main(int argc, char* args[])
{
    glutInit(&argc, args);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Labirinth");

    inicializa();

    glutDisplayFunc(desenhaTela);
    glutReshapeFunc(changeSize);
    glutIdleFunc(desenhaTela);

    glutKeyboardFunc(teclasNormais);
    glutKeyboardUpFunc(teclasNormaisUp);
    glutSpecialFunc(teclasEspeciais);
    glutSpecialUpFunc(teclasEspeciaisSoltar);
    glutMotionFunc(moveMouse);
    glutMouseFunc(mouseButton);

    glutIgnoreKeyRepeat(0);
    //Entra no loop de processamento de eventos
    glutMainLoop();

    return 0;

}


