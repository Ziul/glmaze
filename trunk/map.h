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

    public:
        Tile* getTile(int x, int y);
        int MAP_HEIGHT;
        int MAP_WIDTH;

        Map();

        void render();
        bool load(char* filename);

        //Usado pra outras classes obterem info sobre o mapa.
        static Map MapControl;



        //Operator overload
        inline Tile* operator ()  (const int x, const int y)
        {
            return this->getTile(x,y);
        }



};




#endif
