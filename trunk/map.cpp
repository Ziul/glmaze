#include "map.h"

//Usado pra outras classes obterem info sobre o mapa.
Map Map::MapControl;


//Pega o Tile na posição x,y do mapa.
//Ex: Map 1 2 3   vector será 1 2 3 4 5 6
//        4 5 6
Tile* Map::getTile(int x, int y)
{
    unsigned int ID = 0;

    ID = (y * MAP_WIDTH) + x;

    return &listaTiles[ID];
}

Map::Map(){}

void Map::render(){}
bool Map::load(char* filename)
{
    listaTiles.clear();

    FILE* file = fopen(filename, "r");

    if(file == NULL)
        return false;

    MAP_HEIGHT = MAP_WIDTH = 0;

    //Pega o tamanho do mapa, quanto por quantos blocos
    fscanf(file, "%d-%d\n", &MAP_WIDTH, &MAP_HEIGHT);

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            Tile tempTile;
            fscanf(file, "[%d] ",&tempTile.typeId);

            listaTiles.push_back(tempTile);
        }
        fscanf(file, "\n");
    }
    fclose(file);
    return true;
}




