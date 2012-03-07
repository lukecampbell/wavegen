/*
 * libriff2 - A set of functions for dealing with the RIFF Format
 * Copyright (C) 2010  Lucas Campbell
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
/**
 * @file PCM.c
 * @brief function definitions for PCM handling
 * @author Lucas Campbell <luke.s.campbell@gmail.com>
 * @date 7/19/2010
 */
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "riff2_pcm.h"
#include "riff2.h"

/**
 * Copy the riff2_pcm_frame into a buffer of length len (in preparation for
 * writing usually to a fd)
 * @param buffer The buffer into which frame is copied into
 * @param len The length in bytes of buffer
 * @param frame The riff2_pcm_frame that you wish to copy
 */
size_t 
riff2_framencpy(char *buffer, size_t len, struct riff2_pcm_frame *frame)
{
	size_t rLen = sizeof(struct riff2_pcm_frame);
	if(len < rLen)
		return 0;
	memcpy(buffer,frame,rLen);
	return rLen;
}
/**
 * Write the frame to the file descriptor by calling syscall write()
 * @param fd The file descriptor where frame is written
 * @param frame the riff2_pcm_frame that is going to be written to fd
 */
ssize_t 
riff2_write_frame(int fd, struct riff2_pcm_frame *frame)
{
	int n = sizeof(struct riff2_pcm_frame);
	char buf[n];
	riff2_framencpy(buf,n,frame);
	return write(fd,buf,n);
}
/**
 * Copy the riff2_format_chunk to a (char *)
 * @param buffer The buffer into which fmt will be copied
 * @param len The length of buffer in bytes
 * @param fmt the riff2_format_chunk that will be copied
 */
size_t 
riff2_formatncpy(char *buffer, size_t len, struct riff2_format_chunk *fmt)
{
	size_t rLen = sizeof(struct riff2_format_chunk);
	if(len < rLen)
		return 0;
	memcpy(buffer,fmt,rLen);
	return rLen;
}
/**
 * Writes the riff2_format_chunk into the filedescriptor
 * @param fd The file descriptor that fmt will be written to
 * @param fmt the riff2_format_chunk that will be written
 */
ssize_t 
riff2_write_format(int fd, struct riff2_format_chunk *fmt)
{
	int n = sizeof(struct riff2_format_chunk);
	char buf[n];
	riff2_formatncpy(buf,n,fmt);
	return write(fd,buf,n);
}
/**
 * Copy the riff2_pcm_data chunk into the buffer (char *)
 * @param buffer The buffer to which the riff2_pcm_data frame is copied
 * @param len The length of the buffer
 * @param frame the riff2_pcm_data frame that will be copied
 */
size_t 
riff2_datancpy(char *buffer, size_t len, struct riff2_pcm_data *frame)
{
	size_t rLen = sizeof(struct riff2_pcm_data);
	if(len < rLen)
		return 0;
	memcpy(buffer,frame,rLen);
	return rLen;
}
/**
 * Write riff2_pcm_data frame to a file descriptor
 * @param fd The file descriptor to which the frame will be written
 * @param frame The riff2_pcm_data frame that will be written
 */
ssize_t 
riff2_write_data(int fd, struct riff2_pcm_data *frame)
{
	int n = sizeof(struct riff2_pcm_data);
	char buf[n];
	riff2_datancpy(buf,n,frame);
	return write(fd,buf,n);
}
/**
 * Interleave strings c1 and c2 alternating every 16 bits into buf of length len
 * @param buf The buffer that will be the result
 * @param c1 String buffer 1 (usually channel 0 or left)
 * @param c2 String buffer 2 (usually channel 1 or right)
 * @param len Length of buffer buf
 * @return total number of bytes interleaved (c1+c2)
 */
size_t 
riff2_interleave16(char *buf, char *c1, char *c2, size_t len)
{
	/* data streams are NULL terminated */
	int j=0;
	for(j=0;j<len;j++)
	  {
		if(c1 == '\0' || c2 == '\0')
			break;
		if ( (j % 4) < 2 )
			buf[j]= *(c1++);
		else
			buf[j]= *(c2++);
	  }
	return j;
}

/**
 * Set the riff2_pcm_frame, riff2_format_chunk and riff2_pcm_data chunks using a settings struct
 * @param pcmHeader The header chunk
 * @param fmc The format chunk
 * @param dataFrame The data frame
 * @param set The Settings to assign to all the other members
 *
 */
