#include "gamemanager.h"
#include "eventos.h"

GameManager game;

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
void GameManager::inicializa(void)
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
    //glEnable(GL_NORMALIZE);

    Map::MapControl.load((char*) "test.txt");

    //testes
    player.reset();
    player.addToEntidadeList();
    player.posicao.x = 12*2+6;
    player.posicao.y = 0;
    player.posicao.z = 12 + 4;

    player.aceleracao.x = 10.f;
    player.aceleracao.z = 0.2f;

    player.setTamanho(5);





}
void desenhaTela(void)
{
    game.render();
}

void GameManager::loop(void)
{
    FrameRate::FPSControl.loop();
    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
    {
        Entidade::EntidadeList[i]->loop();
    }

}
void GameManager::render(void)
{
    //Calcula iterações
    this->loop();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat posicaoLuz[4] = {-200.0, 100.0, 0.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);


    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    Camera::CameraControl.ajustaCamera();


    Map::MapControl.render();
    //unsigned int temp = Entidade::EntidadeList.size();
    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
    {
        if (Entidade::EntidadeList[i]->isVisible())
            Entidade::EntidadeList[i]->render();
    }

    txt::renderText2dOrtho(10,10,0,"FPS: %.2f",FrameRate::FPSControl.getFPS());

    glutSwapBuffers();
}
void GameManager::cleanup(void)
{
    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
    {
        delete Entidade::EntidadeList[i];
    }
}


int main(int argc, char* args[])
{
    game.executa(argc, args);
    return 0;
}
void GameManager::executa(int argc, char* args[])
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
}

