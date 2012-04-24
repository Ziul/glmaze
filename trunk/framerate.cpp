#include "framerate.h"


FrameRate FrameRate::FPSControl;



float FrameRate::getFPS()
{
    return fps;
}
void FrameRate::setFPSCap(bool cap)
{
    fpsCap = cap;
}
bool FrameRate::isFPSCap()
{
    return fpsCap;
}
FrameRate::FrameRate()
{
    ticks = glutGet(GLUT_ELAPSED_TIME);
    ticksControl = glutGet(GLUT_ELAPSED_TIME);
    frames = 0;
    fps = 0;
    fpsCap = false;
}

void FrameRate::regulaFPS()
{
    unsigned int step = 1000.0f/FRAMES_PER_SECOND;
    unsigned int decorrido = glutGet(GLUT_ELAPSED_TIME) - ticksControl;
    if(decorrido < step )
        Sleep( step - decorrido);

    ticksControl = glutGet(GLUT_ELAPSED_TIME);
}

void FrameRate::loop()
{
    unsigned int decorrido = glutGet(GLUT_ELAPSED_TIME) - ticks;
    frames++;
    if (decorrido > 1000)
    {
        fps = ((float)frames*1000.0f/(float)decorrido);

        frames = 0;
        ticks = glutGet(GLUT_ELAPSED_TIME);
    }

    if (fpsCap)
        regulaFPS();

}
