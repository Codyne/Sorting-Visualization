#ifndef GENERATE_TONE_H
#define GENERATE_TONE_H

#include <alsa/asoundlib.h>
#include <stdio.h>

void init_pcm(int rate, int channels, int ms);
void play_tone(int tone);
void stop_tone();
void cleanup_pcm();

#endif
