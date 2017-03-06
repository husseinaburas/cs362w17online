CFLAGS = -Wall -fpic -coverage -lm

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


randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer
	echo "Saved to randomtestadventurer.out" &> randomtestadventurer.out
	./randomtestadventurer 10 >> randomtestadventurer.out
	gcov -b -f dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard1.out: randomtestcard1
	echo "Saved to randomtestcard1.out" &> randomtestcard1.out
	./randomtestcard1 >> randomtestcard1.out
	gcov -b -f dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestcard2.out: randomtestcard2
	echo "Saved to randomtestcard2.out" &> randomtestcard2.out
	./randomtestcard2  >> randomtestcard2.out
	gcov -b -f dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

randomtestresults.out: randomtestadventurer randomtestcard1 randomtestcard2
	echo "Saved to randomtestresults.out" &> randomtestresults.out
	./randomtestadventurer >> randomtestresults.out
	gcov -b -f dominion.c >> randomtestresults.out
	./randomtestcard1  >> randomtestresults.out
	gcov -b -f dominion.c >> randomtestresults.out
	./randomtestcard2  >> randomtestresults.out
	gcov -b -f dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	
	
unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c rngs.c
	echo "Running dominion unittestresults:" > unittestresults.out
	
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 dominion.c rngs.c unittest1.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 dominion.c rngs.c unittest2.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 dominion.c rngs.c unittest3.c $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 dominion.c rngs.c unittest4.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 dominion.c rngs.c cardtest1.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 dominion.c rngs.c cardtest2.c $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 dominion.c rngs.c cardtest3.c $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 dominion.c rngs.c cardtest4.c $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out

all: playdom player testDrawCard testBuyCard badTestDrawCard unittestresults.out randomtestadventurer.out randomtestcard1.out randomtestcard2.out randomtestresults.out 

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe unittestresults.out unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard1 randomtestcard1 randomtestadventurer.out randomtestcard1.out randomtestcard2.out randomtestresults.out unittestresults.out *.gcov *.gcda *.gcno *.so
