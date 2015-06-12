#include "sound.h"

int audio_rate = 44100;
Uint16 audio_format = AUDIO_S16SYS;
int audio_channels = 2;
int audio_buffers = 4096;

static const char *walkSoundFile = "./sounds/walk.ogg";
Mix_Chunk *walkSound;

int walkEffectChannelBlocked = 99; // 99 = not blocked, 0-16 blocked

void unblockChannel(int chan)
{
    if (chan == walkEffectChannelBlocked)
        walkEffectChannelBlocked = 99;
}



int init_Audio()
{
    int result = 0;
    int flags = MIX_INIT_OGG;
    if( SDL_Init(SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return 1;
    }
    else
    {
        Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);
        if (flags != (result = Mix_Init(flags)))
        {
            printf("Could not initialize mixer (result: %d).\n", result);
            printf("Mix_Init: %s\n", Mix_GetError());
            return 1;
        }
        else
        {
            walkSound = Mix_LoadWAV(walkSoundFile);
            void (*pUnblockChannel)(int);
            pUnblockChannel = (void *)unblockChannel;
            Mix_ChannelFinished(pUnblockChannel);
            return 0;
        }
    }
}

void close_Audio()
{
    Mix_FreeChunk(walkSound);
    SDL_Quit();
}

int playSound(Mix_Chunk *effect)
{
    Mix_PlayChannel(-1, effect, 0);
}

int playWalkSound()
{
    if(walkEffectChannelBlocked == 99)
    {
        walkEffectChannelBlocked = Mix_PlayChannel(0, walkSound, 0);
    }
}


