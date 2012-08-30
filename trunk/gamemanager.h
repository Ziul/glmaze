//==============================================================================
/*
    Classe que contera o metodo main e gerenciara o jogo.
    Class that will have the main method and care the game
*/
//==============================================================================
#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_
#include <cstdlib>
#include "defines.h"
#include "camera.h"
#include "framerate.h"
#include "map.h"
#include "text.h"
#include "entidade.h"
#include "player.h"
#include "minimap.h"
#include "button.h"
#include "soundAL.h"
#include "textureloader.h"

#define MAX_ENEMY 8

///Note: the cleanup .cpp is called by atExit() in stdlib
class GameManager
{
    private:
        void inicializa(void);
        void inicializaRender(void);
        void inicializaSons(void);
        void loop(void);

        Entidade* enemy[MAX_ENEMY];

        //SoundController ... Controls sound
        SoundAL sc;

        unsigned int ticksAttack;
    public:
        void resetPositions(void);
        ~GameManager();
        void render(void);
        void executa(int argc, char* args[]);
};


#endif
