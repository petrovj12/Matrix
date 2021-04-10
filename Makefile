CC=gcc

all:
	$(CC) -c cmatrix.c -o cmatrix.o -lncurses
	$(CC) -c mat_f.c -o mat_f.o -lncurses
	$(CC) mat_f.o cmatrix.o -o cmatrix -lncurses
clean:
	rm cmatrix.o mat_f.o cmatrix
