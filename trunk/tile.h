//==============================================================================
/*
    Notas:
    TileID representa


*/
//==============================================================================
#ifndef __TILE_H_
#define __TILE_H_

enum
{
    TILE_ID_NENHUM = 0,
    TILE_ID_PAREDE = 1,
    TILE_ID_CHAO = 2,
    TILE_ID_PAREDE_FALSA = 3
};

class Tile
{
    public:
        int tileId;

        float tamanhoX;
        float tamanhoY;
        float tamanhoZ;

        Tile();

};

#endif
