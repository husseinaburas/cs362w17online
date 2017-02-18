CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)
	
randomtestadventurer: dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	
all: randomtestadventurer randomtestcard1 randomtestcard2 

randomtestcard1.out: randomtestcard1
	./randomtestcard1 >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out

randomtestcard2.out: randomtestcard2
	./randomtestcard2 >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out

randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out

coverage.out: randomtestcard1 randomtestcard2 randomtestadventurer
	./randomtestcard1 >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	./randomtestcard2 >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	gcov dominion.c -b >> coverage.out
	cat dominion.c.gcov >> coverage.out

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out