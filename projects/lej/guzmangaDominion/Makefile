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


unit1: dominion.o rngs.o unittest1.c
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o unittest1.c rngs.o -o unittest1 -lm -g

unit2: dominion.o rngs.o unittest2.c
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o unittest2.c rngs.o -o unittest2 -lm -g

unit3: dominion.o rngs.o unittest3.c
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o unittest3.c rngs.o -o unittest3 -lm -g

unit4: dominion.o rngs.o unittest4.c
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o unittest4.c rngs.o -o unittest4 -lm -g

card1: dominion.o rngs.o cardtest1.c
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest1.c rngs.o -o cardtest1 -lm -g

card2: dominion.o rngs.o cardtest2.c
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest2.c rngs.o -o cardtest2 -lm -g

card3: dominion.o rngs.o cardtest3.c
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest3.c rngs.o -o cardtest3 -lm -g

card4: dominion.o rngs.o cardtest4.c
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest4.c rngs.o -o cardtest4 -lm -g


random1: dominion.o rngs.o randomtestcard1.c
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o randomtestcard1.c rngs.o -o randomtestcard1 -lm -g

random2: dominion.o rngs.o randomtestcard2.c
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o randomtestcard2.c rngs.o -o randomtestcard2 -lm -g

randomadventurer: dominion.o rngs.o randomtestadventurer.c
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o randomtestadventurer.c rngs.o -o randomtestadventurer -lm -g


randomtestcard1.out: random1 dominion.o rngs.o
	./randomtestcard1 		&> randomtestcard1.out
	gcov -f dominion.c 		>> randomtestcard1.out
	cat dominion.c.gcov 	>> randomtestcard1.out

randomtestcard2.out: random2 dominion.o rngs.o
	./randomtestcard2		&> randomtestcard2.out
	gcov -f dominion.c 		>> randomtestcard2.out
	cat dominion.c.gcov 	>> randomtestcard2.out

randomtestadventurer.out: randomadventurer dominion.o rngs.o
	./randomtestadventurer		&> randomtestadventurer.out
	gcov -f dominion.c 			>> randomtestadventurer.out
	cat dominion.c.gcov 		>> randomtestadventurer.out


unittestresults.out: unit1 unit2 unit3 unit4 card1 card2 card3 card4 dominion.o rngs.o
	./unittest1 &> unittestresults.out 
	./unittest2 >> unittestresults.out 
	./unittest3 >> unittestresults.out 
	./unittest4 >> unittestresults.out 
	./cardtest1 >> unittestresults.out 
	./cardtest2 >> unittestresults.out 
	./cardtest3 >> unittestresults.out 
	./cardtest4 >> unittestresults.out 
	gcov -b dominion.c     >> unittestresults.out 
	cat dominion.c.gcov >> unittestresults.out 
	gcov -b unittest1.c 	>> unittestresults.out 
	gcov -b unittest2.c 	>> unittestresults.out 
	gcov -b unittest3.c 	>> unittestresults.out 
	gcov -b unittest4.c 	>> unittestresults.out 
	gcov -b cardtest1.c 	>> unittestresults.out 
	gcov -b cardtest2.c 	>> unittestresults.out 
	gcov -b cardtest3.c 	>> unittestresults.out 
	gcov -b cardtest4.c 	>> unittestresults.out 



interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard unit1 unit2 unit3 unit4 card1 card2 card3 card4 random1 random2 randomadventurer

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestcard2 randomtestcardadventurer *.gcov *.gcda *.gcno *.so