void 
riff2_settings(struct riff2_pcm_frame *pcmHeader, struct riff2_format_chunk *fmc,
 		struct riff2_pcm_data* dataFrame,
		const struct riff2_pcm_settings *set)
{
	int samples = (int)(set->len * set->sampleRate);
	pcmHeader->ckID = CHUNK_ID_RIFF;
	pcmHeader->waveID = WAVE_ID_WAVE;
	pcmHeader->ckSize = 4 + 24 + 8 + (samples * set->bytesPerSample * set->channels);
	fmc->ckID = CHUNK_ID_FMT;
	fmc->ckSize = 16;
	fmc->nChannels = set->channels;
	fmc->nSamplesPerSec = set->sampleRate;
	fmc->wFormatTag = WAVE_FORMAT_PCM;
	fmc->nBlockAlign = set->bytesPerSample * set->channels;
	fmc->wBitsPerSample = 8 * set->bytesPerSample;
	fmc->nAvgbytesPerSec = set->sampleRate * set->channels * set->bytesPerSample;
	dataFrame->ckID = CHUNK_ID_DATA;
	dataFrame->ckSize = samples * set->channels * set->bytesPerSample;

}
/**
 * Print details to stdout
 * @param pcmHeader the header
 */
void 
riff2_fprint_frame(FILE *stream, struct riff2_pcm_frame *pcmHeader)
{
	uint32_t cid_riff = CHUNK_ID_RIFF;
	uint32_t cid_fmt = CHUNK_ID_FMT;
	uint32_t cid_data = CHUNK_ID_DATA;
	uint32_t wid_wave = WAVE_ID_WAVE;
	fprintf(stream, "Chunk ID: ");
	if(pcmHeader->ckID == cid_riff)
		fprintf(stream, "RIFF\n");
	else if (pcmHeader ->ckID == cid_fmt)
		fprintf(stream, "FMT \n");
	else if (pcmHeader->ckID == cid_data)
		fprintf(stream, "DATA \n");
	else
		fprintf(stream, "unknown\n");
	fprintf(stream,"Chunk Size: %d\n",pcmHeader->ckSize);
	fprintf(stream, "Wave ID: ");
	if(pcmHeader->waveID == wid_wave)
		fprintf(stream, "WAVE\n");
	else
		fprintf(stream, "unknown\n");

}
/**
 * Print the riff2_format_chunk
 * @param fmt The Format Chunk
 */
void 
riff2_fprint_format(FILE *stream, struct riff2_format_chunk *fmt)
{
	uint32_t cid_fmt = CHUNK_ID_FMT;
	fprintf(stream, "--Format Chunk--\n");
	fprintf(stream, "\tChunk ID: ");
	if(fmt->ckID == cid_fmt)
		fprintf(stream, "FMT\n");
	else
		fprintf(stream, "unknown\n");
	fprintf(stream, "\tChunk Size: %d\n",fmt->ckSize);
	fprintf(stream, "\tFormat Tag: ");
	if(fmt->wFormatTag == 0x01)
		fprintf(stream, "PCM\n");
	else if(fmt->wFormatTag == 0x03)
		fprintf(stream, "IEEE Float\n");
	else if(fmt->wFormatTag == 0x06)
		fprintf(stream, "8-bit ITU-T G.711 A-law\n");
	else if(fmt->wFormatTag == 0x07)
		fprintf(stream, "8-bit ITU_T G.711 µ-law\n");
	else if(fmt->wFormatTag == 0xFFFE)
		fprintf(stream, "extensible\n");
	else
		fprintf(stream, "unknown\n");
	fprintf(stream, "\tChannels: %d\n",fmt->nChannels);
	fprintf(stream, "\tSamples Per Second: %d\n",fmt->nSamplesPerSec);
	fprintf(stream, "\tAvg bytes Per Sec: %d\n",fmt->nAvgbytesPerSec);
	fprintf(stream, "\tBlock Align: %d\n",fmt->nBlockAlign);
	fprintf(stream, "\tbits per sample: %d\n",fmt->wBitsPerSample);
}
/**
 * Print the Data Chunk details
 * @param data The riff2_pcm_data Frame
 */
void 
riff2_fprint_data(FILE *stream, struct riff2_pcm_data *data)
{
	uint32_t cid = CHUNK_ID_DATA;
	fprintf(stream, "--DATA CHUNK--\n");
	if(data->ckID != cid)
		fprintf(stream, "\tInvalid Chunk ID: %X\n",data->ckID);
	else
		fprintf(stream, "\tChunk ID: DATA\n");
	fprintf(stream, "\tChunk Size: %d\n",data->ckSize);
}
