#include "sound.h"

//gcc -I /usr/include/SDL -o test test.cpp -lSDL

int blocked = 0;

int audio_rate = 44100;
Uint16 audio_format = AUDIO_S16SYS;
int audio_channels = 2;
int audio_buffers = 4096;

int blockedChannel = 0;

void step(int chan)
{
    blocked = !blocked;
}

int init_Audio()
{
    int result = 0;
    int flags = MIX_INIT_OGG;
    if( SDL_Init(SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return 0;
    }
    else
    {
        Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);
        if (flags != (result = Mix_Init(flags)))
        {
            printf("Could not initialize mixer (result: %d).\n", result);
            printf("Mix_Init: %s\n", Mix_GetError());
            return 0;
        }
        else
        {
            walkSound = Mix_LoadWAV(walkSoundFile);
            void (*stepFunc)(chan);
            stepFunc = (void *)step;
            Mix_ChannelFinished(stepFunc);
            return 1;
        }
    }
}

void close_Audio()
{
    Mix_FreeChunk(walkSound);
    SDL_Quit();
}

int play_step()
{
    if(!blocked)
    {
        Mix_PlayChannel(0, walkSound, 0);
        blocked = 1;
    }
}


