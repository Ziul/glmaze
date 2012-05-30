#include "player.h"

Player Player::PlayerControl;

//Chame init() para inicializar e colocá-lo na lista
Player::Player()
{
    Entidade();



    setTamanho(2.5f);
    posicao.x = ((TAMANHO_BLOCO*1) + TAMANHO_BLOCO/2) - (tamanho.x/2);
    posicao.y = tamanho.y/2;
    posicao.z = ((TAMANHO_BLOCO*1) + TAMANHO_BLOCO/2) - (tamanho.z/2);
    showWired = true;
}
void Player::ajustaCamera()
{
    float deltaMove = Camera::CameraControl.deltaMove;
    //Se estiver movendo (frente ou traz)
    if (deltaMove)
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
}
