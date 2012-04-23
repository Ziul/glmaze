//==============================================================================
/*
    A classe Vetor que Coordenada que armazena uma posição float x e y

    A classe define as operações comuns de vetores como produto escalar,
    vetorial, comprimento, etc.

*/
//==============================================================================
#ifndef _VETOR3D_H_
#define _VETOR3D_H_

#include <math.h>

//
// NOTA: perproduct = Normal do vetor
//
//           /  left hand perproduct,  x = -a.y, y = a.x;
//          /
//          ------>
//         /
//        /     left hand perproduct,  x = a.y, y = -a.x;

class Vetor3D
{
    public:

        float x;
        float y;
        float z;

        Vetor3D(float fX, float fY, float fZ) : x(fX), y(fY), z(fZ) {}
        Vetor3D() {x=0;y=0;z=0;}

        // Produtos
        // dot = escalar
        inline float dot(const Vetor3D b) const
        {
            return x*b.x + y*b.y + z*b.z;
        }

        // cross = vetorial
        inline float cross2D( const Vetor3D b) const
        {
            return x*b.y - y*b.x;
        }

        // Projeção desse vetor em B
        //Proj = (U.V) . vetor V
        //        |V|²
        Vetor3D project2D(const Vetor3D b)
        {
            Vetor3D proj;
            float dp = dot(b);
            proj.x = (dp/b.dot(b)) * b.x;
            proj.y = (dp/b.dot(b)) * b.y;

            return proj;
        }

        //Tamanho do Vetor
        inline float lenght(void) const
        {
            return (float) sqrt(x*x + y*y + z*z);
        }

        //Operadores

        inline Vetor3D operator + (const Vetor3D &V)   const
        { return Vetor3D(x+V.x, y+V.y, z+V.z); }

        inline Vetor3D operator - (const Vetor3D &V)   const
        { return Vetor3D(x-V.x, y-V.y, z-V.z); }

        inline Vetor3D operator * (float s)           const
        { return Vetor3D(x*s, y*s, z*s); }

        inline Vetor3D operator / (float s)           const
        { return Vetor3D(x/s, y/s, z/s); }


};

#endif



