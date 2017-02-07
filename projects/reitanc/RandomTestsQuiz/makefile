CFLAGS = -Wall -fpic -coverage -lm -g -std=c99

default: testme.out

testme.out: 
	echo "Results for running Random Test Quiz:" > results.out
	gcc -o testme.out testme.c $(CFLAGS)
	testme.out >> results.out
	gcov testme.c >> results.out

clean:
	rm testme.out

cleanall: 
	rm testme.out results.out *.gcda *.gcno *.gcov
