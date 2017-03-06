CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

refactor.o: dominion.h refactor.h refactor.c 
	gcc -c refactor.c -g   $(CFLAGS)

dominion.o: dominion.h refactor.h dominion.c rngs.o
	gcc -c dominion.c refactor.c -g   $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o  refactor.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o  refactor.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o refactor.o  rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o refactor.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o  refactor.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o  refactor.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o refactor.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o  refactor.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestadventurer: randomtestadventurer.c dominion.o refactor.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o refactor.o rngs.o $(CFLAGS)
	
randomtestcard1: randomtestcard1.c dominion.o refactor.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o refactor.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o refactor.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o refactor.o rngs.o $(CFLAGS)	

randomtestadventurer.out:  randomtestadventurer
	./randomtestadventurer 3 &> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	gcov -b refactor.c >> randomtestadventurer.out
	cat refactor.c.gcov >> randomtestadventurer.out	

randomtestcard1.out:  randomtestcard1
	./randomtestcard1 5 &> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	gcov -b refactor.c >> randomtestcard1.out
	cat refactor.c.gcov >> randomtestcard1.out

randomtestcard2.out:  randomtestcard2
	./randomtestcard2 3 &> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	gcov -b refactor.c >> randomtestcard2.out
	cat refactor.c.gcov >> randomtestcard2.out

	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o refactor.o  rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so