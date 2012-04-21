//==============================================================================
/*
    Notas:
    TileID representa


*/
//==============================================================================
#ifndef __TILE_H_
#define __TILE_H_

#define TAMANHO_PADRAO 20;

enum
{
    TILE_TIPO_NENHUM = 0,
    TILE_TIPO_PAREDE = 1,
    TILE_TIPO_CHAO = 2,
    TILE_TIPO_PAREDE_FALSA = 3
};

class Tile
{
    public:
        int typeId;

        float tamanhoX;
        float tamanhoY;
        float tamanhoZ;

        Tile();

};

#endif
