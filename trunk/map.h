#ifndef MAPS_H_
#define MAPS_H_

#include "defines.h"
#include "tile.h"
#include <vector>
#include <stdio.h>

class Map
{
    private:
        std::vector<Tile> listaTiles;

        inline void renderTile(unsigned int i);

    public:
        Tile* getTile(int x, int y);
        inline int getX(int i);
        inline int getY(int i);
        int MAP_HEIGHT;
        int MAP_WIDTH;

        float origemX; //Posição aonde o mapa começa a renderizar,
        float origemZ; //Tile 0,0, aumenta pra direita-baixo

        bool mostraWired;

        Map();

        void render();
        int load(char* filename);

        void iniciaDisplayList();
        GLuint dlMap;

        //Usado pra outras classes obterem info sobre o mapa.
        static Map MapControl;



        //Operator overload
        inline Tile* operator ()  (const int x, const int y)
        {
            return this->getTile(x,y);
        }



};




#endif
