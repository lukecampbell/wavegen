/*
 * waveforms.c
 *
 *  Created on: Jan 2, 2011
 *      Author: luke
 */
/**
 * @file waveforms.c
 * @brief Contains all the functions for maniupulating and creating the waveforms
 * @author Luke Campbell
 * @date 3/12/2011
 */
#include <riff2_pcm.h>
#include <riff2.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "waveGen.h"
#include "gtkradio.h"

#define VOLUME 0.15
/**
 * A 16 bit sinewave
 * @param wf the Waveform specs
 * @return a signed 16 bit value for the amplitude
 */
s_int16
sine16(Waveform *wf)
{
	signed short int amp = 0x7FFF;
	signed short int ret;
	double y = (double)amp * wf->volume * sin(2 * M_PI * (double)wf->freq * wf->t_offset);
	ret = (signed short int) y;
	if(wf->t_offset >= wf->time)
		return 0; /* no more time left on track */
	return ret;
}

/* this wave form is a stepped CW signal with tri-freq */
/**
 * This wave form is a stepped continuous wave signal with three frequencies
 * @param Waveform the waveform specs
 * @return a signed 16 bit value for the amplitude
 */
s_int16
stepLFM16(Waveform *wf)
{
	wf->freq = wf->lfm.freq1;
	if(wf->t_offset <= (0.33 * wf->time))
		return sine16(wf);
	wf->freq = wf->lfm.freq2;
	if(wf->t_offset <= (0.66 * wf->time))
		return sine16(wf);
	wf->freq = wf->lfm.freq3;
	if(wf->t_offset <= (1 * wf->time))
		return sine16(wf);
	else
		return 0;

}
/* linear frequency modulation */
/**
 * This function produces a linear frequency modulated signal
 * @param wf The waveform settings
 * @return a signed 16 bit value for the amplitude
 */
s_int16
lfmWave16(Waveform *wf)
{
	signed short int amp = 0x7FFF;
	signed short int ret;

	double freq = 0.5 * wf->freq * (wf->t_offset / wf->time) * (wf->t_offset / wf->time);
	double y = (double)amp * wf->volume * sin(2 * M_PI * (double)freq );
	ret = (signed short int) y;
	if(wf->t_offset >= wf->time)
		return 0; /* no more time left on track */
	return ret;
}
/**
 * solely for testing purposes has no real input
 */
/*
s_int16 lfmWave16(double freqBase, double freqEnd, double t_offset)
{
	signed short int amp = 0x7FFF;
	signed short int ret;
	double freq = (freqEnd - freqBase) * (freqEnd - freqBase) * (t_offset+1);
	double y = (double) amp * 0.15 * sin(2* M_PI * (double)freq );
	ret = (signed short int) y;
	return ret;
}
*/
/**
 * Solely for testing purposes has no real input
 */
s_int16
cancelWave16(Waveform *wf)
{
	signed short int amp = 0x7FFF;
	signed short int ret;
	wf->freq = -wf->freq * wf->t_offset;
	double y = (double)amp * wf->volume * sin(2 * M_PI * (double)wf->freq );
	ret = (signed short int) y;
	if(wf->t_offset >= wf->time)
		return 0; /* no more time left on track */
	return ret;
}
/**
 * Solely for testing purposes has no real input
 */
s_int16
testWaveB16(Waveform *wf)
{
	if(wf->t_offset >= wf->time)
		return 0; /* no more time left on track */
	return 0;
}
/**
 * Solely for testing purposes has no real input
 */
s_int16
nullwave(Waveform *wf)
{
	return 0;
}
/**
 * Fills a buffer with the waveform
 * @param buf The buffer
 * @len The lenght of the buffer
 * @w16 A function-pointer to a 16-bit wave-generating function
 * @wf The waveform to be passed into the wave-generating function
 * @t Time
 * @dt Delta Time
 */
void
fillChannel(char *buf, size_t len, waveForm16 w16, Waveform *wf, double *t, const double dt)
{
	char *p = buf;
	int j;
	for(j=0;j<(len/2);j++)
	  {
		endianValue16 y;
		wf->t_offset = *t;
		y.val = w16(wf);
		*(p++) = y.bytes[0];
		*(p++) = y.bytes[1];
		*t+=dt;
	  }
}
/**
 * Generates the waveform and writes the buffer(s) to the specified filename
 * @param filename Path to the file to be outputted
 * @param chan1 The waveform to be outputted on channel 1
 * @param chan2 The waveform to be outputted on channel 2
 * @param len Total length of the file
 */
