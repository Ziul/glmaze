#include "gamemanager.h"
#include "eventos.h"
#include <time.h>
GameManager game;

void startButtonAction()
{
    menuPrincipal = false;

    game.resetPositions();

    SoundAL sc;
    sc.stopAll();
    sc.play(SOUND_inter2);
}
void changeSize(int w, int h)
{
    //Prevents division by zero
    if ( h == 0)
        h = 1;

    float ratio = w*1.0 / h;

    //Uses projection matrix
    glMatrixMode(GL_PROJECTION);
    //Reseta matriz
    glLoadIdentity();

    //Arranges viewport to entire window
    glViewport(0,0,w,h);

    //Arranges the right perspective
    gluPerspective(45.0f, ratio, 1, GAME_FOV*TAMANHO_BLOCO);

    //Back to modelView
    glMatrixMode(GL_MODELVIEW);

    wScreen = w;
    hScreen = h;
}
void GameManager::inicializaRender(void)
{
    //transparency
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);

    glEnable(GL_LIGHTING); //enables light
    glEnable(GL_LIGHT0); //enables light #0
    glEnable(GL_LIGHT1); //enables lightz #0
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHT1); //enables light #1

    glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH); //Shading

    glEnable(GL_CULL_FACE); //Reduces the amount of triangles drawn.
    glCullFace(GL_CW);

    wallTexture = texture::loadTextureBMP("data/wall.bmp");
    floorTexture = texture::loadTextureBMP("data/floor.bmp");


}
void GameManager::inicializa(void)
{
    inicializaRender();
    inicializaSons();

//---------------------------
    //Specifies the background color
    glClearColor(0.3f,0.3f,0.9f,1.0f);

    GLfloat fog_color[4] = {0.0f,0.0f,0.0f,1.0};
    glFogfv(GL_FOG_COLOR, fog_color);
    glFogf(GL_FOG_DENSITY, 0.35f);

    glFogi(GL_FOG_MODE, GL_LINEAR);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, TAMANHO_BLOCO*4.0f);
    glFogf(GL_FOG_END, TAMANHO_BLOCO*10.0f);
    glEnable(GL_FOG);

    //Tests menu
    menuPrincipal = true;

    Button* start = new Button();

    start->setXY(220, 200);
    start->setEstados(1, 350, 60, 0);

    start->ClickAction = startButtonAction;

    Button::ButtonList.push_back(start);

    for(unsigned int i = 0; i < MAX_ENEMY; i++) {
        enemy[i] = new Entidade();
        enemy[i]->addToEntidadeList();
        enemy[i]->setTamanho(5);
    }

    Player::PlayerControl = new Player();
    Player::PlayerControl->addToEntidadeList();

}

void GameManager::inicializaSons(void)
{
    sc.init();

    SOUND_main = sc.loadSound("data/mus/main.wav", 1);
    SOUND_inter1 = sc.loadSound("data/mus/M1.WAV", 1);	//Linux & MAC are sensitive case 
    SOUND_inter2 = sc.loadSound("data/mus/M2.WAV", 1);
    SOUND_inter3 = sc.loadSound("data/mus/M3.WAV", 1);
    SOUND_attack = sc.loadSound("data/mus/atk.wav", 1);

    SFX_die = sc.loadSound("data/sfx/die.wav", 0);
    SFX_eat = sc.loadSound("data/sfx/eat.wav", 0);
    SFX_eat2 = sc.loadSound("data/sfx/eat2.wav", 0);
    SFX_alert = sc.loadSound("data/sfx/alert.wav", 0);


    sc.play(SOUND_inter1);


}
void GameManager::resetPositions(void)
{
    printf("Posicoes resetadas: %lu\n", Entidade::EntidadeList.size());

    Map::MapControl.load((char*) "map_pacman_new.txt");

    srand( time(NULL) );

    for(int i = 0; i < MAX_ENEMY; i++) {
        enemy[i]->setRandomPosition();
    }

    Player::PlayerControl->init();
    Player::PlayerControl->resetPosition();
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


    //Verifies change of states on the special ball
    if(attack_mode == 1) //notified change and play music
    {
        //Ste SPECIAL flag active for all entities. Even the player
        for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
        {
            Entidade::EntidadeList[i]->flags = ENTIDADE_FLAG_ESPECIAL;
        }
        Player::PlayerControl->flags = ENTIDADE_FLAG_PLAYER_ESPECIAL; // resets the player's flag
        ticksAttack = glutGet(GLUT_ELAPSED_TIME);
        sc.stopAll();
        sc.play(SFX_alert);
        attack_mode = 2;
    } else
    if (attack_mode == 2)
    {
        //after 3 seconds
        if( (glutGet(GLUT_ELAPSED_TIME) - ticksAttack) > 3000 )
        {
            sc.stopAll();
            sc.play(SOUND_attack);
            attack_mode = 3;
            ticksAttack = glutGet(GLUT_ELAPSED_TIME);
        }
    } else
    if (attack_mode == 3)
    {
        //over the end of the ball efects 10 seconds + 3 the preceding sfx
        if( (glutGet(GLUT_ELAPSED_TIME) - ticksAttack) > 10000)
        {
            sc.stopAll();
            sc.play(SOUND_inter2);
            attack_mode = 0;
            for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
            {
                Entidade::EntidadeList[i]->flags = ENTIDADE_FLAG_NENHUM;
            }
            Player::PlayerControl->flags = ENTIDADE_FLAG_PLAYER_NORMAL; // resets the player's flag
        }
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

        switch(status)
        {
            case STATUS_DERROTA:
                txt::renderText2dOrtho(30,130,8,"Derrota!!!");
                break;
            case STATUS_NORMAL:
                txt::renderText2dOrtho(30,130,8,"Novo jogo!!!");
                break;
            case STATUS_VITORIA:
                txt::renderText2dOrtho(30,130,8,"Vitoria!!!");
                break;
                default:;
        }

        return; 
    }




    //Lighting
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
    //end of lighting


    //calculates iterations
    this->loop();

    //Print SOL's
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


// when called during cleanup destructor,
// segmentation fault occurs only delete the Entity
GameManager::~GameManager()
{
    sc.stopAll();
    sc.exit();
}
void cleanup(void)
{
    unsigned int sizeEnt = Entidade::EntidadeList.size();
    unsigned int sizeBtn = Button::ButtonList.size();
    printf("Entidade cleanup size: %u\n", sizeEnt);
    for(unsigned int i = 0; i < sizeEnt; i++)
        delete Entidade::EntidadeList[i];
    printf("Button cleanup size: %u\n", sizeBtn);
    for(unsigned int i = 0; i < sizeBtn; i++)
        delete Button::ButtonList[i];
    printf("EXIT\n");
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

    //testOpenAL();
    //testSoundALClass();

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
    //Get in the loop processing events
    glutMainLoop();
}

