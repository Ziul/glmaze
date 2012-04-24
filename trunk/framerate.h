#ifndef __FRAMERATE_H_
#define __FRAMERATE_H_

#include "defines.h"


class FrameRate
{
    private:
        unsigned int ticks;
        unsigned int ticksControl;
        unsigned int frames;
        float fps;
    public:
        void loop();

        bool fpsCap;

        void setFPSCap(bool cap);
        bool isFPSCap();
        float getFPS();
        FrameRate();

        void regulaFPS();

        static FrameRate FPSControl;
};


#endif
