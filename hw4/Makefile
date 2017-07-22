#Makefile: PhotoLab2

all: PhotoLab3

PhotoLab3: PhotoLab.o FileIO.o DIPs.o Advanced.o Image.o
	gcc -g -Wall -ansi PhotoLab.o FileIO.o DIPs.o Advanced.o Image.o -o PhotoLab3

PhotoLab.o: PhotoLab.c Constants.h
	gcc -g -Wall -ansi -c PhotoLab.c -o PhotoLab.o

FileIO.o: FileIO.c FileIO.h Constants.h
	gcc -g -Wall -ansi -c FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	gcc -g -Wall -ansi -c DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h Constants.h
	gcc -g -Wall -ansi -c Advanced.c -o Advanced.o

Image.o: Image.c Image.h Constants.h
	gcc -g -Wall -ansi -c Image.c -o Image.o

clean:
	rm -f *.o
	rm -f PhotoLab3


