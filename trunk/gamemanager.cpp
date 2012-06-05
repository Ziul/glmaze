#include "gamemanager.h"
#include "eventos.h"

GameManager game;

void startButtonAction()
{
    menuPrincipal = false;
    for(unsigned int i = 0;i < Entidade::EntidadeList.size(); i++)
        Entidade::EntidadeList[i]->init();
}
void changeSize(int w, int h)
{
    //Previne divisao por zero
    if ( h == 0)
        h = 1;

    float ratio = w*1.0 / h;

    //Usa matriz de projecao
    glMatrixMode(GL_PROJECTION);
    //Reseta matriz
    glLoadIdentity();

    //Arruma viewport para janela inteira
    glViewport(0,0,w,h);

    //Arruma a perspectiva correta
    gluPerspective(45.0f, ratio, 1, GAME_FOV*TAMANHO_BLOCO);

    //Volta para o modelView
    glMatrixMode(GL_MODELVIEW);

    wScreen = w;
    hScreen = h;
}
void GameManager::inicializaRender(void)
{
    //Transparencia
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);

    glEnable(GL_LIGHTING); //Habilita luz
    glEnable(GL_LIGHT0); //Habilita luz #0
    glEnable(GL_LIGHT1); //Habilita luz #0
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHT1); //Habilita luz #1

    glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH); //Shading

    glEnable(GL_CULL_FACE); //Reduz quantidade de triangulos desenhados.
    glCullFace(GL_CW);

    wallTexture = texture::loadTextureBMP("data/wall.bmp");
    floorTexture = texture::loadTextureBMP("data/floor.bmp");


}
void GameManager::inicializa(void)
{
    inicializaRender();
//---------------------------
    //Especifica a cor de fundo
    glClearColor(0.3f,0.3f,0.9f,1.0f);





    GLfloat fog_color[4] = {0.0f,0.0f,0.0f,1.0};
    glFogfv(GL_FOG_COLOR, fog_color);
    glFogf(GL_FOG_DENSITY, 0.35f);

    glFogi(GL_FOG_MODE, GL_LINEAR);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, TAMANHO_BLOCO*4.0f);
    glFogf(GL_FOG_END, TAMANHO_BLOCO*10.0f);
    glEnable(GL_FOG);

    Map::MapControl.load((char*) "map_pacman_new.txt");

    //Testes menu
    menuPrincipal = true;

    Button* start = new Button();

    start->setXY(220, 200);
    start->setEstados(1, 350, 60, 0);

    start->ClickAction = startButtonAction;

    Button::ButtonList.push_back(start);

    //testes
    Entidade* enemy1 = new Entidade();
    Entidade* enemy2 = new Entidade();


    enemy1->init();
    enemy1->posicao.x = 12*4;
    enemy1->posicao.y = 0;
    enemy1->posicao.z = 12*1;

    enemy1->aceleracao.x = 10.f;
    enemy1->aceleracao.z = 0.2f;

    enemy1->setTamanho(5);
    enemy1->addToEntidadeList();
    //
    enemy2->init();
    enemy2->posicao.x = 12*3;
    enemy2->posicao.y = 0;
    enemy2->posicao.z = 12*1;

    enemy2->aceleracao.x = 15.f;
    enemy2->aceleracao.z = 4.2f;

    enemy2->setTamanho(5);
    enemy2->addToEntidadeList();

    Player::PlayerControl.init();
    Player::PlayerControl.addToEntidadeList();

}
void desenhaTela(void)
{

    game.render();


    glutSwapBuffers();
}

void GameManager::loop(void)
{

    FrameRate::FPSControl.loop();
    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
    {
        Entidade::EntidadeList[i]->loop();
    }
    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
    {
        Entidade::EntidadeList[i]->testaColisao();
    }
    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
    {
        Entidade::EntidadeList[i]->executaColisao();
    }

}
void GameManager::render(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (menuPrincipal)
    {
        for(unsigned int i = 0; i < Button::ButtonList.size();i++)
            Button::ButtonList[i]->render();

        txt::renderText2dOrtho(30,150,8,"Aperte o grande quadrado branco para comecar!!!");

        return; /// IGNORA ABAIXO
    }




    //Iluminacao
    GLfloat ambientLight[] = {0.1f, 0.1f, 0.1f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 0.0f};
	GLfloat directedLightPos[] = {0.0f, 20.0f, -20.0f, 1.0f};
	GLfloat light[] = {0.9f, 0.9f, 0.9f, 1.0f};
	GLfloat lightPos[] = {100.0f, 30.0f, -10.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
    //Fim Iluminacao


    //Calcula iteracoes
    this->loop();

    //Imprime SOL's
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(directedLightPos[0],directedLightPos[1],directedLightPos[2]);
        glutSolidSphere(10.0f, 18.0f, 18.0f);
	glPopMatrix();
	glPushMatrix();
        glColor3f(1.0f, 0.0f, 0.0f);
        glTranslatef(lightPos[0],lightPos[1],lightPos[2]);
        glutSolidSphere(10.0f, 18.0f, 18.0f);
	glPopMatrix();

    Map::MapControl.render();
    //unsigned int temp = Entidade::EntidadeList.size();
    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
    {
        if (Entidade::EntidadeList[i]->isVisible())
            Entidade::EntidadeList[i]->render();
    }

    txt::renderText2dOrtho(10,15,0,"FPS: %.2f",FrameRate::FPSControl.getFPS());




	MiniMap::renderMiniMap();

}

//Quanda chamado cleanup durante o destructor ocorre falha de
//segmentação somente no delete Entidade
GameManager::~GameManager()
{
}
void cleanup(void)
{
    printf("Entidade cleanup size: %d\n", Entidade::EntidadeList.size());
    for(unsigned int i = 0; i < Entidade::EntidadeList.size();i++)
        delete Entidade::EntidadeList[i];
    printf("Button cleanup size: %d\n", Button::ButtonList.size());
    for(unsigned int i = 0; i < Button::ButtonList.size(); i++)
        delete Button::ButtonList[i];
}
void testOpenAL()
{
    unsigned int g_buf = -1;
    unsigned int g_src = -1;

    if(!alutInit(NULL, NULL))
    {
        printf("%s",alutGetErrorString(alutGetError()));
        return;
    }
    alGetError();
    alutGetError();

    g_buf = alutCreateBufferFromFile("testing.wav");

    if (alutGetError() != ALUT_ERROR_NO_ERROR)
     {
         alDeleteBuffers(1, &g_buf);
         alutExit();
         return;
     }

     alGenSources(1, &g_src);

     if(alGetError() != AL_NO_ERROR)
     {
         alDeleteBuffers(1, &g_buf);
         alDeleteSources(1, &g_buf);
         alutExit();
         return;
     }

     alSourcei(g_src, AL_BUFFER, g_buf);

     alSourcePlay(g_src);
     alutSleep(4.0f);

     alutExit();
}
void testSoundALClass()
{
    SoundAL sn;
    sn.init();

    int m_i = sn.loadSound("testing.wav", 1);
    sn.play(m_i);

    alutSleep(4.0f);

    sn.exit();
}
int main(int argc, char* args[])
{

    testOpenAL();
    testSoundALClass();

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

    atexit(cleanup);

    glutIgnoreKeyRepeat(0);
    //Entra no loop de processamento de eventos
    glutMainLoop();
}