void
generate(char *filename, Waveform *chan1, Waveform *chan2, double len)
{
	char channel1[1024]; /* channel 1 buffer */
	char channel2[1024]; /* channel 2 buffer */
	char buffer[2048]; /* total buffer */

	struct riff2_pcm_frame pcmHeader;
	struct riff2_format_chunk fmc;
	struct riff2_pcm_data dataFrame;
	struct riff2_pcm_settings set;

	double t1=0,t2=0; /* time offset */
	double dt1=0,dt2=0; /* delta time, time increments */

	int fd, s=0; /* s is the sample increment */
	int samples=0;



	set.bytesPerSample = 2;
	set.len = len;
	set.sampleRate = 44100;
	set.channels = 2;
	samples = (int) (set.sampleRate * set.len);

	dt1 = dt2 = 1.0 / set.sampleRate; /* dt is one second divided by samplerate */





	riff2_settings(&pcmHeader,&fmc,&dataFrame,&set);

	if(filename == NULL)
		filename = "./test.wav";
	fd = open(filename,O_WRONLY | O_CREAT, 0644);

	riff2_write_frame(fd,&pcmHeader);
	riff2_write_format(fd,&fmc);
	riff2_write_data(fd,&dataFrame);
	printf("Channel 1:\n");
	switch(chan1->form)
	  {
		case SINE16:
			printf("\t16bit Sine Wav\n\tFreq: %f\n",chan1->freq);
			break;
		case STEPLFM16:
			printf("\t16bit Step LFM\n\tFreq 1: %f\n\tFreq 2: %f\n\tFreq 3: %f\n",chan1->lfm.freq1,chan1->lfm.freq2,chan1->lfm.freq3);
			break;
		case LFMWAVE16:
			printf("16bit LFM slide\n\tFreq: %f\n",chan1->freq);
			break;
		default:
			printf("NA\n");
			break;
	  }
	printf("Channel 2:\n");
	switch(chan2->form)
	  {
		case SINE16:
			printf("\t16bit Sine Wav\n\tFreq: %f\n",chan2->freq);
			break;
		case STEPLFM16:
			printf("\t16bit Step LFM\n\tFreq 1: %f\n\tFreq 2: %f\n\tFreq 3: %f\n",chan2->lfm.freq1,chan2->lfm.freq2,chan2->lfm.freq3);
			break;
		case LFMWAVE16:
			printf("16bit LFM slide\n\tFreq: %f\n",chan2->freq);
			break;
		default:
			printf("NA\n");
			break;
	  }
	while(s<samples)
	  {
		switch(chan1->form)
		  {
			case SINE16:
				fillChannel(channel1,1024,sine16,chan1,&t1,dt1);
				break;
			case STEPLFM16:
				fillChannel(channel1,1024,stepLFM16,chan1,&t1,dt1);
				break;
			case LFMWAVE16:
				fillChannel(channel1,1024,lfmWave16,chan1,&t1,dt1);
				break;
			case CWAVE16:
				fillChannel(channel1,1024,cancelWave16,chan1,&t1,dt1);
				break;
			default:
				fillChannel(channel1,1024,nullwave,chan1,&t1,dt1);
				break;
		  }
		switch(chan2->form)
		  {
			case SINE16:
				fillChannel(channel2,1024,sine16,chan2,&t2,dt1);
				break;
			case STEPLFM16:
				fillChannel(channel2,1024,stepLFM16,chan2,&t2,dt1);
				break;
			case LFMWAVE16:
				fillChannel(channel2,1024,lfmWave16,chan2,&t2,dt1);
				break;
			case CWAVE16:
				fillChannel(channel2,1024,cancelWave16,chan2,&t2,dt1);
				break;
			default:
				fillChannel(channel2,1024,nullwave,chan2,&t2,dt1);
				break;
		  }
		s+=512;

		riff2_interleave16(buffer,channel1,channel2,2048);
		write(fd,buffer,2048);
	  }
	close(fd);

	/* 16 bit samples */
	printf("%d samples\n",samples);
	printf("t is %f\n",t1);

}
