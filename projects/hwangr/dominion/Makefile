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

unittest1: dominion.o unittest1.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o unittest1.o rngs.o -o unittest1 -lm -g  $(CFLAGS)

unittest2: dominion.o unittest2.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o unittest2.o rngs.o -o unittest2 -lm -g  $(CFLAGS)

unittest3: dominion.o unittest3.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o unittest3.o rngs.o -o unittest3 -lm -g  $(CFLAGS)

unittest4: dominion.o unittest4.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o unittest4.o rngs.o -o unittest4 -lm -g  $(CFLAGS)

cardtest1: dominion.o cardtest1.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest1.o rngs.o -o cardtest1 -lm -g  $(CFLAGS)

cardtest2: dominion.o cardtest2.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest2.o rngs.o -o cardtest2 -lm -g  $(CFLAGS)

cardtest3: dominion.o cardtest3.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest3.o rngs.o -o cardtest3 -lm -g  $(CFLAGS)

cardtest4: dominion.o cardtest4.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest4.o rngs.o -o cardtest4 -lm -g  $(CFLAGS)


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
