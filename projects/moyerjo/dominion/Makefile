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
	
testing_helpers.o: testing_helpers.h testing_helpers.c dominion.o rngs.o
	gcc -c testing_helpers.c -g $(CFLAGS)

cardtest1: cardtest1.c testing_helpers.o dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c testing_helpers.o dominion.o rngs.o $(CFLAGS)
	
cardtest2: cardtest2.c testing_helpers.o dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c testing_helpers.o dominion.o rngs.o $(CFLAGS)
	
cardtest3: cardtest3.c testing_helpers.o dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c testing_helpers.o dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c testing_helpers.o dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c testing_helpers.o dominion.o rngs.o $(CFLAGS)
	
unittest1: unittest1.c testing_helpers.o dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c testing_helpers.o dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c testing_helpers.o dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c testing_helpers.o dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c testing_helpers.o dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c testing_helpers.o dominion.o rngs.o $(CFLAGS)
	
unittest4: unittest4.c testing_helpers.o dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c testing_helpers.o dominion.o rngs.o $(CFLAGS)
		
runtests: testDrawCard cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4
	./testDrawCard &> unittestresult.out
	./cardtest1 >> unittestresult.out
	./cardtest2 >> unittestresult.out
	./cardtest3 >> unittestresult.out
	./cardtest4 >> unittestresult.out
	./unittest1 >> unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	
unittestresults.out: cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4
	./cardtest1 &> unittestresult.out
	./cardtest2 &>> unittestresult.out
	./cardtest3 &>> unittestresult.out
	./cardtest4 &>> unittestresult.out
	./unittest1 &>> unittestresult.out
	./unittest2 &>> unittestresult.out
	./unittest3 &>> unittestresult.out
	./unittest4 &>> unittestresult.out
	gcov -b -c cardtest1.c >> unittestresult.out
	cat cardtest1.c >> unittestresult.out
	gcov -b -c cardtest2.c >> unittestresult.out
	cat cardtest2.c >> unittestresult.out
	gcov -b -c cardtest3.c >> unittestresult.out
	cat cardtest3.c >> unittestresult.out
	gcov -b -c cardtest4.c >> unittestresult.out
	cat cardtest4.c >> unittestresult.out
	gcov -b -c unittest1.c >> unittestresult.out
	cat unittest1.c >> unittestresult.out
	gcov -b -c unittest2.c >> unittestresult.out
	cat unittest2.c >> unittestresult.out
	gcov -b -c unittest3.c >> unittestresult.out
	cat unittest3.c >> unittestresult.out
	gcov -b -c unittest4.c >> unittestresult.out
	cat unittest4.c >> unittestresult.out
	gcov -b -c testing_helpers.c >> unittestresult.out
	cat testing_helpers.c >> unittestresult.out
	gcov -b -c dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
