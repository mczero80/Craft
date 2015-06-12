#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <stdio.h>

static const char *walkSoundFile = "./sounds/walk.ogg";
Mix_Chunk *walkSound;

int init_Audio();

void close_Audio();

int play_step();
