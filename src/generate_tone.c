#include "generate_tone.h"

#define PCM_DEVICE "default"

#define PCM_ERR(err)												\
	if (err < 0)													\
		fprintf(stderr, "[%s:%d] PCM Error [%u]: %s\n",				\
				__FILE__, __LINE__, err, snd_strerror(err));

char *TONE_BUFF;
int TONE_BUFF_SIZE, SECONDS;
unsigned int PERIOD;
snd_pcm_t *pcmHandle = NULL;
snd_pcm_hw_params_t *PARAMS;
snd_pcm_uframes_t FRAMES;

void init_pcm(int rate, int channels, int seconds) {
	unsigned int pcmTmp, dir;
	int err;

	err = snd_pcm_open(&pcmHandle, PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0);
	PCM_ERR(err);

	snd_pcm_hw_params_alloca(&PARAMS);
	snd_pcm_hw_params_any(pcmHandle, PARAMS);

	err = snd_pcm_hw_params_set_access(pcmHandle, PARAMS,
									   SND_PCM_ACCESS_RW_INTERLEAVED);
	PCM_ERR(err);

	err = snd_pcm_hw_params_set_format(pcmHandle, PARAMS,
									   SND_PCM_FORMAT_S16_LE);
	PCM_ERR(err);

	err = snd_pcm_hw_params_set_channels(pcmHandle, PARAMS, channels);
	PCM_ERR(err);

	err = snd_pcm_hw_params_set_rate_near(pcmHandle, PARAMS, &rate, 0);
	PCM_ERR(err);

	err = snd_pcm_hw_params(pcmHandle, PARAMS);
	PCM_ERR(err);

	snd_pcm_hw_params_get_channels(PARAMS, &pcmTmp);
	snd_pcm_hw_params_get_rate(PARAMS, &pcmTmp, 0);

	snd_pcm_hw_params_get_period_size(PARAMS, &FRAMES, 0);

	TONE_BUFF_SIZE = FRAMES * channels * 2;
	TONE_BUFF = (char *) malloc(TONE_BUFF_SIZE);

	snd_pcm_hw_params_get_period_time(PARAMS, &pcmTmp, NULL);
	PERIOD = pcmTmp;
	SECONDS = seconds;
}

void play_tone(int tone) {
	int err;

	for (int i = 0; i < TONE_BUFF_SIZE; i++) TONE_BUFF[i] = i * tone;

	snd_pcm_prepare(pcmHandle);
	for (int i = (SECONDS * 1000000) / PERIOD; i > 0; i--) {
		if (err = snd_pcm_writei(pcmHandle, TONE_BUFF, FRAMES) == -EPIPE) {
			snd_pcm_prepare(pcmHandle);
		}
		PCM_ERR(err);
	}
}

void stop_tone() {
	int err;
	if (pcmHandle) {
		err = snd_pcm_drop(pcmHandle);
		PCM_ERR(err);
	}
}

void cleanup_pcm() {
	snd_pcm_drop(pcmHandle);
	snd_pcm_close(pcmHandle);
	free(TONE_BUFF);
}
