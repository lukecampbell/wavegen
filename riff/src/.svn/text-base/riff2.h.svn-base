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
 * @file riff.h
 * @brief Declarations for pertinent information to RIFF format .wav
 * @date 7/19/2010
 * @author Lucas Campbell <luke.s.campbell@gmail.com>
 */

#ifndef RIFF2_H_
#define RIFF2_H_

#define RIFF2_VERSION 1.0

#define WAVE_FORMAT_PCM 		0x0001 //!< Standard PCM Definition
#define WAVE_FORMAT_IEEE_FLOAT	0x0003 //!< IEEE Float Format
#define WAVE_FORMAT_ALAW		0x0006 //!< 8-bit ITU-T G.711 A-law
#define WAVE_FORMAT_MULAW		0x0007 //!< 8-bit ITU_T G.711 µ-law
#define WAVE_FORMAT_EXTENSIBLE	0xFFFE	//!< Determined by SubFormat



#ifdef RIFF_LITTLE_ENDIAN
#pragma "LITTLE ENDIAN IS DEFINED"
#define CHUNK_ID_RIFF	0x46464952 //!< "RIFF"
#define WAVE_ID_WAVE	0x45564157 //!< "WAVE"
#define CHUNK_ID_FMT	0x20746D66 //!< "FMT "
#define CHUNK_ID_DATA	0x61746164 //!< "DATA"
#endif /* def LITTLE_ENDIAN */


#ifdef RIFF_BIG_ENDIAN
#pragma "BIG ENDIAN IS DEFINED"
#define CHUNK_ID_RIFF	0x52494646
#define WAVE_ID_WAVE	0x57415645
#define CHUNK_ID_FMT	0x666D7420
#define CHUNK_ID_DATA	0x64617461
#endif /* def BIG_ENDIAN */


#include <inttypes.h> /* for uint32_t */

/**
 * Basic chunk
 */
struct riff2_chunk
{
	uint32_t ckID; /*!< Chunk ID: "RIFF" */
	uint32_t cksize; /*!< Chunk Size: 4+n */
	uint32_t waveID; /*!< WAVE ID: "WAVE" */
	uint32_t waveChunks;  /*!< Wave chunks containing format information and sampled data */
};
/*----------------------------------------*/
/**
 * Format Chunk containing specific formatting data
 */
struct riff2_format_chunk
{

	uint32_t ckID;			/*!< Chunk ID: "fmt " */
	uint32_t ckSize;			/*!< chunk size: 16, 18 or 40 */
	uint16_t wFormatTag;		/*!< format code */
	uint16_t nChannels;		/*!< number of inerleaved channels */
	uint32_t nSamplesPerSec;		/*!< sampling rate (blocks per second */
	uint32_t nAvgbytesPerSec;		/*!< data rate */
	uint16_t nBlockAlign;		/*!< data block size (bytes) */
	uint16_t wBitsPerSample;	/*!< bits per sample */

};
/**
 * Format Chunk Extended v2
 */
struct riff2_format_chunk_v2
{

	uint32_t ckID;			/*!< Chunk ID: "fmt " */
	uint32_t ckSize;			/*!< chunk size: 16, 18 or 40 */
	uint16_t wFormatTag;		/*!< format code */
	uint16_t nChannels;		/*!< number of inerleaved channels */
	uint32_t nSamplesPerSec;		/*!< sampling rate (blocks per second */
	uint32_t nAvgbytesPerSec;		/*!< data rate */
	uint16_t nBlockAlign;		/*!< data block size (bytes) */
	uint16_t wBitsPerSample;	/*!< bits per sample */
	uint16_t cbSize;			/*!< size of the extension 0 or 22 */
};
/**
 * Format Chunk Extended v3
 */
struct riff2_format_chunk_v3
{

	uint32_t ckID;			/*!< Chunk ID: "fmt " */
	uint32_t ckSize;			/*!< chunk size: 16, 18 or 40 */
	uint16_t wFormatTag;		/*!< format code */
	uint16_t nChannels;		/*!< number of inerleaved channels */
	uint32_t nSamplesPerSec;		/*!< sampling rate (blocks per second */
	uint32_t nAvgbytesPerSec;		/*!< data rate */
	uint16_t nBlockAlign;		/*!< data block size (bytes) */
	uint16_t wBitsPerSample;	/*!< bits per sample */
	uint16_t wValidBitsPerSample;  /*!< number of valid bits */
	uint32_t dwChannelMask;			/*!< Speaker Position mask */
	uint8_t SubFormat[16];			/*!< GUID, including data format */

};
#endif /* RIFF_H_ */
