#include "entidade.h"


static std::vector<Entidade*> Entidade::EntidadeList;

Entidade::Entidade();
Entidade::~Entidade();
void Entidade::calculaColisao(Entidade* objeto);
void Entidade::calculaColisaoMapa();

void Entidade::removeFromEntidadeList();

bool Entidade::carregaModelo(char* file);
void Entidade::loop();
void Entidade::render();
void Entidade::cleanup();
void Entidade::executaColisao();
void Entidade::testaColisao();
