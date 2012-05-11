//==============================================================================
/*
    Classe que contera o metodo main e gerenciara o jogo.
*/
//==============================================================================
#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "defines.h"
#include "camera.h"
#include "framerate.h"
#include "map.h"
#include "text.h"
#include "entidade.h"
#include "textureloader.h"

class GameManager
{
    private:
        void inicializa(void);
        void inicializaRender(void);
        void loop(void);
        void cleanup(void);
    public:
        Entidade player;
        void render(void);
        void executa(int argc, char* args[]);
};


#endif
