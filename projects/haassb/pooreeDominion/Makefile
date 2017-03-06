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
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o cardtest1 -g cardtest1.c dominion.o rngs.o

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o cardtest2 -g cardtest2.c dominion.o rngs.o

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o cardtest3 -g cardtest3.c dominion.o rngs.o	
	
cardtest4: cardtest4.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o cardtest4 -g cardtest4.c dominion.o rngs.o
	
unittest1: unittest1.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o unittest1 -g unittest1.c dominion.o rngs.o

unittest2: unittest2.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o unittest2 -g unittest2.c dominion.o rngs.o

unittest3: unittest3.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o unittest3 -g unittest3.c dominion.o rngs.o	
	
unittest4: unittest4.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o unittest4 -g unittest4.c dominion.o rngs.o
	
randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o	

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o		
	
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o	
	
unittestresults.out: cardtest1.c cardtest2.c cardtest3.c cardtest4.c unittest1.c unittest2.c unittest3.c unittest4.c randomtestcard1.c randomtestadventurer.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o cardtest1 -g cardtest1.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o cardtest2 -g cardtest2.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o cardtest3 -g cardtest3.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o cardtest4 -g cardtest4.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o unittest1 -g unittest1.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o unittest2 -g unittest2.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o unittest3 -g unittest3.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o unittest4 -g unittest4.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -lm -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o
	
	./cardtest1 >> unittestresult.out
	./cardtest2 >> unittestresult.out
	./cardtest3 >> unittestresult.out
	./cardtest4 >> unittestresult.out
	./unittest1 >> unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	./randomtestcard1 >> unittestresult.out
	./randomtestcard2 >> unittestresult.out
	./randomtestadventurer >> unittestresult.out

	gcov -b dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

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
	rm -f *.o playdom.exe playdom test.exe test player player.exe unittest1 testInit testInit.exe *.gcov *.gcda *.gcno *.so
