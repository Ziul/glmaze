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
inline int Map::getX(int i)
{
    return i % MAP_WIDTH;
}
inline int Map::getY(int i)
{
    return (int) i/MAP_WIDTH;
}

Map::Map()
{
    origemX = -TAMANHO_BLOCO;
    origemZ = -TAMANHO_BLOCO;
    mostraWired = false;
}

void Map::render()
{
    glPushMatrix();
    float offset = (float)TAMANHO_BLOCO/2.0f;
    glTranslated(offset, offset, offset); //Pois o glut imprime a partir do centro
    glColor3f(COR_PAREDE);

    for(unsigned int i = 0; i < listaTiles.size(); i++)
    {
        renderTile(i);
    }
    glPopMatrix();
}
inline void Map::renderTile(unsigned int i)
{
    //Move ponto de referencia
    if (i != 0) //No primeiro não há deslocamento
    {
            if (getY(i) > getY(i-1) ) //Se o Y do Tile atual foi maior que o antigo
                glTranslated(
                             -(TAMANHO_BLOCO*(MAP_WIDTH-1)  ),     0,TAMANHO_BLOCO);
            else   //Moveu em X
                glTranslated(TAMANHO_BLOCO,0,0);
    }
    if(listaTiles[i].typeId == TILE_TIPO_PAREDE )
    {
        if(mostraWired)
            glutWireCube(listaTiles[i].tamanho);
        else
            glutSolidCube(listaTiles[i].tamanho);
    }
    else
    if(listaTiles[i].typeId == TILE_TIPO_CHAO )
    {
        float offset = (float)TAMANHO_BLOCO/2.0f;
        glColor3f(COR_CHAO);
        glTranslated(-offset,-offset,-offset); //Volta ao ponto 0,0 do quadrado, estava no centro por causa do glut
        glBegin(GL_QUADS);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, TAMANHO_BLOCO);
            glVertex3f(TAMANHO_BLOCO, 0.0f, TAMANHO_BLOCO);
            glVertex3f(TAMANHO_BLOCO, 0.0f, 0.0f);
        glEnd();
        glTranslated(offset,offset,offset);
        glColor3f(COR_PAREDE);

    }

}

bool Map::load(char* filename)
{
    listaTiles.clear();

    FILE* file = fopen(filename, "r");

    if(file == NULL)
        return false;

    MAP_HEIGHT = MAP_WIDTH = 0;

    //Pega o tamanho do mapa, quanto por quantos blocos
    int error = fscanf(file, "%d-%d\n", &MAP_WIDTH, &MAP_HEIGHT);

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            Tile tempTile;
            error = fscanf(file, "[%d] ",&tempTile.typeId);

            listaTiles.push_back(tempTile);
        }
        error = fscanf(file, "\n");
    }
    fclose(file);
    return true;
}




