#include "entidade.h"


std::vector<Entidade*> Entidade::EntidadeList;

Entidade::Entidade(){}
Entidade::~Entidade(){}
void Entidade::calculaColisao(Entidade* objeto){}
void Entidade::calculaColisaoMapa(){}

void Entidade::removeFromEntidadeList(){}

bool Entidade::carregaModelo(char* file){return true;}
void Entidade::loop(){}
void Entidade::render(){}
void Entidade::cleanup(){}
void Entidade::executaColisao(){}
void Entidade::testaColisao(){}
