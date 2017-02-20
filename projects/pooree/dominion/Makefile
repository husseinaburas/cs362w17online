CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -std=c99 -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o
	./randomtestadventurer &> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -std=c99 -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o
	./randomtestcard1 &> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -std=c99 -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o
	./randomtestcard2 &> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittestresults.out: cardtest1.c cardtest2.c cardtest3.c cardtest4.c unittest1.c unittest2.c unittest3.c unittest4.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -std=c99 -o cardtest1 -g cardtest1.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -std=c99 -o cardtest2 -g cardtest2.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -std=c99 -o cardtest3 -g cardtest3.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -std=c99 -o cardtest4 -g cardtest4.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -std=c99 -o unittest1 -g unittest1.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -std=c99 -o unittest2 -g unittest2.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -std=c99 -o unittest3 -g unittest3.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -std=c99 -o unittest4 -g unittest4.c dominion.o rngs.o
	./cardtest1 &> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard randomtestadventurer randomtestcard1 randomtestcard2

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 testInit.exe *.gcov *.gcda *.gcno *.so
