#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <stdio.h>

void unblockChannel(int chan);

int init_Audio();

void close_Audio();

int playSound(Mix_Chunk *effect);

int playWalkSound();


