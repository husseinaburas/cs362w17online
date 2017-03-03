CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

randGameState.o: randGameState.h randGameState.c 
	gcc -c randGameState.c $(CFLAGS)

randomtestcard1: randomtestcard1.c randGameState.o dominion.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.c randGameState.o dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c randGameState.o dominion.o rngs.o
	gcc -o randomtestcard2 randomtestcard2.c randGameState.o dominion.o rngs.o $(CFLAGS)
	
randomtestadventurer: randomtestadventurer.c randGameState.o dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c randGameState.o dominion.o rngs.o $(CFLAGS)
	
randomtests: randGameState.o randomtestcard1 randomtestcard2 randomtestadventurer
	./randomtestcard1 5 &> randomtestcard1.out
	./randomtestcard2 5 &> randomtestcard2.out
	./randomtestadventurer 5 &> randomtestadventurer.out
	gcov -b -f dominion.c > coverage.out
	gcov dominion.c >> coverage.out
	cat dominion.c.gcov >> coverage.out

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so
