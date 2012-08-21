
/************************************************************************

    Versao inicial simplificada. Do post de
    http://www.gamedev.net/topic/373295-nice-way-to-add-sound-to-my-glut-project-also-icons/
    Simplesmente carregue o som e toque, não precisa mexer no listener
    nem velocidy, position e orientação

    NOTA: Não esquecer de chamar init e exit ou havera vazamento de memoria.

************************************************************************/
#ifndef _SOUND_AL_
#define _SOUND_AL_

#include "defines.h"

#define BUFFER_SIZE_AL 256
#define SOURCE_SIZE_AL 256

class SoundAL
{
    private:
    typedef struct
    {
        ALuint buffer;
        ALboolean loop;
        int active;
    } buf;

    typedef struct
    {
        ALuint source;
        int active;
    } src;

        //Pega primeiro buffer/source não utilizado
        int getUBuffer(void);
        int getUSource(void);
        int createSource(int buf_index);
    public:
        SoundAL();
        ~SoundAL();

        static buf buffer[BUFFER_SIZE_AL];
        static src source[SOURCE_SIZE_AL];

        void init(void);
        void exit(void);

        int loadSound(const char filename[256], int loop);

        void play(int src_i);
        void pause(int src_i);
        void stop(int src_i);
        void stopAll();

        bool isPlaying(int src_i);
/*
        void deleteBuffer(unsigned int b);

        void setListener(float position[3], float vel[3], float orientation[6]);
        void setSoundPos(unsigned int s, float x, float y, float z, float vx, float vy, float vz);
*/
};

#endif
