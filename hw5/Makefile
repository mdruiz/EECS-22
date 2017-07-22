#Makefile: MovieLab

CC     = gcc
CFLAGS = -ansi -Wall -c
LFLAGS = -ansi -Wall

all: MovieLab

MovieLab: MovieLab.o Movie.o DIPs.o ImageList.o Image.o
	$(CC) $(LFLAGS) MovieLab.o Movie.o DIPs.o ImageList.o  Image.o -o MovieLab

MovieLab.o: MovieLab.c
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o

Movie.o: Movie.c Movie.h
	$(CC) $(CFLAGS) Movie.c -o Movie.o

DIPs.o: DIPs.c DIPs.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

ImageList.o: ImageList.c ImageList.h 
	$(CC) $(CFLAGS) ImageList.c -o ImageList.o

Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o

clean:
	rm -f *.o
	rm -f MovieLab
	rm -f out.yuv

