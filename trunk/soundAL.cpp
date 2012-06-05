#include "soundAL.h"

SoundAL::buf SoundAL::buffer[BUFFER_SIZE_AL];
SoundAL::src SoundAL::source[SOURCE_SIZE_AL];

SoundAL::SoundAL()
{
}
SoundAL::~SoundAL()
{
}

void SoundAL::init()
{
    alutInit(NULL, 0);

    for(int i = 0; i < BUFFER_SIZE_AL;i++)
        buffer[i].active=0;

        for(int i = 0; i < SOURCE_SIZE_AL;i++)
        source[i].active=0;
    //limpa erros
    alGetError();
    alutGetError();
}

int SoundAL::loadSound(const char filename[256], int loop)
{
    int buf_value = alutCreateBufferFromFile(filename);

    if (alutGetError() != ALUT_ERROR_NO_ERROR)
    {
        printf("Erro ao carregar arquivo de som: %s", alutGetErrorString(alutGetError()));
        return -1;
    }

    int buf_index = getUBuffer();

    if (buf_index == -1)
        return -1;

    buffer[buf_index].buffer = buf_value;
    buffer[buf_index].loop = loop;
    buffer[buf_index].active = 1;

    int src_index = createSource(buf_index);

    //Erro ao carregar source, printf na funcão createSource
    if (src_index == -1)
        return -1;



    return src_index;
}

int SoundAL::createSource(int buf_index)
{
    int src_index = getUSource();

    alGenSources(1,&source[src_index].source);

    if(alGetError() != AL_NO_ERROR)
    {
        alDeleteBuffers(1,&buffer[buf_index].buffer);
        alDeleteSources(1,& source[src_index].source);
        printf("Erro ao carregar arquivo de som: %d", alGetError());
        return -1;
    }
    //Liga a source ao buffer
    alSourcei(source[src_index].source, AL_BUFFER, buffer[buf_index].buffer);
    alSourcei (source[src_index].source, AL_LOOPING,  buffer[buf_index].loop);

    source[src_index].active = 1;

    return src_index;

}

void SoundAL::exit()
{
    for(int i = 0; i < BUFFER_SIZE_AL; i++)
        if(buffer[i].active)
            alDeleteBuffers(1,&buffer[i].buffer);

    for(int i = 0; i < SOURCE_SIZE_AL; i++)
        if(source[i].active)
            alDeleteBuffers(1,&source[i].source);

    alutExit();
}

void SoundAL::play(int src_i)
{
    alSourcePlay(source[src_i].source);
}

void SoundAL::pause(int src_i)
{
    alSourcePause(source[src_i].source);
}
void SoundAL::stop(int src_i)
{
    alSourceStop(source[src_i].source);
}

int SoundAL::getUBuffer()
{
    for(int i = 0; i < BUFFER_SIZE_AL; i++)
        if(!buffer[i].active)
            return i;

    return -1;
}

int SoundAL::getUSource()
{
    for(int i = 0; i < SOURCE_SIZE_AL; i++)
        if(!source[i].active)
            return i;

    return -1;
}
