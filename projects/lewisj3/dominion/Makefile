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

unittest%: unittest%.c dominion.o rngs.o
	gcc -o $@ -g  $@.c dominion.o rngs.o $(CFLAGS)

cardtest%: cardtest%.c dominion.o rngs.o
	gcc -o $@ -g  $@.c dominion.o rngs.o $(CFLAGS)

randomtestcard%: randomtestcard%.c dominion.o rngs.o interface.o
	gcc -o $@ -g $@.c dominion.o rngs.o interface.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o interface.o
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o interface.o $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 \
	cardtest2 cardtest3 cardtest4
	touch unittestresults.out
	find \( -name "unittest?" -o -name "cardtest?" \) -exec sh -c '{} &>> unittestresults.out' ';'
	sleep 2
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtests.out: randomtestadventurer randomtestcard1 randomtestcard2
	touch randomtests.out
	-./randomtestadventurer $(arg1) >> randomtests.out 2>&1
	-./randomtestcard1 $(arg1) >> randomtests.out 2>&1
	-./randomtestcard2 $(arg1) >> randomtests.out 2>&1
	sleep 4
	gcov dominion.c >> randomtests.out
	cat dominion.c.gcov >> randomtests.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard unittest1 \
	unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 \
	cardtest4

clean:
	rm -f *.out *.o playdom.exe playdom test.exe test player \
		player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so \
		unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 \
		cardtest3 cardtest4 randomtestcard1 testDrawCard badTestDrawCard \
		randomtestcard2 randomtestadventurer
