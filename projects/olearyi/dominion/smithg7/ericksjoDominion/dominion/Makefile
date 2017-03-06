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

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4

unittestresults.out: dominion.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	echo "***************************************************************" >> unittestresults.out
	echo "   BEGINNING UNIT TESTS" >> unittestresults.out
	echo "***************************************************************" >> unittestresults.out
	./unittest1 >> unittestresults.out
	gcov unittest1 -b >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov unittest2 -b >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov unittest3 -b >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov unittest4 -b >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out
	echo "***************************************************************" >> unittestresults.out
	echo "   BEGINNING CARD TESTS" >> unittestresults.out
	echo "***************************************************************" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov cardtest1 -b >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov cardtest2 -b >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov cardtest3 -b >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov cardtest4 -b >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o interface.o
	gcc -o randomtestadventurer randomtestadventurer.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	./randomtestadventurer 15 
	# >> randomtestadventurer.out
	# gcov dominion.c -b >> randomtestadventurer.out
	# cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard1: randomtestcard1.c dominion.o interface.o
	gcc -o randomtestcard1 randomtestcard1.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	./randomtestcard1 16
	# >> randomtestcard1.out
	# gcov dominion.c -b >> randomtestcard1.out
	# cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2: randomtestcard2.c dominion.o interface.o
	gcc -o randomtestcard2 randomtestcard2.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	./randomtestcard2 17 
	# >> randomtestcard2.out
	# gcov dominion.c -b >> randomtestcard2.out
	# cat dominion.c.gcov >> randomtestcard2.out

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
