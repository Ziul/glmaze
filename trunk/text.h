#ifndef __TEXTT__H_
#define __TEXTT__H_

#include "defines.h"
#include <stdio.h>

namespace txt
{
    extern void renderBitmapString(
            float x,
            float y,
            int spacing,
            void *font,
            char *string) ;



    ///ARRUMA PROJECOES
    extern void setProjecaoOrto();
    extern void restauraProjecaoPerspectiva();

    extern void renderText2dOrtho(float x, float y, int spacing, const char*pStr, ...);

}



#endif



