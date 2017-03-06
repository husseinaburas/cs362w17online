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
	
cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	
cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	
cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	
unittest1: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	
runtests: testDrawCard 
	./unittest1 &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

testresults.out: RandomTestCard1 RandomTestCard2 RandomTestAdventurer cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest3 unittest4
	echo "Results saved to randomtestresults.out" &> randomtestresults.out
	./RandomTestCard1.c ${ARGS} >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	./RandomTestCard2 ${ARGS} >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	./RandomTestAdventurer ${ARGS} >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	./cardtest1 >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	./cardtest2 >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	./cardtest3 >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	./cardtest4 >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	./unittest1 >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	./unittest3 >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	./unittest4 >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.out *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
