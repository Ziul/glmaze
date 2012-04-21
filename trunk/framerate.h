#ifndef __FRAMERATE_H_
#define __FRAMERATE_H_

#include "defines.h"
#include "text.h"

class FrameRate
{
    private:
        unsigned int ticks;
        unsigned int frames;
        float fps;
    public:
        void execute()
        {
            unsigned int decorrido = glutGet(GLUT_ELAPSED_TIME) - ticks;
            frames++;
            if (decorrido >= 1000)
            {
                fps = ((float)frames*1000.0f/(float)decorrido);

                frames = 0;
                ticks = glutGet(GLUT_ELAPSED_TIME);
            }

        }

        float getFPS()
        {
            return fps;
        }
        FrameRate()
        {
            ticks = glutGet(GLUT_ELAPSED_TIME);
            frames = 0;
            fps = 0;
        }
};


#endif
