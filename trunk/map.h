#ifndef _MAPS_H_
#define _MAPS_H_

#include "defines.h"
#include "tile.h"
#include <vector>
#include <stdio.h>

class Map
{
    private:
        std::vector<Tile> listaTiles;
        std::vector<Tile> listaRetangulos;
        void geraQuadradosOptimizados();

        int RENDER_MODE;


        void renderTile(unsigned int i);
        void renderTileOptimizado(unsigned int i);
        void renderBloco(float width, float height, float flatness, bool left, 
        				bool right, bool front, bool back, bool top, int TYPE);
        bool mostraWired;
    public:

        void reset();
        Tile* getTile(int x, int y);
        inline int getX(int i);
        inline int getY(int i);
        int MAP_HEIGHT;
        int MAP_WIDTH;

        float origemX; //Posicao aonde o mapa comeca a renderizar,
        float origemZ; //Tile 0,0, aumenta pra direita-baixo

        void setWired(int wired);
        bool isWire();

        Map();

        void render();
        void render(float cameraX, float cameraY, float cameraZ);
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
