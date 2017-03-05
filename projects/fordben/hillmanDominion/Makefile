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
	
unittest1: unittest1.c dominion.c rngs.o
	gcc -o unittest1 -g unittest1.c dominion.c rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.c rngs.o
	gcc -o unittest2 -g unittest2.c dominion.c rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.c rngs.o
	gcc -o unittest3 -g unittest3.c dominion.c rngs.o $(CFLAGS)	

unittest4: unittest4.c dominion.c rngs.o
	gcc -o unittest4 -g unittest4.c dominion.c rngs.o $(CFLAGS)
	
cardtest1: cardtest1.c dominion.c rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.c rngs.o $(CFLAGS)
	
cardtest2: cardtest2.c dominion.c rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.c rngs.o $(CFLAGS)
	
cardtest3: cardtest3.c dominion.c rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.c rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.c rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.c rngs.o $(CFLAGS)
	
unittestresults.out: unittest1.c unittest2.c unittest3.c dominion.c rngs.o rngs.c rngs.h
	gcc -o unittest1 -g unittest1.c dominion.c rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

	gcc -o unittest2 -g unittest2.c dominion.c rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	gcc -o unittest3 -g unittest3.c dominion.c rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	gcc -o unittest4 -g unittest4.c dominion.c rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	gcc -o cardtest1 -g cardtest1.c dominion.c rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	gcc -o cardtest2 -g cardtest2.c dominion.c rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	
	gcc -o cardtest3 -g cardtest3.c dominion.c rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -o cardtest4 -g cardtest4.c dominion.c rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	

unittests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4

randomtestcard1: randomtestcard1.c dominion.c rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.c rngs.o $(CFLAGS)
	
randomtestcard1.out: randomtestcard1 dominion.c rngs.o rngs.c rngs.h
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.c rngs.o $(CFLAGS)
	./randomtestcard1 34 >> randomtestcard1.out
	gcov -b -f dominion.c >> randomtestcard1.out

randomtestcard2.out: randomtestcard2 dominion.c rngs.o rngs.c rngs.h
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.c rngs.o $(CFLAGS)
	./randomtestcard2 20 >> randomtestcard2.out
	gcov -b -f dominion.c >> randomtestcard2.out

randomtestadventurer.out: randomtestadventurer dominion.c rngs.o rngs.c rngs.h	
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.c rngs.o $(CFLAGS)
	./randomtestadventurer 21 >> randomtestadventurer.out
	gcov -b -f dominion.c >> randomtestadventurer.out
	
randomtestcard2: randomtestcard2.c dominion.c rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.c rngs.o $(CFLAGS)
	
randomtestadventurer:  randomtestadventurer.c dominion.c rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.c rngs.o $(CFLAGS)
	
randomtestcard.out: randomtestcard1 dominion.c rngs.o rngs.c rngs.h
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.c rngs.o $(CFLAGS)
	./randomtestcard1 34 >> randomtestcard.out
	gcov -b -f dominion.c >> randomtestcard.out
	
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.c rngs.o $(CFLAGS)
	./randomtestcard2 20 >> randomtestcard.out
	gcov -b -f dominion.c >> randomtestcard.out
	
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.c rngs.o $(CFLAGS)
	./randomtestadventurer 21 >> randomtestcard.out
	gcov -b -f dominion.c >> randomtestcard.out
	
randomtests: randomtestcard1 randomtestcard2 randomtestadventurer
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe
