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

void Map::renderBloco(float width, float height, float flatness, int TYPE = GL_QUADS)
{
    float w = width/2;
    float h = height/2;
    float f = flatness/2;

	glBegin(TYPE);
    //Front
	glNormal3f(0.0f, 0.0f, 1.0f);
        //glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-w, -h, f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(w, -h, f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(w, h, f);
        //glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-w, h, f);

	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
        //glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(w, -h, -f);
        //glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(w, h, -f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(w, h, f);
        //glNormal3f(1.0f, 0.0f, 1.0f);
	glVertex3f(w, -h, f);

	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
        //glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-w, -h, -f);
        //glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-w, h, -f);
        //glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(w, h, -f);
        //glNormal3f(1.0f, 0.0f, -1.0f);
	glVertex3f(w, -h, -f);

	//Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
        //glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-w, -h, -f);
        //glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-w, -h, f);
        //glNormal3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-w, h, f);
        //glNormal3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-w, h, -f);

	//Top
	glNormal3f(0.0f, 1.0f, 0.0f);
        //glNormal3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-w, h, -f);
        //glNormal3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-w, h, f);
        //glNormal3f(1.0f, 1.0f, 1.0f);
	glVertex3f(w, h, f);
        //glNormal3f(1.0f, 1.0f, -1.0f);
	glVertex3f(w, h, -f);

    ///Não precisa imprimir fundo
    /*
	//Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
        //glNormal3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-w, -h, -f);
        //glNormal3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-w, -h, f);
        //glNormal3f(1.0f, -1.0f, 1.0f);
	glVertex3f(w, -h, f);
        //glNormal3f(1.0f, -1.0f, -1.0f);
	glVertex3f(w, -h, -f);
	*/
	glEnd();
}


void Map::render()
{
    glPushMatrix();
    //float offset = (float)TAMANHO_BLOCO/2.0f;
    //glTranslated(0.0f, offset, offset); //Pois o glut imprime a partir do centro

    /*
    for(unsigned int i = 0; i < listaTiles.size(); i++)
    {
        renderTile(i);
    }
    */
    //Desenha chão


    glColor3f(COR_PAREDE); //Desenha paredes
    for(unsigned int i = 0; i < listaRetangulos.size();i++)
    {
        glPushMatrix();

        if (listaRetangulos[i].typeId == TILE_TIPO_PAREDE )
        {
            //float px = listaRetangulos[i].posX * listaRetangulos[i].tamanho;
            glTranslatef(listaRetangulos[i].posX * listaRetangulos[i].tamanho,
                         listaRetangulos[i].posY * listaRetangulos[i].tamanho,
                         listaRetangulos[i].posZ * listaRetangulos[i].tamanho
                         );
            //Desenha a partir do centro
            float tamanhoOffsetX = (listaRetangulos[i].x * listaRetangulos[i].tamanho)/2;
            float tamanhoOffsetY = (listaRetangulos[i].y * listaRetangulos[i].tamanho)/2;
            float tamanhoOffsetZ = (listaRetangulos[i].z * listaRetangulos[i].tamanho)/2;
            glTranslatef(tamanhoOffsetX,tamanhoOffsetY,tamanhoOffsetZ);

            renderBloco(listaRetangulos[i].x * listaRetangulos[i].tamanho,
                        listaRetangulos[i].y * listaRetangulos[i].tamanho,
                        listaRetangulos[i].z * listaRetangulos[i].tamanho);
        }
        else
        if (listaRetangulos[i].typeId == TILE_TIPO_CHAO )
        {
            glColor3f(COR_CHAO);
            //float px = listaRetangulos[i].posX * listaRetangulos[i].tamanho;
            glTranslatef(listaRetangulos[i].posX * listaRetangulos[i].tamanho,
                         (listaRetangulos[i].posY * listaRetangulos[i].tamanho) - 1 -listaRetangulos[i].tamanho/2,
                         listaRetangulos[i].posZ * listaRetangulos[i].tamanho
                         );
            float tamanhoOffsetY = ((listaRetangulos[i].y * listaRetangulos[i].tamanho)/2) + 1;
            glBegin(GL_QUADS);
                glNormal3f(0.0f, 1.0f, 0.0f);
                glVertex3f(0.0f,                                                tamanhoOffsetY,     0.0f);
                glVertex3f(0.0f,                                                tamanhoOffsetY,     listaRetangulos[i].z * listaRetangulos[i].tamanho);
                glVertex3f(listaRetangulos[i].x * listaRetangulos[i].tamanho,   tamanhoOffsetY,     listaRetangulos[i].z * listaRetangulos[i].tamanho);
                glVertex3f(listaRetangulos[i].x * listaRetangulos[i].tamanho,   tamanhoOffsetY,     0.0f);
            glEnd();
            glColor3f(COR_PAREDE);

        }
        glPopMatrix();

    }
    glPopMatrix();
}

