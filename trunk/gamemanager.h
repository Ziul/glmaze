//==============================================================================
/*
    Classe que conterá o método main e gerenciará o jogo.
*/
//==============================================================================
#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

class GameManager
{
    private:
        void changeSize(int w, int h);
        void inicializa(void);
        void loop(void);
        void render(void);
        void cleanup(void);
    public:
        void executa();
};


#endif
