CFLAGS = -fpic -coverage -lm -std=c99 -ftest-coverage -fprofile-arcs

all:
	gcc -o test.run -g testme.c  $(CFLAGS)

test: all
	./test.run
