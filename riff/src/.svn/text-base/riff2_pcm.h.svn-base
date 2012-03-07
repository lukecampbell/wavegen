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
 * @file PCM.h
 * @brief Declarations for structs and functions pertaining to PCM modifications
 * @author Lucas Campbell <luke.s.campbell@gmail.com>
 * @date 8/19/2010
 */
#include "riff2.h"
#include <unistd.h>
#include <stdio.h>
#ifndef PCM_H_
#define PCM_H_


/**
 * Outlines the entire RIFF Header into one structure
 */
struct riff2_pcm_window
{
	struct riff2_pcm_frame *headChunk; //!< The Header Chunk
	struct riff2_format_chunk *formatChunk; //!< The Format Chunk
	struct riff2_pcm_data *dataChunk; //!< The Data Chunk
};
/**
 * The settings struct used to setup the other structures
 */
struct riff2_pcm_settings
{
	uint32_t bytesPerSample; //!< Number of uint8_ts per sample
	uint32_t sampleRate; //!< The Sample rate (samples per second)
	uint32_t channels; //!< Number of Channels
	double len; //!< The Length of the file in seconds
};
/**
 * Basic PCM Frame
 */
struct riff2_pcm_frame
{
	uint32_t ckID; //!< Chunk ID
	uint32_t ckSize; //!< Chunk Size
	uint32_t waveID; //!< Wave ID

};
/**
 * The Data Chunk
 */
struct riff2_pcm_data
{
	uint32_t ckID; //!< Chunk ID
	uint32_t ckSize; //!< Chunk Size
};

/** FUNCTION DECLARATIONS **/

/*! @brief Copies the frame to the buffer of length len */
size_t riff2_framencpy(char *buffer, size_t len, struct riff2_pcm_frame *frame);
/*! @brief Writes the frame to the file descriptor */
ssize_t riff2_write_frame(int fd, struct riff2_pcm_frame *frame);
/*! @brief Copies the Format Chunk to the buffer of size len */
size_t riff2_formatncpy(char *buffer, size_t len, struct riff2_format_chunk *fmt);
/*! @brief Write the format chunk to the file descriptor fd */
ssize_t riff2_write_format(int fd, struct riff2_format_chunk *fmt);
/*! @brief Copies the Data Frame to the buffer of size len */
size_t riff2_datancpy(char *buffer, size_t len, struct riff2_pcm_data *frame);
/*! @brief Write the Data Frame to the file descriptor fd */
ssize_t riff2_write_data(int fd, struct riff2_pcm_data *frame);
/*! @brief Interleave c1 and c2 into buf of length len */
size_t riff2_interleave16(char *buf, char *c1, char *c2, size_t len);
/*! @brief declare all the members of the following structs using set */
void riff2_settings(struct riff2_pcm_frame *pcmHeader, struct riff2_format_chunk *fmc, struct riff2_pcm_data* dataFrame, const struct riff2_pcm_settings *set);
/*! @brief Print The Frame Header */
void riff2_fprint_frame(FILE *stream, struct riff2_pcm_frame *pcmHeader);
/*! @brief Print the waveFormat Chunk */
void riff2_fprint_format(FILE *stream, struct riff2_format_chunk *fmt);
/*! @brief Print the Data Chunk */
void riff2_fprint_data(FILE *stream, struct riff2_pcm_data *data);

#endif /* PCM_H_ */
