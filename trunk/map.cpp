#include "map.h"

//Usado pra outras classes obterem info sobre o mapa.
Map Map::MapControl;


//Pega o Tile na posicao x,y do mapa.
//Ex: Map 1 2 3   vector sera 1 2 3 4 5 6
//        4 5 6
Tile* Map::getTile(int x, int y)
{
    unsigned int ID = 0;

    ID = (y * MAP_WIDTH) + x;

    return &listaTilesOptimizados[ID];
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
    RENDER_MODE = 0x0007; //GL_QUADS
}

void Map::renderBloco(float width, float height, float flatness, bool left,
		bool right, bool front, bool back, bool top, int TYPE = GL_QUADS)
{
    float w = width/2;
    float h = height/2;
    float f = flatness/2;

    float xTexNumber = width/TAMANHO_BLOCO;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glBegin(TYPE);
    //Front
    if(front)
    {
         glNormal3f(0.0f, 0.0f, 1.0f);
            //glNormal3f(-1.0f, 0.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-w, -h, f);
            //glNormal3f(1.0f, 0.0f, 1.0f);
            glTexCoord2f(xTexNumber, 0.0f);
        glVertex3f(w, -h, f);
            //glNormal3f(1.0f, 0.0f, 1.0f);
            glTexCoord2f(xTexNumber, 1.0f);
        glVertex3f(w, h, f);
            //glNormal3f(-1.0f, 0.0f, 1.0f);
            glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-w, h, f);
    }

	//Right
	if(right)
	{
         glNormal3f(1.0f, 0.0f, 0.0f);
            //glNormal3f(1.0f, 0.0f, -1.0f);
            glTexCoord2f(0.0f, 0.0f);
        glVertex3f(w, -h, -f);
            //glNormal3f(1.0f, 0.0f, -1.0f);
            glTexCoord2f(0.0f, 1.0f);
        glVertex3f(w, h, -f);
            glTexCoord2f(1.0f, 1.0f);
            //glNormal3f(1.0f, 0.0f, 1.0f);
        glVertex3f(w, h, f);
            glTexCoord2f(1.f, 0.0f);
            //glNormal3f(1.0f, 0.0f, 1.0f);
        glVertex3f(w, -h, f);
	}

	//Back
	if(back)
    {
            glNormal3f(0.0f, 0.0f, -1.0f);
            //glNormal3f(-1.0f, 0.0f, -1.0f);
            glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-w, -h, -f);
            //glNormal3f(-1.0f, 0.0f, -1.0f);
            glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-w, h, -f);
            //glNormal3f(1.0f, 0.0f, -1.0f);
            glTexCoord2f(xTexNumber, 1.0f);
        glVertex3f(w, h, -f);
            //glNormal3f(1.0f, 0.0f, -1.0f);
            glTexCoord2f(xTexNumber, 0.0f);
        glVertex3f(w, -h, -f);
	}


	//Left
	if(left)
    {
        glNormal3f(-1.0f, 0.0f, 0.0f);
            //glNormal3f(-1.0f, 0.0f, -1.0f);
            glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-w, -h, -f);
            //glNormal3f(-1.0f, 0.0f, 1.0f);
            glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-w, -h, f);
            //glNormal3f(-1.0f, 0.0f, 1.0f);
            glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-w, h, f);
            //glNormal3f(-1.0f, 0.0f, -1.0f);
            glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-w, h, -f);
    }
    glEnd();
