
CC=gcc
LIBS = -lpulse -lpulse-simple -lriff2
LINCLUDE = 
WARNING = -Wall

all: wavPlayer
wavPlayer: wavPlayer.o 
	$(CC) $(WARNING) -o wavPlayer $(LINCLUDE) wavPlayer.o $(LIBS)
	
wavPlayer.o: wavPlayer.c
	$(CC) $(WARNING) -c wavPlayer.c
	
	

clean:
	rm -rf *.o
	
