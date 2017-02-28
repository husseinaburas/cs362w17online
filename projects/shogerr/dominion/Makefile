CFLAGS = -Wall -fpic -coverage -lm

all: playdom player testDrawCard testBuyCard badTestDrawCard

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

player: player.c interface.o
	gcc -o player player.c -g dominion.o rngs.o interface.o $(CFLAGS)

unittest.out: unittest1 unittest2 unittest3 unittest4
	rm -f unittestresult.out
	touch unittestresult.out
	./unittest1 >> unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	gcov -b dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: unittest1.c dominion.o rngs.o
	gcc -o $@ $< -g dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o $@ $< -g dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o $@ $< -g dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o $@ $< -g dominion.o rngs.o  $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o $@ $< -g dominion.o rngs.o  $(CFLAGS)

#cardtest2: cardtest2.c dominion.o rngs.o
#	gcc -o $@ $< -g dominion.o rngs.o  $(CFLAGS)

#cardtest3: cardtest3.c dominion.o rngs.o
#	gcc -o $@ $< -g dominion.o rngs.o  $(CFLAGS)

#cardtest4: cardtest4.c dominion.o rngs.o
#	gcc -o $@ $< -g dominion.o rngs.o  $(CFLAGS)

randomtestadventurer: randomtestadventurer.c randomtest.o dominion.o rngs.o
	gcc -o $@ $< -g `echo $(filter-out $<, $^)` $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o $@ $< -g `echo $(filter-out $<, $^)` $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o $@ $< -g `echo $(filter-out $<, $^)` $(CFLAGS)

randomtest.o: randomtest.h randomtest.c
	gcc -c randomtest.c -g

clean:
	rm -f *.o *.out playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so

.PHONY: clean unittest.out
