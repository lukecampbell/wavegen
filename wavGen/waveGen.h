/*
 * waveGen.h
 *
 *  Created on: Aug 19, 2010
 *      Author: Lucas Campbell
 */

#ifndef WAVEGEN_H_
#define WAVEGEN_H_
#define MAX_AMPLITUDE 	0x7FFFFFFF;
#define MIN_AMPLITUDE 	0x80000000;
#define SAMPLE_RATE 	8000;

#define SINE16		0x01
#define	STEPLFM16	0x02
#define TESTWAVE16	0x04
#define	LFMWAVE16	0x08
#define	CWAVE16		0x10
#define	NULLWAVE16	0x00
/**
 * Structure to hold the three frequencies
 */
typedef struct {
	double freq1;
	double freq2;
	double freq3;
}TriFreq;
/**
 * Structure to specify the waveform
 */
typedef struct {
	int form; 		/*!< the waveform 				*/
	double time;	/*!< time of the waveform 		*/
	double freq;	/*!< frequency of the waveform	*/
	double t_offset;/*!< time offset				*/
	double volume;	/*!< volume coefficient			*/
	TriFreq lfm;	/*!< Three frequencies for trifreq */

}Waveform;
/**
 * 32 bit union
 */
typedef union {
	signed int val;
	char bytes[4];
}endianValue32;
/**
 * 16 bit union
 */
typedef union {
	signed short int val;
	char bytes[2];
}endianValue16;

typedef signed short int s_int16;				/*!< signed 16-bit integer */

typedef s_int16 (*waveForm16) (Waveform *wf);	/*!< 16 bit wave-generating function pointer */
/*! @brief Generates the output */
void generate(char *filename, Waveform *chan1, Waveform *chan2, double len);
/*! @brief Fills the buffer with the waveform */
void fillChannel(char *buf, size_t len,waveForm16 w16, Waveform *wf, double *t, const double dt);
s_int16 nullwave(Waveform *wf);
s_int16 testWaveB16(Waveform *wf);
s_int16 cancelWave16(Waveform *wf);
//s_int16 lfmWave16(double freqBase, double freqEnd, double t_offset);
//s_int16 testWave16(Waveform *wf);
s_int16 lfmWave16(Waveform *wf);
s_int16 stepLFM16(Waveform *wf);
s_int16 sine16(Waveform *wf);


/* defined as amplitude */



#endif /* WAVEGEN_H_ */
