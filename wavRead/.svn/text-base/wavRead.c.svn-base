/*
 * wavRead.c
 *
 *  Created on: Aug 21, 2010
 *      Author: luke
 */


#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <riff2_pcm.h>
#include <riff2.h>


void printUsage()
{
	printf("wavRead [inputfile].wav\n");

}

struct pcmchunk
{
	struct riff2_pcm_frame header;
	struct riff2_format_chunk fmt;
	struct riff2_pcm_data data;
};

int main(int argc, char *argv[])
{
	int fd;
	char buf[1024];
	struct pcmchunk chunk;
	size_t n=0;
	size_t header = 44;
	if(argc < 2)
	{
		printUsage();
		return 0;
	}
	printf("header is %d bytes and chunk is %d bytes\n",44,44);
	if((fd = open(argv[1],O_RDONLY))<0)
	{
		fprintf(stderr,"open() failed: %s\n",argv[1]);
		return 0;
	}
	printf("opened %s\n",argv[1]);

	while(n < 44)
		n+=read(fd,buf,header);

	memcpy(&chunk,buf,44);

	riff2_fprint_frame(stdout,&chunk.header);
	riff2_fprint_format(stdout,&chunk.fmt);
	close(fd);
	return 0;
}
