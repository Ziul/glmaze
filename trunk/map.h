#ifndef _MAPS_H_
#define _MAPS_H_

#include "defines.h"
#include "tile.h"
#include "camera.h"
#include "text.h"
#include <vector>
#include <stdio.h>
#include <math.h>
#include "model_obj.h"


class Map
{
    private:
        std::vector<Tile> listaTiles;
        std::vector<Tile> listaTilesOptimizados;
        void geraQuadradosOptimizados();

        int RENDER_MODE;


        //void renderTile(unsigned int i);
        void renderTileOptimizado(unsigned int i);
        void renderBloco(float width, float height, float flatness, bool left,
        				bool right, bool front, bool back, bool top, int TYPE);


        bool mostraWired;
    public:
        Tile* getTile(int x, int y);
        inline int getX(int i);
        inline int getY(int i);

        void setWired(int wired);
        bool isWire();

        Map();

        //void render();
        void render();
        int load(char* filename);

        //Used to others classes to get info about the map
        static Map MapControl;
        //Operator overload
        inline Tile* operator ()  (const int x, const int y)
        {
            return this->getTile(x,y);
        }
        //Propriedades publicas
    public:
        int MAP_HEIGHT;
        int MAP_WIDTH;

        float origemX; // Where the map start to render
        float origemZ; //Tile 0,0, growls on right-down

        GLuint dlMap;

        Model_OBJ coin;
        Model_OBJ bigCoin;

        float coinRotate;
        float coinVelocidade;
        //Usa pra calcular rotate
        unsigned int deltaTicks;


};


#endif
