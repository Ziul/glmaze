//==============================================================================
/*
    A classe Vetor que Coordenada que armazena uma posição float x e y

    A classe define as operações comuns de vetores como produto escalar,
    vetorial, comprimento, etc.

*/
//==============================================================================
#ifndef _VETOR_H_
#define _VETOR_H_

#include <math.h>

//
// NOTA: perproduct = Normal do vetor
//
//           /  left hand perproduct,  x = -a.y, y = a.x;
//          /
//          ------>
//         /
//        /     left hand perproduct,  x = a.y, y = -a.x;

class Vetor
{
    public:

        float x;
        float y;

        Vetor(float fX, float fY) : x(fX), y(fY) {}
        Vetor() {x=0;y=0;}

        // Produtos
        // dot = escalar
        inline float dot(const Vetor b) const
        {
            return x*b.x + y*b.y;
        }

        // cross = vetorial
        inline float cross( const Vetor b) const
        {
            return x*b.y - y*b.x;
        }

        // Projeção desse vetor em B
        //Proj = (U.V) . vetor V
        //        |V|²
        Vetor project(const Vetor b)
        {
            Vetor proj;
            float dp = dot(b);
            proj.x = (dp/b.dot(b)) * b.x;
            proj.y = (dp/b.dot(b)) * b.y;

            return proj;
        }

        //Tamanho do Vetor
        inline float lenght(void) const
        {
            return (float) sqrt(x*x + y*y);
        }

        //Operadores

        inline Vetor operator + (const Vetor &V)   const
        { return Vetor(x+V.x, y+V.y); }

        inline Vetor operator - (const Vetor &V)   const
        { return Vetor(x-V.x, y-V.y); }

        inline Vetor operator * (float s)           const
        { return Vetor(x*s, y*s); }

        inline Vetor operator / (float s)           const
        { return Vetor(x/s, y/s); }


};

#endif


