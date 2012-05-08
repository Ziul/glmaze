#include "tile.h"

Tile::Tile()
{
    tamanho = TAMANHO_BLOCO;
    posY = 0;

    left = right = front = back = top = bottom = false;
}
