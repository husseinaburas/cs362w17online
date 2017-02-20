CFLAGS = -Wall -fpic -coverage -lm -w -std=c99

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
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

unit1: dominion.o rngs.o
	gcc -o unittest1 unittest1.c dominion.o rngs.o -g $(CFLAGS)
	
unit2: dominion.o rngs.o
	gcc -o unittest2 unittest2.c dominion.o rngs.o -g $(CFLAGS)
	
unit3: dominion.o rngs.o
	gcc -o unittest3 unittest3.c dominion.o rngs.o -g $(CFLAGS)
	
unit4: dominion.o rngs.o
	gcc -o unittest4 unittest4.c dominion.o rngs.o -g $(CFLAGS)
	
cardtest1: dominion.o rngs.o
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o -g $(CFLAGS)
	
cardtest2: dominion.o rngs.o
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o -g $(CFLAGS)
	
cardtest3: dominion.o rngs.o
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o -g $(CFLAGS)
	
cardtest4: dominion.o rngs.o
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o -g $(CFLAGS)
	
randomtestcard1: dominion.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: dominion.o rngs.o
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	
randomtestadventurer: dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	
randomtestadventurer.out: randomtestadventurer
	
	./randomtestadventurer 8 >> randomtestadventurer.out
	gcov -b dominion.c		 >> randomtestadventurer.out
	cat dominion.c.gcov 	 >> randomtestadventurer.out

randomtestcard1.out: randomtestcard1
	
	./randomtestcard1 8		>> randomtestcard1.out
	gcov -b dominion.c		>> randomtestcard1.out
	cat dominion.c.gcov 	>> randomtestcard1.out

randomtestcard2.out: randomtestcard2
	
	./randomtestcard2 3		>> randomtestcard2.out
	gcov -b dominion.c		>> randomtestcard2.out
	cat dominion.c.gcov 	>> randomtestcard2.out
	
unittestresults.out: unit1 unit2 unit3 unit4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard1 randomtestcard2

	./unittest1 			>> unittestresults.out
	printf '\n' 			>> unittestresults.out
	gcov dominion.c 		>> unittestresults.out
	
	./unittest2 			>> unittestresults.out
	printf '\n' 			>> unittestresults.out
	gcov dominion.c 		>> unittestresults.out
	
	./unittest3 			>> unittestresults.out
	printf '\n' 			>> unittestresults.out
	gcov dominion.c 		>> unittestresults.out
	
	./unittest4 			>> unittestresults.out
	printf '\n' 			>> unittestresults.out
	gcov dominion.c 		>> unittestresults.out
	
	./cardtest1 			>> unittestresults.out
	printf '\n' 			>> unittestresults.out
	gcov dominion.c 		>> unittestresults.out
	
	./cardtest2 			>> unittestresults.out
	printf '\n' 			>> unittestresults.out
	gcov dominion.c 		>> unittestresults.out
	
	./cardtest3 			>> unittestresults.out
	printf '\n' 			>> unittestresults.out
	gcov dominion.c 		>> unittestresults.out
	
	./cardtest4 			>> unittestresults.out
	printf '\n' 			>> unittestresults.out
	gcov dominion.c 		>> unittestresults.out
	
	./randomtestcard1		>> unittestresults.out
	printf '\n'				>> unittestresults.out
	gcov dominion.c			>> unittestresults.out
	
	./randomtestcard2		>> unittestresults.out
	printf '\n'				>> unittestresults.out
	gcov dominion.c			>> unittestresults.out
	
	./randomtestadventurer	>> unittestresults.out
	printf '\n'				>> unittestresults.out
	gcov dominion.c 		>> unittestresults.out
	
clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestcard2 randomtestadventurer *.out
