CFLAGS = -Wall -fpic -coverage -lm  -std=c99

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

randomtestadventurer.out: randomtestadventurer.c rngs.h rngs.c dominion.h dominion.c
	
	gcc -c rngs.c -g rngs.h rngs.c -Wall -fpic -coverage 
	gcc -c dominion.c -g dominion.h dominion.c -Wall -fpic -coverage -std=c99

	echo "Random Test Adventurer Card" > randomtestadventurer.out
	
	echo "randomtestadventurer.c:" >> randomtestadventurer.out
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	randomtestadventurer $(SEED) >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out

randomtestcard1.out: randomtestcard1.c rngs.h rngs.c dominion.h dominion.c
	
	gcc -c rngs.c -g rngs.h rngs.c -Wall -fpic -coverage 
	gcc -c dominion.c -g dominion.h dominion.c -Wall -fpic -coverage -std=c99

	echo "Random Test Smithy Card" > randomtestcard1.out
	
	echo "randomtestcard1.c:" >> randomtestcard1.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	randomtestcard1 $(SEED) >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out


randomtestcard2.out: randomtestcard2.c rngs.h rngs.c dominion.h dominion.c
	
	gcc -c rngs.c -g rngs.h rngs.c -Wall -fpic -coverage 
	gcc -c dominion.c -g dominion.h dominion.c -Wall -fpic -coverage -std=c99

	echo "Random Test Village Card" > randomtestcard2.out
	
	echo "randomtestcard2.c:" >> randomtestcard2.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	randomtestcard2 $(SEED) >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c rngs.h rngs.c dominion.h dominion.c
	gcc -c rngs.c -g rngs.h rngs.c -Wall -fpic -coverage 
	gcc -c dominion.c -g dominion.h dominion.c -Wall -fpic -coverage  -std=c99

	echo "Complete Unit Test Assignment 4" > unittestresults.out
	
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f -r *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.dSYM .DS_Store *.gch

cleantests:
	rm -f -r *.o unittestresults.out unittest1 unittest2 unittest3 unittest4 unittest5 cardtest1 cardtest2 cardtest3 cardtest4 cardtest5 *.gcda *.gcno *.gcov *.dSYM .DS_Store *.gch

cleanrandtests:
	rm -f -r *.o randomtestadventurer.out randomtestcard1.out randomtestcard2.out randomtestcard1 randomtestcard2 randomtestadventurer *.gcda *.gcno *.gcov *.dSYM .DS_Store *.gch