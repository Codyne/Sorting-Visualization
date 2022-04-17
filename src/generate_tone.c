#include "generate_tone.h"

#define PCM_DEVICE "default"

#define PCM_ERR(err)												\
	if (err < 0)													\
		fprintf(stderr, "PCM Error [%d]: %s\n", snd_strerror(err));	\

void generate_tone(int tone, int rate, int channels, int ms) {
	unsigned int err, pcmTmp, dir;
	char *buff;
	int buffSize;

	snd_pcm_t *pcm;
	snd_pcm_hw_params_t *params;
	snd_pcm_uframes_t frames;

	err = snd_pcm_open(&pcm, PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0);
	PCM_ERR(err);

	snd_pcm_hw_params_alloca(&params);
	snd_pcm_hw_params_any(pcm, params);

	err = snd_pcm_hw_params_set_access(pcm, params,
									   SND_PCM_ACCESS_RW_INTERLEAVED);
	PCM_ERR(err);

	err = snd_pcm_hw_params_set_format(pcm, params,
									   SND_PCM_FORMAT_S16_LE);
	PCM_ERR(err);

	err = snd_pcm_hw_params_set_channels(pcm, params, channels);
	PCM_ERR(err);

	err = snd_pcm_hw_params_set_rate_near(pcm, params, &rate, 0);
	PCM_ERR(err);

	err = snd_pcm_hw_params(pcm, params);
	PCM_ERR(err);

	snd_pcm_hw_params_get_channels(params, &pcmTmp);
	snd_pcm_hw_params_get_rate(params, &pcmTmp, 0);

	snd_pcm_hw_params_get_period_size(params, &frames, 0);

	buffSize = frames * channels * 2;
	buff = (char *) malloc(buffSize);
	for (int i = 0; i < buffSize; i++) buff[i] = i * tone;

	snd_pcm_hw_params_get_period_time(params, &pcmTmp, NULL);

	for (int i = (ms * 1000) / pcmTmp; i > 0; i--) {
		if (err = snd_pcm_writei(pcm, buff, frames) == -EPIPE) {
			snd_pcm_prepare(pcm);
		}
		PCM_ERR(err);
	}

	snd_pcm_drain(pcm);
	snd_pcm_close(pcm);
	free(buff);
}
