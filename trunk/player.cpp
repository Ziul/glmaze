#include "player.h"

Player Player::PlayerControl;

//Chame init() para inicializar e colocá-lo na lista
Player::Player()
{
    Entidade();
    resetPosition();

}
void Player::resetPosition()
{
    Camera::CameraControl.reset();
    lastVida = 0;

    setTamanho(5);
    posicao.x = ((TAMANHO_BLOCO*1) + TAMANHO_BLOCO/2) - (tamanho.x/2);
    posicao.y = tamanho.y/2;
    posicao.z = ((TAMANHO_BLOCO*1) + TAMANHO_BLOCO/2) - (tamanho.z/2);
    showWired = true;
    score = 0;
    vidas = 1;
}

Player::~Player()
{
}
void Player::ajustaCamera()
{
    Camera::CameraControl.loop(); //Ajusta timer.

    float deltaMove = Camera::CameraControl.deltaMove;
    //Se estiver movendo (frente ou traz)
    if (deltaMove) //Se estiver colidido, nem calcula o movimento
    {   //Efetua movimento
        Camera::CameraControl.calculaMovimento(deltaMove);                        //Calcula posicao da camera
        Vetor3D pos;
        // menos tamanho.x para pegar o centro do cubo.
        pos.x = Camera::CameraControl.cameraX-(tamanho.x/2);
        pos.y = Camera::CameraControl.cameraY-(tamanho.y/2);
        pos.z = Camera::CameraControl.cameraZ-(tamanho.z/2);
        if( isColisaoMapa(pos) == false)  //Verifica se colidiu
            setPosicao(pos.x, pos.y, pos.z); // e setado para poder calcular colisoes com entidades no futuro
        else
            //Se colidir, então desfaz o movimento
            Camera::CameraControl.calculaMovimento(-deltaMove);                   //Recalcula para posicao anterior se colidiu
    }
    float deltaMoveLado = Camera::CameraControl.deltaMoveLado;
    //Se moviento lateral
    if (deltaMoveLado)
    {
        Camera::CameraControl.calculaMovimentoLateral(deltaMoveLado);
        Vetor3D pos;
        pos.x = Camera::CameraControl.cameraX-(tamanho.x/2);
        pos.y = Camera::CameraControl.cameraY-(tamanho.y/2);
        pos.z = Camera::CameraControl.cameraZ-(tamanho.z/2);
        if (isColisaoMapa(pos) == false)
            setPosicao(pos.x, pos.y, pos.z);
        else
            Camera::CameraControl.calculaMovimentoLateral(-deltaMoveLado);
    }

    Camera::CameraControl.ajustaCamera();

    render();
}
void Player::moveFrente(bool mover){
    Camera::CameraControl.moveFrente(mover);
}
void Player::moveTraz(bool mover){
    Camera::CameraControl.moveTraz(mover);
}
void Player::moveEsquerda(bool mover){
    Camera::CameraControl.moveEsquerda(mover);
}
void Player::moveDireita(bool mover){
    Camera::CameraControl.moveDireita(mover);
}
void Player::giraEsquerda(bool mover){
    Camera::CameraControl.giraEsquerda(mover);
}
void Player::giraDireita(bool mover){
    Camera::CameraControl.giraDireita(mover);
}
void Player::giraCima(bool mover){
    Camera::CameraControl.giraCima(mover);
}
void Player::giraBaixo(bool mover){
    Camera::CameraControl.giraBaixo(mover);
}
void Player::setMouse(int x, int y){
    Camera::CameraControl.setMouse(x,y);
}
void Player::moveMouse(int x, int y){
    Camera::CameraControl.moveMouse(x,y);
}
//temp como public
void Player::calculaDirecao(void){
    Camera::CameraControl.calculaDirecao();
}
//Liga ou desliga correr
void Player::setCorrer(void){
    Camera::CameraControl.setCorrer();
}
void Player::setAndar(void){
    Camera::CameraControl.setAndar();
    deltaTicks = glutGet(GLUT_ELAPSED_TIME);
}

//
void Player::loop()
{
    //int delta = glutGet(GLUT_ELAPSED_TIME) - deltaTicks;
    //float fator = delta/1000.f;
    //deltaTicks = glutGet(GLUT_ELAPSED_TIME);
    //testaColisao();
    ajustaCamera();

}
void Player::testaColisao()
{
    Tile* tileBall = 0;

    //Se for diferente de 0, isto é, NULL.
    if ( (tileBall = isColisaoMapa(posicao, TILE_TIPO_CHAO_COM_BOLA)) ) {
        //BOLA NORMAL, ACUMULA PONTOS
        score += PONTOS_BOLA;
        tileBall->typeId = TILE_TIPO_CHAO;
        ///TOCA SOM!!!!
        SoundAL sc;
        sc.play(SFX_eat);

    } else if ((tileBall = isColisaoMapa(posicao, TILE_TIPO_CHAO_COM_BOLA_ESPECIAL)) ){
        score += PONTOS_BOLA_ESPECIAL;
        tileBall->typeId = TILE_TIPO_CHAO;
        ///TOCA SOM!!!!
        SoundAL sc;
        sc.play(SFX_eat2);
    }

    //Executa

}
void Player::renderScore()
{
   txt::renderText2dOrtho(wScreen -100, 10,0,"Pontos:%d",score);
   txt::renderText2dOrtho(wScreen -160, 10,0,"Vidas:%d",vidas);
}
void Player::render()
{
    Entidade::render();
    renderScore();
}
void Player::executaColisao()
{
    if (!isColidido())
        return;
    Camera::CameraControl.calculaMovimento(-Camera::CameraControl.deltaMove);
    Camera::CameraControl.calculaMovimentoLateral(-Camera::CameraControl.deltaMoveLado);
    setPosicao(Camera::CameraControl.cameraX-(tamanho.x/2), Camera::CameraControl.cameraY-(tamanho.x/2), Camera::CameraControl.cameraZ-(tamanho.x/2));



    //se tiver passado 1.5 segundos desde a ultima vez que tomou dano.
    if ( (glutGet(GLUT_ELAPSED_TIME) - lastVida ) > 1500 ) {
        vidas--;
        lastVida = glutGet(GLUT_ELAPSED_TIME);
    }

    if (vidas <= 0) {
        menuPrincipal = true;
        status = STATUS_DERROTA;
        SoundAL sc;
        sc.stopAll();
        sc.play(SFX_die);
        alutSleep(2.0f);
        sc.play(SOUND_inter1);
    }


    entidadeColidida.clear();
}
