#ifndef GENERATE_TONE_H
#define GENERATE_TONE_H

#include <alsa/asoundlib.h>
#include <stdio.h>

void generate_tone(int tone, int rate, int channels, int fps);

#endif
