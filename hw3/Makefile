#Makefile: PhotoLab2

all: PhotoLab2

PhotoLab2: PhotoLab.o FileIO.o DIPs.o Advanced.o
	gcc -Wall -ansi PhotoLab.o FileIO.o DIPs.o Advanced.o -o PhotoLab2

PhotoLab.o: PhotoLab.c Constants.h
	gcc -Wall -ansi -c PhotoLab.c -o PhotoLab.o

FileIO.o: FileIO.c FileIO.h Constants.h
	gcc -Wall -ansi -c FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	gcc -Wall -ansi -c DIPs.c -o DIPs.o

Advanced.o: Advanced.c Advanced.h Constants.h
	gcc -Wall -ansi -c Advanced.c -o Advanced.o

clean:
	rm -f *.o
	rm -f PhotoLab2

