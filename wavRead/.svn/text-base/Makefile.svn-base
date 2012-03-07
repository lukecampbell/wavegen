

CC=gcc
DEFINE=
LINCLUDE = 
LIBS = -lriff2
WARNING = -Wall
all: wavRead

wavRead: wavRead.o 
	$(CC) $(WARNING) -o wavRead $(DEFINE) $(LINCLUDE) wavRead.o $(LIBS) 
	
wavRead.o: wavRead.c
	$(CC) $(WARNING) $(DEFINE) -c wavRead.c
	


clean:
	rm -rf *.o
