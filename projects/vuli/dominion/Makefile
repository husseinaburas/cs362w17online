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

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -rf *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.dSYM testDrawCard badTestDrawCard \
	unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard1 randomtestcard2

tests_helpers.o: tests_helpers.h tests_helpers.c dominion.h dominion.c
	gcc -c tests_helpers.c -g  $(CFLAGS)


# ---------------------------------------------------------------------------------------
# assn3: Unit testing
unittests: unittest1.c unittest2.c unittest3.c unittest4.c dominion.o rngs.o tests_helpers.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o tests_helpers.o $(CFLAGS)
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o tests_helpers.o $(CFLAGS)
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o tests_helpers.o $(CFLAGS)
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o tests_helpers.o $(CFLAGS)

cardtests: cardtest1.c cardtest2.c dominion.o rngs.o tests_helpers.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o tests_helpers.o $(CFLAGS)
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o tests_helpers.o $(CFLAGS)
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o tests_helpers.o $(CFLAGS)
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o tests_helpers.o $(CFLAGS)

unittestresults.out: unittests cardtests
	./unittest1 > unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out

	echo "**********************************************************" >> unittestresults.out
	gcov -b unittest1.c >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out
	echo "**********************************************************\n" >> unittestresults.out
 
	echo "**********************************************************" >> unittestresults.out
	gcov -b unittest2.c >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out
	echo "**********************************************************\n" >> unittestresults.out
 
	echo "**********************************************************" >> unittestresults.out
	gcov -b unittest3.c >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out
	echo "**********************************************************\n" >> unittestresults.out
 
	echo "**********************************************************" >> unittestresults.out
	gcov -b unittest4.c >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out
	echo "**********************************************************\n" >> unittestresults.out
 
	echo "**********************************************************" >> unittestresults.out
	gcov -b cardtest1.c >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out
	echo "**********************************************************\n" >> unittestresults.out
 
	echo "**********************************************************" >> unittestresults.out
	gcov -b cardtest2.c >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out
	echo "**********************************************************\n" >> unittestresults.out
 
	echo "**********************************************************" >> unittestresults.out
	gcov -b cardtest3.c >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out
	echo "**********************************************************\n" >> unittestresults.out
 
	echo "**********************************************************" >> unittestresults.out
	gcov -b cardtest4.c >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out
	echo "**********************************************************\n" >> unittestresults.out

	echo "**********************************************************" >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	echo "**********************************************************\n" >> unittestresults.out

	echo "**********************************************************" >> unittestresults.out
	gcov -b tests_helpers.c >> unittestresults.out
	cat tests_helpers.c.gcov >> unittestresults.out
	echo "**********************************************************\n" >> unittestresults.out
 

# ---------------------------------------------------------------------------------------
# assn4: Random testing
RANDOM_TESTS_SEED=4

randomtestcard1.out: randomtestcard1.c dominion.o rngs.o tests_helpers.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o tests_helpers.o $(CFLAGS)	
	./randomtestcard1 $(RANDOM_TESTS_SEED) > randomtestcard1.out
	echo "**********************************************************" >> randomtestcard1.out
	gcov -b randomtestcard1.c >> randomtestcard1.out
	cat randomtestcard1.c.gcov >> randomtestcard1.out
	echo "**********************************************************\n" >> randomtestcard1.out
	echo "**********************************************************" >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	echo "**********************************************************\n" >> randomtestcard1.out

randomtestcard2.out: randomtestcard2.c dominion.o rngs.o tests_helpers.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o tests_helpers.o $(CFLAGS)	
	./randomtestcard2 $(RANDOM_TESTS_SEED) > randomtestcard2.out
	echo "**********************************************************" >> randomtestcard2.out
	gcov -b randomtestcard2.c >> randomtestcard2.out
	cat randomtestcard2.c.gcov >> randomtestcard2.out
	echo "**********************************************************\n" >> randomtestcard2.out
	echo "**********************************************************" >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	echo "**********************************************************\n" >> randomtestcard2.out

randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o tests_helpers.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o tests_helpers.o $(CFLAGS)	
	./randomtestadventurer $(RANDOM_TESTS_SEED) > randomtestadventurer.out
	echo "**********************************************************" >> randomtestadventurer.out
	gcov -b randomtestadventurer.c >> randomtestadventurer.out
	cat randomtestadventurer.c.gcov >> randomtestadventurer.out
	echo "**********************************************************\n" >> randomtestadventurer.out
	echo "**********************************************************" >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	echo "**********************************************************\n" >> randomtestadventurer.out

randomtests: randomtestcard1.out randomtestcard2.out randomtestadventurer.out


