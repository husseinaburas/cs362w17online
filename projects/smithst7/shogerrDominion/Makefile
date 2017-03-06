CFLAGS = -Wall -fpic -coverage -lm -std=c99

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

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	./unittest1 > unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtest1: randomtestcard1 randomtestcard1.c  dominion.o rngs.o $(CFLAGS)
	gcc randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	gcov dominion.c >>  randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtest2: randomtestcard2 randomtestcard2.c  dominion.o rngs.o $(CFLAGS)
	gcc randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	gcov dominion.c >>  randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer: randomtestadventurer randomtestadventurer.c  dominion.o rngs.o $(CFLAGS)
	gcc randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c >>  randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