glDisable(GL_TEXTURE_2D);
	glBegin(TYPE);
	//Top
	if(top)
	{
        glNormal3f(0.0f, 1.0f, 0.0f);
        //glNormal3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-w, h, -f);
            //glNormal3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-w, h, f);
            //glNormal3f(1.0f, 1.0f, 1.0f);
        glVertex3f(w, h, f);
            //glNormal3f(1.0f, 1.0f, -1.0f);
        glVertex3f(w, h, -f);
	}

    ///Nao precisa imprimir fundo
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
    float offset = (float)TAMANHO_BLOCO/2.0f;
    glTranslated(offset, offset, offset); //Pois o glut imprime a partir do centro
    glColor3f(COR_PAREDE);

    int indexX = (Camera::CameraControl.cameraX / TAMANHO_BLOCO);
    int indexY = (Camera::CameraControl.cameraZ / TAMANHO_BLOCO);

    int beginX = indexX - GAME_FOV;
    int beginY = indexY - GAME_FOV;
    int endX = indexX + GAME_FOV;
    int endY = indexY + GAME_FOV;
    if(endX > MAP_WIDTH)
            endX = MAP_WIDTH;
    if(endY > MAP_HEIGHT)
        endY = MAP_HEIGHT;
    if(beginX < 0)
        beginX = 0;
    if(beginY < 0)
        beginY = 0;


    for(int i = beginY; i < endY; i++)
    {
        for(int j = beginX; j < endX; j++)
        {
            glPushMatrix();
                renderTileOptimizado(j+i*MAP_WIDTH);
            glPopMatrix();
        }
    }

    //Desenha chao
    glPopMatrix();

}
void Map::renderTileOptimizado(unsigned int i)
{
    //Camera no centro do quadrado 0,0,0
    glTranslated(listaTilesOptimizados[i].posX * TAMANHO_BLOCO,
                 listaTilesOptimizados[i].posY * TAMANHO_BLOCO,
                 listaTilesOptimizados[i].posZ * TAMANHO_BLOCO);


    if(listaTilesOptimizados[i].typeId == TILE_TIPO_PAREDE )
    {
        renderBloco(listaTilesOptimizados[i].tamanho, listaTilesOptimizados[i].tamanho, listaTilesOptimizados[i].tamanho,
                    listaTilesOptimizados[i].left,listaTilesOptimizados[i].right,listaTilesOptimizados[i].front,
                    listaTilesOptimizados[i].back,listaTilesOptimizados[i].top,
                    RENDER_MODE);

    }
    else //Imprime chao
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        float offset = (float)TAMANHO_BLOCO/2.0f;
        glColor3f(COR_CHAO);
        glBegin(RENDER_MODE);
            glNormal3f(0.0f, 1.0f, 0.0f);
                glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-offset, -offset, -offset);
                glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-offset, -offset, offset);
                glTexCoord2f(1.0f, 1.0f);
            glVertex3f(offset, -offset, offset);
                glTexCoord2f(1.0f, 0.0f);
            glVertex3f(offset, -offset, -offset);
        glEnd();
        glColor3f(COR_PAREDE);
        glDisable(GL_TEXTURE_2D);
        if (listaTilesOptimizados[i].typeId == TILE_TIPO_CHAO_COM_BOLA)
        {
            glTranslated(0,-2,0);
            glutSolidSphere(1,8,8);
        }
        else
        if (listaTilesOptimizados[i].typeId == TILE_TIPO_CHAO_COM_BOLA_ESPECIAL)
        {
            glTranslated(0,-2,0);
            glutSolidSphere(3,8,8);
        }

    }
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
    geraQuadradosOptimizados();
    return error;
}

void Map::geraQuadradosOptimizados()
{
    listaTilesOptimizados.clear();

    for(int iY = 0; iY < MAP_HEIGHT; iY++)
    {
       for(int iX = 0; iX < MAP_WIDTH; iX++) //Testa todos os blocos a depois do atual em X
       {
           Tile retangulo;
           int index = iX + MAP_WIDTH*iY;
           if (listaTiles[index].typeId != TILE_TIPO_PAREDE)
           {
               retangulo.typeId = listaTiles[index].typeId;
               retangulo.posX = iX;
               retangulo.posZ = iY;
               listaTilesOptimizados.push_back(retangulo);
               continue;
           }

            retangulo.top = true;
            //Se parede, verifica fora de bordas
            if (index-1 < 0)
                retangulo.left = true;
            else //Se for chao, entao tem parede naquela direcao
                if (listaTiles[index-1].typeId != TILE_TIPO_PAREDE)
                    retangulo.left = true;
            if (index - MAP_WIDTH < 0)
                retangulo.back = true;
            else //Se for chao, entao tem parede naquela direcao
                if (listaTiles[index - MAP_WIDTH].typeId != TILE_TIPO_PAREDE)
                    retangulo.back = true;
            if (index +1 >= (int)listaTiles.size())
                retangulo.right = true;
            else //Se for chao, entao tem parede naquela direcao
                if (listaTiles[index +1].typeId != TILE_TIPO_PAREDE)
                    retangulo.right = true;
            if (index + MAP_WIDTH >= (int)listaTiles.size())
                retangulo.front = true;
            else //Se for chao, entao tem parede naquela direcao
                if (listaTiles[index + MAP_WIDTH].typeId != TILE_TIPO_PAREDE)
                    retangulo.front = true;

            retangulo.posX = iX;
            retangulo.posZ = iY;
            retangulo.typeId = listaTiles[index].typeId;

            listaTilesOptimizados.push_back(retangulo);

        }
    }
}



void Map::setWired(int wired)
{
    if (wired)
    {
        mostraWired = true;
        RENDER_MODE = GL_LINES;
    }
    else
    {
        mostraWired = false;
        RENDER_MODE = GL_QUADS;
    }

}
bool Map::isWire()
{
    return mostraWired;
}


