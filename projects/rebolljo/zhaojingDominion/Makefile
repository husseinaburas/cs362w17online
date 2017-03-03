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

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -std=c99 -g cardtest1.c -o cardtest1 dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -std=c99 -g cardtest2.c -o cardtest2 dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -std=c99 -g cardtest3.c -o cardtest3 dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -std=c99 -g cardtest4.c -o cardtest4 dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -std=c99 -g unittest1.c -o unittest1 dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -std=c99 -g unittest2.c -o unittest2 dominion.o rngs.o $(CFLAGS) 

unittest3: unittest3.c dominion.o rngs.o
	gcc -std=c99 -g unittest3.c -o unittest3 dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -std=c99 -g unittest4.c -o unittest4 dominion.o rngs.o  $(CFLAGS)

unittestresults.out: cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4
	rm -f unittestresults.out
	./cardtest1 &> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >>unittestresults.out

quickresults.out: randomtestadventurer randomtestcard1 randomtestcard2
	rm -f randomtestadventurer.out
	rm -f randomtestcard1.out
	rm -f randomtestcard2.out
	./randomtestadventurer
	./randomtestcard1
	./randomtestcard2

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -std=c99 -g randomtestadventurer.c -o randomtestadventurer dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -std=c99 -g randomtestcard1.c -o randomtestcard1 dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -std=c99 -g randomtestcard2.c -o randomtestcard2 dominion.o rngs.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer 
	rm -f randomtestadventurer.out
	./randomtestadventurer 55 &> randomtestadventurer.out
	gcov -b -f dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard1.out: randomtestcard1
	rm -f randomtestcard1.out
	./randomtestcard1 55 &> randomtestcard1.out
	gcov -b -f dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: randomtestcard2
	rm -f randomtestcard2.out
	./randomtestcard2 55 &> randomtestcard2.out
	gcov -b -f dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	
removefiles:
	rm -f randomtestadventurer
	rm -f randomtestcard1
	rm -f randomtestcard2

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