void Map::renderTile(unsigned int i)
{
    //Move ponto de referencia
    if (i != 0) //No primeiro não há deslocamento
    {
            if (getY(i) > getY(i-1) ) //Se tiver pulado de linha, volta em X e avança em Z
                glTranslated(
                             -(TAMANHO_BLOCO*(MAP_WIDTH-1)  ),     0, TAMANHO_BLOCO);
            else   //Moveu em X
                glTranslated(TAMANHO_BLOCO,0,0);
    }
    if(listaTiles[i].typeId == TILE_TIPO_PAREDE )
    {
        if(mostraWired)
            renderBloco(listaTiles[i].tamanho, listaTiles[i].tamanho, listaTiles[i].tamanho, GL_LINE);
        else
            renderBloco(listaTiles[i].tamanho, listaTiles[i].tamanho, listaTiles[i].tamanho, GL_QUADS);
    }
    else
    if(listaTiles[i].typeId == TILE_TIPO_CHAO )
    {
        float offset = (float)TAMANHO_BLOCO/2.0f;
        glColor3f(COR_CHAO);
        glBegin(GL_QUADS);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-offset, -offset, -offset);
            glVertex3f(-offset, -offset, offset);
            glVertex3f(offset, -offset, offset);
            glVertex3f(offset, -offset, -offset);
        glEnd();
        glColor3f(COR_PAREDE);

    }

}

void Map::iniciaDisplayList()
{

}

int Map::load(char* filename)
{
    listaTiles.clear();

    FILE* file = fopen(filename, "r");

    if(file == NULL)
        return -1;

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
    ///TESTE
    geraListaRetangulos();
    return error;
}

void Map::geraListaRetangulos()
{
    static int type = listaTiles[0].typeId;

    int xDesloc = 0;
    int xSize = 1;

    type = listaTiles[xDesloc].typeId; //Pega o tipo do bloco

    for(int iY = 0; iY < MAP_HEIGHT; iY++)
    {

        xDesloc = 0;
        while(true)
        {
           if (xDesloc+1 > MAP_WIDTH)
               break;
           int index = xDesloc + MAP_WIDTH*iY;
           type = listaTiles[index].typeId;
           for(int iX = xDesloc+1; iX <= MAP_WIDTH; iX++) //Testa todos os blocos a depois do atual em X
           {
               if (iX == 80)
               {
                   index = iX + MAP_WIDTH*iY;
                   int type1 = listaTiles[index].typeId;
                   type1 = listaTiles[index+1].typeId;
                   type1 = listaTiles[index+2].typeId;
                   type1 = listaTiles[index+3].typeId;
                   type1 = listaTiles[index+4].typeId;

               }

               index = iX + MAP_WIDTH*iY;
               if(iX != (MAP_WIDTH) && listaTiles[index].typeId == type) //Se for o mesmo tipo, aumenta o tamanho
                   xSize++;
               else
               {
                   if(listaTiles[index].typeId == type && iX == (MAP_WIDTH-1))
                        xSize++;
                   Tile retangulo;
                   retangulo.tamanho = TAMANHO_BLOCO;
                   retangulo.y = 1;
                   retangulo.z = 1;
                   retangulo.x = xSize;
                   retangulo.typeId = type;
                   retangulo.posX = xDesloc;
                   retangulo.posZ = iY;
                   retangulo.posY = 0;
                    listaRetangulos.push_back(retangulo);
                   xDesloc = iX;
                   xSize = 1;
                   break;
                }
            }
        }// FIM WHILE
    }
}

void Map::reset()
{
    Map();
}



