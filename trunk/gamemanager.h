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

        void calculaDirecao(void);
        void calculaMovimento(float delta);
        void calculaMovimentoLateral(float delta);

        void desenhaTela(void);
        void inicializa(void)
    public:
        void executa();
}


#endif
