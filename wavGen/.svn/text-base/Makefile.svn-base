CC = gcc
GTKCFLAGS=`/usr/bin/pkg-config --cflags gtk+-2.0`
GTKLIBFLAGS=`/usr/bin/pkg-config --libs gtk+-2.0`
LIBS = -lriff2 -lm
CFLAGS = -ggdb -Wall


all: waveGen

waveGen: gtkmethods.o main.o waveforms.o template.xml
	$(CC) -o waveGen gtkmethods.o main.o waveforms.o $(GTKLIBFLAGS) $(LIBS)
main.o: main.c
	$(CC) -c main.c $(GTKCFLAGS) $(CFLAGS)
gtkmethods.o: gtkmethods.c
	$(CC) -c gtkmethods.c $(GTKCFLAGS) $(CFLAGS)
waveforms.o: waveforms.c
	$(CC) -c waveforms.c $(GTKCFLAGS) $(CFLAGS)
	
template.xml: template.glade
	gtk-builder-convert template.glade template.xml

	
clean: 
	rm -rf *.o
	rm -rf *.wav
	rm -rf template.xml
	
