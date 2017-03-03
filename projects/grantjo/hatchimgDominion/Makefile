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

unit1:	unittest1.c dominion.o rngs.o
	gcc -o unit1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unit2: unittest2.c dominion.o rngs.o
	gcc -o unit2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unit3: unittest3.c dominion.o rngs.o
	gcc -o unit3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unit4: unittest4.c dominion.o rngs.o
	gcc -o unit4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

card1: cardtest1.c dominion.o rngs.o
	gcc -o card1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

card2: cardtest2.c dominion.o rngs.o
	gcc -o card2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

card3: cardtest3.c dominion.o rngs.o
	gcc -o card3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

card4: cardtest4.c dominion.o rngs.o
	gcc -o card4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard unit1 unit2 unit3 unit4 card1 card2 card3 card4 randomtestadventurer randomtestcard1 randomtestcard2

unittestresults.out: playdom player testDrawCard testBuyCard badTestDrawCard unit1 unit2 unit3 unit4 card1 card2 card3 card4
	rm -rf dominion.gcda
	./unit1 > unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	#cat dominion.c.gcov >> unittestresults.out
	rm -rf dominion.gcda
	./unit2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	#cat dominion.c.gcov >> unittestresults.out
	rm -rf dominion.gcda
	./unit3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	rm -rf dominion.gcda
	./unit4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	rm -rf dominion.gcda
	./card1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	rm -rf dominion.gcda
	./card2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	rm -rf dominion.gcda
	./card3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	rm -rf dominion.gcda
	./card4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

randomtestadventurer.out: playdom player testDrawCard testBuyCard badTestDrawCard randomtestadventurer
	rm -rf dominion.gcda
	./randomtestadventurer -1 > randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	
randomtestcard1.out: playdom player testDrawCard testBuyCard badTestDrawCard randomtestcard1
	rm -rf dominion.gcda
	./randomtestcard1 -1 > randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	
randomtestcard2.out: playdom player testDrawCard testBuyCard badTestDrawCard randomtestcard2
	rm -rf dominion.gcda
	./randomtestcard2 -1 > randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	
clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
