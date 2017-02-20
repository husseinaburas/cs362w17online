CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g $(CFLAGS)

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

RandomTestCard1: RandomTestCard1.c dominion.o rngs.o
	gcc -o RandomTestCard1 -g RandomTestCard1.c dominion.o rngs.o $(CFLAGS)

RandomTestCard2: RandomTestCard2.c dominion.o rngs.o
	gcc -o RandomTestCard2 -g RandomTestCard2.c dominion.o rngs.o $(CFLAGS)

RandomTestAdventurer: RandomTestAdventurer.c dominion.o rngs.o
	gcc -o RandomTestAdventurer -g RandomTestAdventurer.c dominion.o rngs.o $(CFLAGS)
	
runtests: testDrawCard 
	./unittest1 &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestresults.out: RandomTestCard1 RandomTestCard2 RandomTestAdventurer
	echo "Results saved to randomtestresults.out" &> randomtestresults.out
	./RandomTestCard1.c ${ARGS} >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	./RandomTestCard2 ${ARGS} >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	./RandomTestAdventurer ${ARGS} >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.out *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
