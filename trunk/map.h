#ifndef MAPS_H_
#define MAPS_H_

#include "includes.h"
#include "tile.h"
#include <vector>

class Map
{
    private:
        std::vector<Tile> listaTiles;

    public:
        Tile* getTile(int x, int y);
        int MAPA_ALTURA;
        int MAPA_LARGURA;

        Mapp();

        void render();
        bool load(char* filename);

        //Usado pra outras classes obterem info sobre o mapa.
        static Map MapControl;

};




#endif
