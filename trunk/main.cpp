#include "defines.h"
#include <math.h>

#include "map.h"

float angle = 0.0f;

float lookX = 0.5f;
float lookY = 0.0f;
float lookZ = -1.0f;

float cameraX = 0.0f;
float cameraY = 5.0f;
float cameraZ = 30.0f;

float deltaAngle = 0.0f;
float deltaMove = 0.0f;
float deltaMoveLado = 0.0f;

float velocidadeMove = 0.2f;
float velocidadeVira = 0.1f;
int xOrigem;

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
            deltaAngle = -velocidadeVira;
            break;
        case 'D':
        case 'd':
            deltaAngle = velocidadeVira;
            break;
        case 'Q':
        case 'q':
            deltaMoveLado = velocidadeMove;
            break;
        case 'E':
        case 'e':
            deltaMoveLado = -velocidadeMove;
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
            deltaAngle = 0.0f;
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
        case GLUT_KEY_UP: deltaMove = 0.5f; break;
        case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
        default: break;
    }
}

void teclasEspeciaisSoltar(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT: deltaAngle = 0.0f; break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN: deltaMove = 0.0f; break;
        default: break;
    }
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP)
            ;
    }
}

void moveMouse(int x, int y)
{

}

void calculaDirecao(float delta)
{
    angle += delta;
    lookX = sin(angle*M_PI/180);
    lookZ = -cos(angle*M_PI/180);
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
    float lateralX = sin( (angle-90)*M_PI/180);
    float lateralZ = -cos( (angle-90)*M_PI/180);
    //Adiciona ao movimento
    //Fator delta vezes direção. 0.1f para ajustar velocidade.
    cameraX += delta * (lateralX) * 0.1f;
    cameraZ += delta * (lateralZ) * 0.1f;

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
    if (deltaAngle)
        calculaDirecao(deltaAngle);
    if (deltaMoveLado)
        calculaMovimentoLateral(deltaMoveLado);

    gluLookAt(  cameraX      , cameraY      , cameraZ,
                cameraX+lookX, cameraY+lookY, cameraZ+lookZ,
                0.0f   , 1.0f,    0.0f);




    glColor3f(0.3f, 0.9f, 0.2f);
    glPushMatrix();
        glTranslated(0,5,0);
        glutSolidCube(10);
        glTranslated(10,0,0);
        glutSolidCube(10);
        glTranslated(10,0,0);
        glutSolidCube(10);
        glTranslated(0,0,10);
        glutSolidCube(10);
        glTranslated(0,0,10);
        glutSolidCube(10);
        glTranslated(-10,0,0);
        glutSolidCube(10);
        glTranslated(0,0,10);
        glutSolidCube(10);
        glTranslated(0,0,10);
        glutSolidCube(10);

        glTranslated(0,0,10);
        glutSolidCube(10);
        glTranslated(-10,0,0);
        glutSolidCube(10);
        glTranslated(-10,0,0);
        glutSolidCube(10);
        glTranslated(0,0,-10);
        glutSolidCube(10);
        glTranslated(0,0,-10);
        glutSolidCube(10);
        glTranslated(0,0,-10);
        glutSolidCube(10);


        glTranslated(-10,0,0);
        glutSolidCube(10);
        glTranslated(0,0,10);
        glutSolidCube(10);
        glTranslated(0,0,10);
        glutSolidCube(10);
        glTranslated(-10,0,0);
        glutSolidCube(10);
        glTranslated(-10,0,0);
        glutSolidCube(10);

        glTranslated(0,0,-10);
        glutWireCube(10);
        glTranslated(0,0,-10);
        glutSolidCube(10);
        glTranslated(0,0,-10);
        glutSolidCube(10);
        glTranslated(-10,0,0);
        glutSolidCube(10);

        glTranslated(0,0,-10);
        glutSolidCube(10);



        glTranslated(10,0,0);
        glutSolidCube(10);

        glTranslated(10,0,0);
        glutSolidCube(10);

        glTranslated(10,0,0);
        glutSolidCube(10);
        glTranslated(10,0,0);
        glutSolidCube(10);



    glPopMatrix();


    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();



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

    calculaDirecao(0.0f);
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
    glutMotionFunc(moveMouse);
    glutMouseFunc(mouseButton);

    glutIgnoreKeyRepeat(0);
    //Entra no loop de processamento de eventos
    glutMainLoop();

    return 0;

}


