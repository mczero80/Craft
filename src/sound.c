#include "sound.h"

//gcc -I /usr/include/SDL -o test test.cpp -lSDL

Mix_Chunk *step;

int init_Audio()
{
    if( SDL_Init(SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return 0;
    }
    else
    {
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            return 0;
        }
        else
        {
            step = Mix_LoadWAV("sounds/walking-bare-feet.wav");
            return 1;
        }
    }
}

void close_Audio()
{
    //Free the sound effects
    Mix_FreeChunk( step );
    step = NULL;

    //Free the music
    //Mix_FreeMusic( gMusic );
    //gMusic = NULL;

    //Quit SDL subsystems
    Mix_Quit();
    SDL_Quit();
}

int play_step()
{
    //int Mix_SetPosition(int channel, Sint16 angle, Uint8 distance);

    int SChannel = 0;

    if (step == NULL)
    {
        Mix_FreeChunk(step);
        return 1;
    }
    else
    {
        SChannel = Mix_PlayChannel(-1, step, 0);

        while(Mix_Playing(SChannel) != 0);
        {
            Mix_FreeChunk(step);
        }

        return 0;
    }
}
