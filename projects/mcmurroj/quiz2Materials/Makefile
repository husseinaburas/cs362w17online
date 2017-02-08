CFLAGS = -Wall -fpic -coverage -lm

default: testme.c
	gcc testme.c -o testme  $(CFLAGS)

clean:
	rm -f *.o testme *.gcov *.gcda *.gcno *.so
